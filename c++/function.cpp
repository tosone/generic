#include <iostream>
#include <vector>

using namespace std;

template <typename T>
T GetMax(T a, T b) {
  return a > b ? a : b;
}

void test() {
  cout << GetMax<int>(1, 2) << endl;
  cout << GetMax<int>(2, 1) << endl;
}

// template <class T>
// class mypair {
//    T values [2];
//  public:
//    mypair (T first, T second)
//    {
//      values[0]=first; values[1]=second;
//    }
// };

// #include <type_traits>
// template<typename T>
// class YourClass {
//    YourClass() {
//        // Compile-time check
//        static_assert(std::is_base_of<BaseClass, T>::value, "type parameter of
//        this class must derive from BaseClass");
//    }
// }

// 泛型检查
// template <class T>
// int compute_length(T *value) {
//   return value->size();
//   // return value->length();
// }

// void test2() {
//   string s = "test";
//   vector<int> vec;

//   compute_length(&s);
//   compute_length(&vec);
// }

int main() {
  test();

  return 0;
}
