#include "gtest/gtest.h"
#include "pers_set.h"
#include <vector>
using namespace std;

template <typename T>
vector<T> vec(persistent_set<T> const& s) {
	vector<T> res;
	for (auto it = s.begin(); it != s.end(); ++it) {
		res.push_back(*it);
	}
	return res;
}

TEST(test_set, insert) {
	persistent_set<int> s;
	s.insert(32);
	s.insert(33);
	EXPECT_EQ(vector<int>({32, 33}), vec(s));
}

TEST(test_set, insert_10_elements) {
	persistent_set<int> s;
	for (int i = 0; i < 5; i++) {
		s.insert(i);
	}
	for (int j = 9; j >= 5; j--) {
		s.insert(j);
	}
	EXPECT_EQ(vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
}

TEST(test_set, copy) {
	persistent_set<int> s;
	s.insert(1);
	persistent_set<int> p(s);
	p.insert(2);
	EXPECT_EQ(vector<int>({ 1 }), vec(s));
	EXPECT_EQ(vector<int>({ 1, 2 }), vec(p));
}

TEST(test_set, copy2) {
	persistent_set<int> s;
	s.insert(12);
	persistent_set<int> p(s);
	s.insert(45);
	EXPECT_EQ(vector<int>({ 12, 45 }), vec(s));
	EXPECT_EQ(vector<int>({ 12 }), vec(p));
	p.insert(0);
	EXPECT_EQ(vector<int>({ 12, 45 }), vec(s));
	EXPECT_EQ(vector<int>({ 0, 12 }), vec(p));
}

TEST(test_set, insert_and_copy) {
	persistent_set<int> s;
	s.insert(4);
	s.insert(5);
	s.insert(7);
	s.insert(6);
	s.insert(1);
	s.insert(2);
	s.insert(8);
	s.insert(3);
	s.insert(0);
	s.insert(9);
	EXPECT_EQ(vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
	persistent_set<int> p(s);
	s.insert(100);
	EXPECT_EQ(vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 100 }), vec(s));
	EXPECT_EQ(vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(p));
}
TEST(test_set, erase0) {
	persistent_set<int> s;
	s.insert(4);
	s.erase(s.begin());
	EXPECT_EQ(vector<int>({}), vec(s));
}

TEST(test_set, erase) {
	persistent_set<int> s;
	EXPECT_EQ(vector<int>({ }), vec(s));
	s.insert(4);
	EXPECT_EQ(vector<int>({ 4 }), vec(s));
	s.insert(5);
	EXPECT_EQ(vector<int>({ 4, 5 }), vec(s));
	s.insert(7);
	EXPECT_EQ(vector<int>({ 4, 5, 7 }), vec(s));
	s.insert(6);
	EXPECT_EQ(vector<int>({ 4, 5, 6, 7 }), vec(s));
	s.insert(1);
	EXPECT_EQ(vector<int>({ 1, 4, 5, 6, 7 }), vec(s));
	s.insert(2);
	EXPECT_EQ(vector<int>({ 1, 2, 4, 5, 6, 7 }), vec(s));
	s.insert(8);
	EXPECT_EQ(vector<int>({ 1, 2, 4, 5, 6, 7, 8 }), vec(s));
	s.insert(3);
	EXPECT_EQ(vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8 }), vec(s));
	s.insert(0);
	EXPECT_EQ(vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8 }), vec(s));
	s.insert(9);
	EXPECT_EQ(vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
	s.erase(s.begin());
	EXPECT_EQ(vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
	s.erase(s.find(5));
	EXPECT_EQ(vector<int>({ 1, 2, 3, 4, 6, 7, 8, 9 }), vec(s));
	s.erase(s.find(3));
	EXPECT_EQ(vector<int>({ 1, 2, 4, 6, 7, 8, 9 }), vec(s));
	s.erase(s.find(7));
	EXPECT_EQ(vector<int>({ 1, 2, 4, 6, 8, 9 }), vec(s));
	s.erase(s.find(1));
	EXPECT_EQ(vector<int>({ 2, 4, 6, 8, 9 }), vec(s));
	s.erase(s.find(8));
	EXPECT_EQ(vector<int>({ 2, 4, 6, 9 }), vec(s));
	s.erase(s.find(9));
	EXPECT_EQ(vector<int>({2, 4, 6}), vec(s));
	s.erase(s.find(4));
	EXPECT_EQ(vector<int>({ 2, 6 }), vec(s));
	s.erase(s.begin());
	EXPECT_EQ(vector<int>({ 6 }), vec(s));
	s.erase(s.begin());
	EXPECT_EQ(vector<int>({ }), vec(s));
	s.insert(100);
	EXPECT_EQ(vector<int>({ 100 }), vec(s));
	s.erase(s.find(100));
	EXPECT_EQ(vector<int>({}), vec(s));
}

TEST(test_set, erase2) {
	persistent_set<int> s;
	s.insert(4);
	s.insert(5);
	s.insert(7);
	s.insert(6);
	s.insert(1);
	s.insert(2);
	s.insert(8);
	s.insert(3);
	s.insert(0);
	s.insert(9);
	EXPECT_EQ(vector<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), vec(s));
	persistent_set<int> p;
	for (int i = 0; i < 10; i++) {
		p = s;
		auto it = p.begin();
		for (int j = 0; j < i; j++) {
			it++;
		}
		p.erase(it);
		vector<int> ans({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
		ans.erase(ans.begin() + i);
		EXPECT_EQ(ans, vec(p));
	}
}

struct smth {
	int var;
	smth(int var) : var(var) {}
	smth() = delete;
	smth(smth const& rhs) {
		var = rhs.var;
	}
	smth(smth&& rhs) noexcept {
		var = rhs.var;
	}
	bool operator<(smth const& rhs) const {
		return var < rhs.var;
	}
	bool operator==(smth const& rhs) const {
		return var == rhs.var;
	}
};

TEST(test_set, smth) {
	persistent_set<smth> s;
	s.insert(smth(2));
	s.insert(smth(1));
	s.erase(s.find(2));
	s.insert(smth(5));
	EXPECT_EQ(vector<smth>({1, 5}), vec(s));
	persistent_set<smth> p(s);
	p.insert(smth(0));
	EXPECT_EQ(vector<smth>({ 1, 5 }), vec(s));
	EXPECT_EQ(vector<smth>({ 0, 1, 5 }), vec(p));
	persistent_set<smth> q(s);
	s.insert(smth(8));
	EXPECT_EQ(vector<smth>({ 1, 5 }), vec(q));
	q = s;
	EXPECT_EQ(vector<smth>({ 1, 5, 8 }), vec(s));
	EXPECT_EQ(vector<smth>({ 1, 5, 8 }), vec(q));
	s.erase(s.find(8));
	EXPECT_EQ(vector<smth>({ 1, 5 }), vec(s));
	EXPECT_EQ(vector<smth>({ 1, 5, 8 }), vec(q));
}

TEST(test_linked_ptr, copy_null) {
	my_linked_ptr<int> a;
	my_linked_ptr<int> b = a;
	my_linked_ptr<int> c = a;
	my_linked_ptr<int> d = a;
	my_linked_ptr<int> e = a;

	my_linked_ptr<int> f(new int(5));
	a = f;
	c = f;
	f = f;
	d = f;
	b = my_linked_ptr<int>(new int(6));
	c = b;
	swap(b, c);
	f = c;
	e = f;
	a = f;
	d = a;
	b = f;
}

TEST(test_set, full_tree) {
	persistent_set<int> s;
	s.insert(4);
	s.insert(2);
	s.insert(3);
	s.insert(1);
	s.insert(6);
	s.insert(5);
	s.insert(7);
	EXPECT_EQ(vector<int>({ 1, 2, 3, 4, 5, 6, 7 }), vec(s));
}

TEST(test_set, second_insert) {
	persistent_set<int> s;
	s.insert(4);
	s.insert(4);
	s.insert(2);
	s.insert(3);
	s.insert(1);
	s.insert(6);
	s.insert(5);
	s.insert(7);
	s.insert(3);
	EXPECT_EQ(vector<int>({ 1, 2, 3, 4, 5, 6, 7 }), vec(s));
}

TEST(test_set, decrease_end) {
	persistent_set<int> s;
	s.insert(4);
	s.insert(12);
	s.insert(1);
	persistent_set<int>::iterator it = s.end();
	it--;
	EXPECT_EQ(12, *it);
}

template < typename Set >
std::vector < std::vector < int > > test(std::string const& msg) {
	int tt = clock();
	srand(100);
	std::vector < Set > ss(256);
	for (int i = 0; i < 1000000; ++i) {
		int r = rand() & 7;
		if (r == 0) {
			int j = rand() & 255;
			ss[j] = ss[rand() & 255];
		} else if (r <= 3) {
			int j = rand() & 255;
			ss[j].insert(rand() & 16383);
		} else {
			int j = rand() & 255;
			auto it = ss[j].find(rand() & 16383);
			if (it != ss[j].end())
				ss[j].erase(it);
		}
	}
	std::vector < std::vector < int > > a(256);
	for (int i = 0; i < 256; ++i)
		for (int x : ss[i])
			a[i].push_back(x);
	std::cout << msg << " " << 1.*(clock() - tt) / CLOCKS_PER_SEC << "\n";
	return a;
}

TEST(test_set, random) {
	auto r1 = test<persistent_set<int, my_shared_ptr>>("shared_ptr");
	auto r2 = test<persistent_set<int, my_linked_ptr>>("linked_ptr");
	EXPECT_EQ(r1, r2);
	auto r3 = test<set<int>>("std::set  ");
	EXPECT_EQ(r2, r3);
}