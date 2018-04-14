#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <string.h>
#include <queue>

std::string file_name = "search4";

static const size_t alpha_size = 26;

class pork {	
private:
	struct node {
		int next[alpha_size];
		std::vector<int> term;

		int suf_link, super_link;
	};

	std::vector<node> nodes;
	int num_strings = 0;
public:
	pork() {
		nodes.emplace_back();
	}

	void add_string(const std::string &str) {
		int cur_v = 0;

		for (size_t i = 0; i < str.size(); i++) {
			const int next = str[i] - 'a';

			if (nodes[cur_v].next[next] == 0) {
				nodes.emplace_back();
				nodes[cur_v].next[next] = (int)nodes.size() - 1;
			}

			cur_v = nodes[cur_v].next[next];
		}
		nodes[cur_v].term.push_back(num_strings++);
	}

	void build() {
		std::queue<int> q;

		q.push(0);
		while (!q.empty()) {
			int cur = q.front();
			q.pop();

			for (size_t c = 0; c < alpha_size; c++) {
				if (nodes[cur].next[c] == 0) {
					nodes[cur].next[c] = nodes[nodes[cur].suf_link].next[c];
				}
				else {
					int next = nodes[cur].next[c];

					if (cur != 0) {
						nodes[next].suf_link = nodes[nodes[cur].suf_link].next[c];
						nodes[next].super_link =
							!nodes[nodes[next].suf_link].term.empty() ?
							nodes[next].suf_link : nodes[nodes[next].suf_link].super_link;
					}
					q.push(next);
				}
			}
		}
	}

	std::vector<bool> find_entry_in_text_once(std::string text) {
		std::vector<bool> entry(num_strings);
		std::vector<bool> was(nodes.size());

		int cur = 0;
		for (size_t i = 0; i < text.size(); i++) {
			cur = nodes[cur].next[text[i] - 'a'];

			int tmp = cur;
			while (!was[tmp]) {
				 if (!nodes[tmp].term.empty()) {
					for (auto &&ends : nodes[tmp].term)
						entry[ends] = true;
				 }
				 was[tmp] = true;
				 tmp = nodes[tmp].super_link;
			}
		}
		return entry;
	}
};

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	pork p;

	int n;
	std::cin >> n;

	std::string str;
	for (int i = 0; i < n; i++) {
		std::cin >> str;
		p.add_string(str);
	}
	
	std::string text;
	std::cin >> text;

	p.build();
	auto res = p.find_entry_in_text_once(text);

	for (size_t i = 0; i < res.size(); i++) {
		if (res[i])
			std::cout << "YES\n";
		else
			std::cout << "NO\n";
	}
}