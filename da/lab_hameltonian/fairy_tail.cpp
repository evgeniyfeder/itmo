#include <iostream>
#include <string>
#include <list>

std::list<int> order;

void search_place(int left, int right, int vase) {
	static std::string res;
	while (right - left > 1) {
		int mid = left + (right - left) / 2;
		
		auto elem_mid = order.begin();
		std::advance(elem_mid, mid);

		std::cout << 1 << " " << *elem_mid << " " << vase << std::endl;
		std::cout.flush();

		std::cin >> res;
		
		if (res == "YES")
			left = mid;
		else
			right = mid;
	}
	auto need_insert = order.begin();
	std::advance(need_insert, right);
	order.insert(need_insert, vase);
}

int main() {
/*#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif*/
	std::ios_base::sync_with_stdio(false);
	
	int n;
	std::cin >> n;
	
	order.push_back(1);
	for (int i = 2; i <= n; i++)
		search_place(-1, i - 1, i);
	
	std::cout << 0 << " ";
	for (auto &i : order)
		std::cout << i << " ";

}
