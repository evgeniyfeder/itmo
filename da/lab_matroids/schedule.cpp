#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
std::string file_name = "schedule";

struct task {
	int dedline, cost;
	task(int dedline, int cost) : dedline(dedline), cost(cost) {}
};

std::map<int, int> s;
std::vector<task> v;
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);
	int n;
	
	std::cin >> n;
	int max_dedline = 0;
	for (int i = 0; i < n ; i++) {
		int dedline, cost;
		std::cin >> dedline >> cost;

		v.emplace_back(dedline, cost);
		max_dedline = std::max(max_dedline, dedline);
	}

	std::sort(v.begin(), v.end(), [](const task &a, const task &b) {return a.cost > b.cost; });
	
	if (max_dedline != 0)
		s.insert(std::make_pair(max_dedline, max_dedline));
	int64_t res = 0;
	for (int i = 0; i < n; i++) {
		int deadline = v[i].dedline;
		
		auto last_empty_it = s.lower_bound(deadline);
		if (deadline == 0) {
			res += v[i].cost;
			continue;
		}
		
		if (last_empty_it == s.end()) {
			if (s.size() != 0) {
				auto it = --s.end();
				auto last_empty = std::make_pair(it->first, it->second);
				s.erase(it);
				
				if (last_empty.second != 1)
					s.insert(std::make_pair(last_empty.first - 1, last_empty.second - 1));
				continue;
			}
			else {
				res += v[i].cost;
				continue;
			}
		}

		auto last_empty = std::make_pair(last_empty_it->first, last_empty_it->second);
		if (last_empty.first - last_empty.second + 1 > deadline) {
			if (last_empty_it != s.begin()) {
				--last_empty_it;
				auto last_empty_prev = std::make_pair(last_empty_it->first, last_empty_it->second);
				s.erase(last_empty_it);

				if (last_empty_prev.second != 1)
					s.insert(std::make_pair(last_empty_prev.first - 1, last_empty_prev.second - 1));
				continue;
			}
			else {
				res += v[i].cost;
				continue;
			}
		}

		s.erase(last_empty_it);

		if (last_empty.first == deadline) {
			if (last_empty.second != 1)
				s.insert(std::make_pair(deadline - 1, last_empty.second - 1));
		}
		else if (last_empty.first - last_empty.second + 1 < deadline) {
			s.insert(std::make_pair(deadline - 1, last_empty.second - (last_empty.first - deadline + 1)));
			s.insert(std::make_pair(last_empty.first, last_empty.first - deadline));
		}
		else if (last_empty.first - last_empty.second + 1 == deadline) {
			s.insert(std::make_pair(last_empty.first, last_empty.second - 1));
		}
		else {
			s.insert(std::make_pair(last_empty.first, last_empty.second));
			res += v[i].cost;
		}
	}
	std::cout << res << std::endl;
}
