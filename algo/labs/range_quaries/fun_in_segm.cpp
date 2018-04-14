#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>
std::string file_name = "fun";
#define MAX_NUM 1000001
#define MAX_N 200001
long long res = 0;
int segm_l = 0, segm_r = 0;
int cnt[MAX_NUM], arr[MAX_N];

inline void add_ind(int ind) {
	res += (long long)((cnt[arr[ind]] << 1) + 1) * arr[ind];
	cnt[arr[ind]]++;
}

inline void del_ind(int ind) {
	cnt[arr[ind]]--;
	res -= (long long)((cnt[arr[ind]] << 1) + 1) * arr[ind];
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		arr[i] = a;
	}

	struct query {
		int left, right, num;
	};
	std::vector<query> queries(m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &queries[i].left, &queries[i].right);
		queries[i].num = i;
		queries[i].left--;
		queries[i].right--;
	}

	static const int k = int(double(sqrt(n)));
	std::sort(queries.begin(), queries.end(), [](const query &a, const query &b) {return ((a.left / k) != (b.left / k) ? a.left < b.left : a.right < b.right);  });

	std::vector<long long> answers(m);
	add_ind(0);
	for (int i = 0; i < m; i++) {
		int cur_left = queries[i].left, cur_right = queries[i].right;
		while (cur_left < segm_l)
			add_ind(--segm_l);
		while (segm_l < cur_left)
			del_ind(segm_l++);
		while (segm_r < cur_right)
			add_ind(++segm_r);
		while (cur_right < segm_r)
			del_ind(segm_r--);
		answers[queries[i].num] = res;
	}
	for (size_t i = 0; i < answers.size(); i++) {
		printf("%lld\n", answers[i]);
	}
	return 0;
}