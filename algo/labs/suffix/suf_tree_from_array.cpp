#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <set>

// std::string file_name = "common";

static const int alphasize = 256;
class suf_array {
private:
	std::string str;
	std::vector<int> permutation;

public:
	suf_array(const std::string &new_str) : str(new_str), permutation(new_str.size()) {
		str.push_back(1);
		int n = (int)str.size();

		/* Sort with size 1 */
		std::vector<int> cnt(std::max(n, alphasize));
		std::vector<int> perm(n), classes(n);

		for (auto c : str)
			++cnt[c];
		for (int i = 1; i < alphasize; i++)
			cnt[i] += cnt[i - 1];

		for (int i = 0; i < n; i++)
			perm[--cnt[str[i]]] = i;

		classes[perm[0]] = 0;
		int classes_num = 1;
		for (int i = 1; i < n; i++) {
			if (str[perm[i]] != str[perm[i - 1]]) classes_num++;
			classes[perm[i]] = classes_num - 1;
		}


		std::vector<int> next_perm(n), next_classes(n);
		for (int h = 0; (1 << h) < n; h++) {
			int len = 1 << h;

			/* Generate new permutation */
			for (int i = 0; i < n; i++) {
				next_perm[i] = perm[i] - len;
				if (next_perm[i] < 0) next_perm[i] += n;
			}
			memset(cnt.data(), 0, sizeof(int) * classes_num);

			for (int i = 0; i < n; i++)
				++cnt[classes[next_perm[i]]];
			for (int i = 1; i < classes_num; i++)
				cnt[i] += cnt[i - 1];

			for (int i = n - 1; i >= 0; i--)
				perm[--cnt[classes[next_perm[i]]]] = next_perm[i];

			/* Generate new classes */
			next_classes[perm[0]] = 0;
			classes_num = 1;
			for (int i = 1; i < n; i++) {
				const int mid1 = (perm[i] + len) % n;
				const int mid2 = (perm[i - 1] + len) % n;
				if (classes[perm[i]] != classes[perm[i - 1]] || classes[mid1] != classes[mid2])
					++classes_num;
				next_classes[perm[i]] = classes_num - 1;
			}
			memcpy(classes.data(), next_classes.data(), n * sizeof(int));
		}

		for (int i = 0; i < n - 1; i++)
			permutation[i] = perm[i + 1];
		str.pop_back();
	}

	void print() {
		for (auto &&i : permutation) {
			std::cout << i + 1 << ' ';
		}
		std::cout << '\n';
	}

	std::vector<int> count_lcp() {
		int size = (int)permutation.size();

		std::vector<int> rev_perm(size); // index str -> permutation number
		for (int i = 0; i < size; i++)
			rev_perm[permutation[i]] = i;

		std::vector<int> result(size - 1);

		str.push_back(1);

		int cur_lcp = 0;
		for (int i = 0; i < size; i++) {
			if (cur_lcp > 0)
				--cur_lcp;
			if (rev_perm[i] == size - 1)
				cur_lcp = 0;
			else {
				while (str[i + cur_lcp] == str[permutation[rev_perm[i] + 1] + cur_lcp])
					cur_lcp++;
				result[rev_perm[i]] = cur_lcp;
			}
		}
		str.pop_back();

		return result;
	}


	void build_tree() {
		auto lcp = count_lcp();
		int n = str.size();

		for (i)
	}
};
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	/*#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);*/
#endif
	std::ios_base::sync_with_stdio(false);
	std::string a;
	std::cin >> a;

	std::reverse(a.begin(), a.end());
	suf_array sa(a);
	auto res = sa.count_substring_for_every_suffix();

	for (auto &&x : res)
		std::cout << x << '\n';

	return 0;
}
