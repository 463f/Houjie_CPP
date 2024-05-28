#include "String.h"

int main() {
  String s1("hello");
  String s2("world");

  String s3(s2);
  std::cout << s3 << std::endl;

  s3 = s1;
  std::cout << s3 << std::endl;
  std::cout << s2 << std::endl;
  std::cout << s1 << std::endl;

  return 0;
}
