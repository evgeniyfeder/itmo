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

	long long num_unique_str() {
		int size = (int)permutation.size();

		std::vector<int> rev_perm(size); // index str -> permutation number
		for (int i = 0; i < size; i++)
			rev_perm[permutation[i]] = i;

		std::vector<int> result(size - 1);

		str.push_back(1);

		int cur_lcp = 0;
		long long sum = 0;
		for (int i = 0; i < size; i++) {
			if (cur_lcp > 0)
				--cur_lcp;
			if (rev_perm[i] == size - 1)
				cur_lcp = 0;
			else {
				while (str[i + cur_lcp] == str[permutation[rev_perm[i] + 1] + cur_lcp])
					cur_lcp++;
				result[rev_perm[i]] = cur_lcp;
				sum += cur_lcp;
			}
		}
		str.pop_back();

		return (long long)size * (long long)(size + 1) / 2 - sum;
	}

	void refren() {
		auto lcp = count_lcp();
		int n = (int)lcp.size() + 1;

		std::set<std::pair<int, int>> sorted_lcp;
		for (int i = 0; i < (int)lcp.size(); i++) {
			sorted_lcp.insert(std::make_pair(lcp[i], i));
		}

		std::set<int> used;
		used.insert(-1);

		int r = 0, l = 0;
		int64_t refren = -1;
		for (auto &&x : sorted_lcp) { // lcp, ind
			auto ins_res = used.insert(x.second); // <pair, is_new>
			if (x.first != 0) {
				auto r_it = ++ins_res.first;
				auto l_it = ----ins_res.first;
				int cur_r, cur_l;

				if (r_it == used.end())
					cur_r = n - 1;
				else
					cur_r = *r_it;
				cur_l = *l_it;

				int64_t cur_refren = (int64_t)x.first * (cur_r - cur_l);
				if (cur_refren > refren) {
					refren = cur_refren;
					r = cur_r;
					l = cur_l;
				}
			}
		}

		if (refren >= (int64_t)lcp.size()) {
			int64_t len = refren / (r - l);
			std::cout << refren << '\n' << len << '\n';
			for (int i = 0; i < len; i++)
				std::cout << int(str[permutation[l + 1] + i] - 10) << ' ';
		}
		else {
			std::cout << n << '\n' << n << '\n';
			for (int i = 0; i < (int)n; i++)
				std::cout << int(str[i] - 10) << ' ';
		}
	}


	int get_data(const std::vector<std::vector<int>> &vec, int len, int ind, int n) {
		if (ind >= n)
			return INT_MAX;
		return vec[len][ind];
	}
	/* Need create suf array s1#s2 for common s1 s2 */
	std::string count_common_string(int len1) {
		auto lcp = count_lcp();
		int n = (int)lcp.size();
		int max_ind = 0, max = -1;
		
		for (int i = 0; i < n; i++) {
			if ((permutation[i] < len1 && permutation[i + 1] >= len1) || (permutation[i] >= len1 && permutation[i + 1] < len1)) {
				if (lcp[i] > max) {
					max = lcp[i];
					max_ind = permutation[i];
				}
			}
		}

		return str.substr(max_ind, max);
	}

	/* Count strings for every prefix */
	std::vector<std::vector<int32_t>> sparse;
	std::vector<int> log_length;

	int get_segm_min(int left, int right) {
		if (left > right) std::swap(left, right);
		int l = right - left + 1;
		return std::min(sparse[left][log_length[l]], sparse[right - (1 << log_length[l]) + 1][log_length[l]]);
	}

	std::vector<int64_t> count_substring_for_every_suffix() {
		auto lcp = count_lcp();
		int n = (int)lcp.size();

		/* Count sparse table */
		log_length.resize(n + 1);
		log_length[0] = -1;
		for (int i = 1; i <= n; i++) {
			log_length[i] = log_length[i - 1] + int((i & (i - 1)) == 0);
		}

		sparse.resize(n);
		int logn = log_length[n] + 1;
		for (int i = 0; i < n; i++) {
			sparse[i].resize(logn);
			sparse[i][0] = lcp[i];
		}

		for (int step = 1; step < logn; step++) {
			for (int i = 0; i < n; i++) {
				if (i + (1 << (step - 1)) >= n)
					break;
				sparse[i][step] = std::min(sparse[i][step - 1], sparse[i + (1 << (step - 1))][step - 1]);
			}
		}

		/* Count result */
		std::vector<int64_t> result;

		std::set<int> used;
		used.insert(-1);

		std::vector<int> rev_perm(n + 1); // index str -> permutation number
		for (int i = 0; i < n + 1; i++)
			rev_perm[permutation[i]] = i;

		/*for (int i = 0; i < n + 1; i++)
			std::cout << str.substr(permutation[i], n + 1 - permutation[i]) << '\n'; */

		int64_t res = 1;
		used.insert(rev_perm[n]);
		result.push_back(1);
		for (int i = n - 1; i >= 0; i--) { // lcp, ind
			auto ins_res = used.insert(rev_perm[i]); // <pair, is_new>
			auto r_it = ++ins_res.first;
			auto l_it = ----ins_res.first;
			
			int cur_res = 0;
			if (r_it != used.end())
				cur_res = std::max(get_segm_min(rev_perm[i], *r_it - 1), cur_res);
			if (*l_it != -1)
				cur_res = std::max(get_segm_min(*l_it, rev_perm[i] - 1), cur_res);
			res += (int64_t)n + 1 - i - cur_res;
			result.push_back(res);
		}
		return result;
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
