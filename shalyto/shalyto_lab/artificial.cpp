#include <iostream>

int main() {
   freopen("artificial.in", "r", stdin);
   freopen("artificial.out", "w", stdout);

   size_t n;
   std::cin >> n;

   switch (n) {
   case 1: std::cout << "2 1 R M\n3 3 M M\n3 4 R M\n2 2 L M"; break;
   case 2: std::cout << "1 1 R M"; break;
   case 3: std::cout << "3 3 R M\n3 3 L M\n2 1 M M";break;
   case 4: std::cout << "4 4 R M\n4 2 L M\n1 2 M M\n3 4 M M";break;
   case 5: std::cout << "3 2 M M\n1 1 R M\n2 3 M L";break;
   case 6: std::cout << "4 3 M M\n5 1 L M\n2 5 M M\n3 1 R M\n2 1 M M";break;
   case 7: std::cout << "2 2 L M\n2 4 R M\n2 4 M M\n1 3 M M";break;
   case 8: std::cout << "2 5 M M\n1 1 R M\n2 5 R M\n3 3 R M\n4 5 M M";break;
   case 9: std::cout << "5 3 R M\n1 3 M M\n6 4 M M\n6 2 L M\n4 4 L M\n2 1 R M";break;
   case 10: std::cout << "3 4 R M\n6 1 R M\n2 5 R M\n5 1 R M\n6 2 L M\n1 1 M M";break;
   }
   return 0;
}
