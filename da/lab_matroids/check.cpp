#include <iostream>
#include <set>
#include <unordered_map>
std::string file_name = "check";

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	int n, m;
	std::cin >> n >> m;
	bool has_zero = false;
	std::unordered_map<int, std::vector<int>> S;

	for (int i = 0; i < m; i++) {
		int cur = 0, size;
		std::cin >> size;

		if (size == 0)
			has_zero = true;

		std::vector<int> v;
		for (int j = 0, shift; j < size; j++) {
			std::cin >> shift;
			cur |= 1 << (shift - 1);
			v.push_back(shift - 1);
		}
		S.insert(std::make_pair(cur, v));
	}

	/* Check 1 */
	if (!has_zero) {
		std::cout << "NO";
		return 0;
	}

	/* Check 2 */
	int max = 1 << n;
	std::vector<bool> check_2(max, true);
	check_2[0] = true;
	for (int i = 1; i < max; i++) {
		int cur_ind = 0;
		check_2[i] = S.find(i) != S.end();
		while ((1 << cur_ind) <= i) {
			int cur = i & (~(1 << cur_ind));
			check_2[i] = check_2[cur] & check_2[i];
			
			cur_ind++;
		}
	}
	
	for (auto it = S.begin(); it != S.end(); ++it)
		if (!check_2[it->first]) {
			std::cout << "NO";
			return 0;
		}

	/* Check 3 */
	for (auto a = S.begin(); a != S.end(); ++a) {
		for (auto b = a; b != S.end(); ++b) {
			if (a->second.size() > b->second.size()) {
				std::vector<bool> b_without_a(n);
				for (int i = 0; i < a->second.size(); i++)
					b_without_a[a->second[i]] = true;
				for (int i = 0; i < b->second.size(); i++)
					b_without_a[b->second[i]] = false;

				bool check = false;
				for (int i = 0; i < n; i++) {
					if (b_without_a[i])
						check |= (S.find(b->first | (1 << i)) != S.end());
				}
				if (!check) {
					std::cout << "NO";
					return 0;
				}
			}
			else if (a->second.size() < b->second.size()) {
				std::vector<bool> b_without_a(n);
				for (int i = 0; i < b->second.size(); i++)
					b_without_a[b->second[i]] = true;
				for (int i = 0; i < a->second.size(); i++)
					b_without_a[a->second[i]] = false;

				bool check = false;
				for (int i = 0; i < n; i++) {
					if (b_without_a[i])
						check |= (S.find(a->first | (1 << i)) != S.end());
				}
				if (!check) {
					std::cout << "NO";
					return 0;
				}
			}
		}
	}
	std::cout << "YES";
	return 0;
}
