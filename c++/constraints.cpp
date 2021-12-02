#include <iostream>
#include <vector>

using namespace std;

template <class T>
int compute_length(T *value) {
  return value->size();
  // return value->length();
}

void test2() {
  string s = "test";
  vector<int> vec;

  compute_length(&s);
  compute_length(&vec);
}

int main(int argc, char const *argv[]) {
  test2();
  return 0;
}
