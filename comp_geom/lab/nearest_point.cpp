#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <queue>
#include <cmath>
#include <algorithm>
#include <limits>

double sqr(double a) { return a * a; }

struct Point {
   using point_type = double;

   point_type x, y;

   Point(point_type new_x = 0, point_type new_y = 0) : x(new_x), y(new_y) {}

   double len() const {
       return sqrt(sqr(x) + sqr(y));
   }

   Point operator*(point_type a) const {
      return Point(a * x, a * y);
   }

   Point operator/(point_type a) const{
      return Point(x / a, y / a);
   }

   Point operator+(Point const & p) const {
      return Point(x + p.x, y + p.y);
   }

   Point operator-(Point const & p) const {
      return Point(x - p.x, y - p.y);
   }
};

struct IndexedPoint {
   Point p;
   size_t index;

   IndexedPoint(Point const &p, size_t index) : p(p), index(index) {}
};

struct Rect {
   Point center, halfsize;

   Rect(Point const &center, Point const & halfsize) : center(center), halfsize(halfsize){}
};


class QuadTree {
private:
    struct Node {
        Point ld, ur;
        std::vector<std::unique_ptr<Node>> childs;
        std::vector<IndexedPoint> pts;

        void create_child(std::vector<IndexedPoint> const & pts, Point const & new_ld, Point const & new_ru,
                          std::function<bool(Point const &)> pred) {
            std::vector<IndexedPoint> new_pts;
            for (auto && ip : pts) {
                if (pred(ip.p)) {
                    new_pts.emplace_back(ip);
                }
            }
            childs.emplace_back(new Node(new_pts, new_ld, new_ru));
        }

        Node(std::vector<IndexedPoint> const & pts, Point const &ld, Point const & ur) : ld(ld), ur(ur) {
            if (pts.size() <= 4) {
                this->pts = pts;
                return;
            }
            Point med = (ld + ur) / 2;
            // left down
            create_child(pts, {ld.x, ld.y}, {med.x, med.y}, [&med](Point const &p) { return p.x <  med.x && p.y <  med.y; });
            // right down
            create_child(pts, {med.x, ld.y}, {ur.x, med.y}, [&med](Point const &p) { return p.x >=  med.x && p.y <  med.y; });
            // left up
            create_child(pts, {ld.x, med.y}, {med.x, ur.y}, [&med](Point const &p) { return p.x < med.x && p.y >= med.y; });
            // right up
            create_child(pts, {med.x, med.y}, {ur.x, ur.y}, [&med](Point const &p) { return p.x >=  med.x && p.y >= med.y; });
        }
    };
    std::unique_ptr<Node> head;

public:
    QuadTree(std::vector<Point> const &pts) {
        Point ld = pts[0], ur = pts[0];
        for (auto && p : pts) {
            if (ld.x > p.x)
                ld.x = p.x;
            if (ld.y > p.y)
                ld.y = p.y;
            if (ur.x < p.x)
                ur.x = p.x;
            if (ur.y < p.y)
                ur.y = p.y;
        }

        ld = {-2048, -2048};
        ur = {2048, 2048};

        std::vector<IndexedPoint> id_pts;
        id_pts.reserve(pts.size());
        for (size_t i = 0; i < pts.size(); i++) {
            id_pts.emplace_back(pts[i], i);
        }
        head = std::make_unique<Node>(id_pts, ld, ur);
    }

    double dist(Point const & p, Node const * rect) {
       Point center = (rect->ld + rect->ur) / 2;
       Point halfsize = (rect->ur - rect->ld) / 2;
       double dx = std::max(std::abs(p.x - center.x) - halfsize.x, 0.);
       double dy = std::max(std::abs(p.y - center.y) - halfsize.y, 0.);
       return sqrt(dx * dx + dy * dy);
    }

    size_t find_nearest(Point const & p) {
        auto comp = [=](Node const * a, Node const * b) {
                   return dist(p, a) > dist(p, b);
               };
        std::priority_queue<Node *, std::vector<Node *>, decltype(comp)> pqueue(comp);

        double min_dist = std::numeric_limits<double>::max();
        size_t index = std::numeric_limits<size_t>::max();
        pqueue.push(head.get());
        while (pqueue.size() > 0 && min_dist > dist(p, pqueue.top())) {
            Node *node = pqueue.top();
            pqueue.pop();
            if (node->childs.size() > 0) {
               for (auto && ptrc : node->childs) {
                  pqueue.push(ptrc.get());
               }
            } else {
               for (auto const & curp : node->pts) {
                  double cdist = (p - curp.p).len();
                  if (cdist < min_dist) {
                     min_dist = cdist;
                     index = curp.index;
                  }
               }
            }
        }
        return index;
    }
};

int main() {
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Point> pts;
    for (size_t i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;
        pts.emplace_back(x, y);
    }

    QuadTree qt(pts);

    for (size_t i = 0; i < m; ++i) {
        int32_t x, y;
        std::cin >> x >> y;
        std::cout << qt.find_nearest(Point(x, y)) + 1 << std::endl;
    }
}
