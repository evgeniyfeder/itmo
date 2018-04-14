#include <string>
#include <iostream>
#include <vector>

typedef unsigned int uint;

uint p_mul[] = { 1, 31, 961, 29791, 923521, 28629151, 887503681, 1742810335, 2487512833, 4098453791, 2498015937, 129082719, 4001564289, 3789408671, 1507551809, 3784433119, 1353309697, 3297894943, 3450495425, 3886143071, 211350913, 2256911007, 1244764481, 4227960543, 2217757953, 31019807, 961614017, 4040230751, 693101697, 11316127, 350799937, 2284863455, 2111290369, 1025491999, 1725480897, 1950300255, 329765761, 1632803999, 3372283713, 1461579999, 2359307009, 124073247, 3846270657, 3270273375, 2594226817, 3111619999, 1970939457, 969581023, 4287207937, 4054427167, 1133190593, 769170015, 2369433985, 438009503, 693392705, 20337375, 630458625, 2364348191, 280349889, 100911967, 3128270977, 2487119775, 4086268993, 2120287199, 1304393729, 1781499935, 3686890433, 2624453727, 4048654209, 954228895, 3811291969, 2185934047, 3339446017, 443611423, 867052225, 1108815199, 13532801, 419516831, 120119873, 3723716063, 3766048257, 783378975, 2809911745, 1207918175, 3085725057, 1168196255, 1854345537, 1650136799, 3909600513, 938531615, 3324676289, 4280717151, 3853212801, 3485479839, 675692609, 3766601695, 800535553, 3341765663, 515520449, 3096232031, 1493912449 };
#define SIZE_STR 100
#define SIZE_MASK 2
uint hash(std::string key) {
	uint hash = 0;
	for (size_t i = 1; i <= key.length(); i++) {
		hash += p_mul[i] * key[key.length() - i];
	}
	/*int hash = 0;
	for (int i = 0; i < n; ++i)
	hash = (hash * p + s[i] - 'a' + mod) % mod; */
	return hash;
}

std::string file_name = "";
int main(void) {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	std::vector<std::string> strings;
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < 26; ++j) {
			std::string str;
			str.push_back('a' + i);
			str.push_back('a' + j);
			strings.push_back(str);
			str.clear();
			str.push_back('A' + i);
			str.push_back('A' + j);
			strings.push_back(str);
			str.clear();
			str.push_back('a' + i);
			str.push_back('A' + j);
			strings.push_back(str);
			str.clear();
			str.push_back('A' + i);
			str.push_back('a' + j);
			strings.push_back(str);

		}

	for (int i = 0; i < strings.size(); i++)
		for (int j = i + 1; j < strings.size(); j++) {
			uint a = hash(strings[i]), b = hash(strings[j]);
			if (a == b)
				std::cout << strings[i] << " " << strings[j] << " " << hash(strings[j]) << std::endl;
		}
	/* uint p = 31, p_mul = 1;
	for (size_t i = 0; i <= 100; i++) {
		std::cout << p_mul << ", ";
		p_mul *= p;
	} */

	return 0;
}