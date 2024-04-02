#include <iostream>

struct SmartStr {
  std::string str;

  SmartStr(const std::string& s) : str(s) {}

  void print() const {
    std::cout << str << std::endl;
  }
};

int main() {
  SmartStr obj("Hello, World!");
  SmartStr *arr =new SmartStr[10];
  obj.print();

  return 0;
}