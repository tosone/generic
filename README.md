# 泛型

泛型程序设计（generic programming）是程序设计语言的一种风格或范式。泛型允许程序员在**强类型程序设计语言**中编写代码时使用一些以后才指定的类型，在实例化时作为参数指明这些类型。

个人理解泛型就是研究如何传递参数类型的，使语言可以在编译器将对象的多态展开。

泛型并不是任何类型都能传，不是 (void *) 一梭子搞，泛型也有类型约束。

```c
#include <stdint.h>
#include <stdio.h>

int cmpfunc(const void *a, const void *b) {
  return (*(signed int *)b > *(signed int *)a) ? 1 : 0;
}

int main(int argc, char const *argv[]) {
  int8_t a = 5;
  int8_t b = 5;
  printf("%d\n", cmpfunc(&a, &b)); // 输出结果会是什么?
  return 0;
}
```

上边这种 (void *) 转换成 (unsigned int)，在不同的语言是有一些性能损失，属于运行时的 "参数多态"。

泛型主要是在编译器完成类型检查和签名生成，不同语言中也有不同的实现，这也并不是绝对的。

泛型的应用对象上主要有三种：方法，类，接口。不同语言对于这三个对象实现并不完全一样，有些可能就完全没有类或者接口等等。

## C

C/C++ playground: [https://www.programiz.com/cpp-programming/online-compiler/](https://www.programiz.com/cpp-programming/online-compiler/)

C 语言中有泛型么？其实是有的。

```c
#include <math.h> // sqrt cbrtl cbrt cbrtf
#include <stdio.h>

#include <tgmath.h> // sqrt

// 自定义泛型扩展
#define cbrt(X) _Generic((X), long double : cbrtl, default : cbrt, float : cbrtf)(X)

void test1() {
  double x = 8.0;
  const float y = 3.375;
  printf("cbrt(8.0) = %f\n", cbrt(x));
  printf("cbrtf(3.375) = %f\n", cbrt(y));
}

// 使用tgmath.h中的宏定义泛型函数
void test2() {
  int i = 2;
  printf("sqrt(2) = %f\n", sqrt(i));

  float f = 0.5;
  printf("sin(0.5f) = %f\n", sin(f));

  float complex dc = 1 + 0.5 * I;
  float complex z = sqrt(dc);
  printf("sqrt(1 + 0.5i) = %f+%fi\n", creal(z), cimag(z));
}

int main(void) {
  test1();
  test2();
}
```

## C++

C++ 对泛型的实现是 template，template 在 C++ 内被称为是[图灵完备](http://web.archive.org/web/20050118195822/http://osl.iu.edu/~tveldhui/papers/2003/turing.pdf)的，也就是是程序在编译过程中可以完成任何可以在运行时进行的任务，使得 template 成为元编程中很重要的一个东西，元编程其实并不是 template 的目标，只是他可以完成这个目标。

元编程就是可以操作代码行为的程序，就不做展开了。

```cpp
// template <class myType>
// myType GetMax (myType a, myType b) {
// return (a>b?a:b);
// }

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
//        static_assert(std::is_base_of<BaseClass, T>::value, "type parameter of this class must derive from BaseClass");
//    }
// }

#include <iostream>
#include <vector>

using namespace std;

template <class T>
int compute_length(T *value)
{
    return value->size();
    // return value->length();
}

int main() {
    std::cout << "Hello world!";

    string s = "test";
    vector<int> vec;

    compute_length(&s);
    compute_length(&vec);

    return 0;
}
```

## Rust

rust 这种语言确实是入门稍微陡峭一点，周末的时间尝试为 rust 写一个 containerd 的 SDK，‣，如果在 C++ 中有了解过一点点右值，右值引用，引用计数，完美转发，再将这些概念映射到 rust 中的移动语义，借用，智能指针等等这些概念上。前期入门的时候，总会遇见这种问题，为什么我的代码不能编译？

总会出现这样的错误，图来自于公司的 rust 群组：

![Untitled](%E6%B3%9B%E5%9E%8B%20d62cb84cdfce4375afaff5b4baa4634b/Untitled.png)

```rust
// struct Point<T> {
//     x: T,
//     y: T,
// }

struct Foo<T> {
    text: T,
}

impl<T> Foo<T> {
    fn value(&self) -> &T {
        &self.text
    }
}

fn main() {
    let x = Foo { text: 3i32 };

    println!("output: {}", x.value());
}
```

```rust
struct Struct;

trait Trait<T> {
    fn method(&self) -> T;
}

impl Trait<u8> for Struct {
    fn method(&self) -> u8 {
        16
    }
}

impl Trait<String> for Struct {
    fn method(&self) -> String {
        "hello".to_string()
    }
}

fn main() {
    let s = Struct;
    let a: u8 = s.method();
    let b: String = s.method();
    println!("a={}, b={}", a, b);
}
```

相对来说 Rust 的泛型没有像 C++ 那样无拘无束，更符合泛型最原本的样子。

## Typescript

这个语言稍微有意思一些，立足于 JavaScript 和 C# 之上。这种语言（ts 可以被称为一门语言）既有一些弱类型的特性也有一些也有一些强类型的特性，某些地方处于强弱类型语言的边缘，所以有人说 Typescript 可以用 any 一把梭。

```tsx
interface ITask {
    name: string;

    start?: boolean;

    repeat?: (...args: any[]) => boolean | number; // 这个返回值算是泛型么？

    while?: (...args: any[]) => boolean;

    if?: (...args: any[]) => boolean;
    else?: (...args: any[]) => Promise<any>;

    func?: (...args: any[]) => Promise<any>; // any 算是泛型么？
    // any 在 ts 中不检查任何相关变量类型和相关方法的

    externalFunc?: {
        headers: Map<string, string>;
        method: string;
        url: string;
    };

    requires?: string[];
}

function test<Type extends Array<Number>>(arg: Type): Number {
    return arg.length;
}

console.log(test([1, 2, 3]));

// class GenericNumber<NumType> {
//     zeroValue: NumType;
//     add: (x: NumType, y: NumType) => NumType;
// }

// ts-node ts/generic.ts
```

## Go

在目前所有语言中的语法难度上 Go 相对来说是最简洁最简单的，这里看 [grammars](https://github.com/antlr/grammars-v4/blob/master/golang/GoLexer.g4) 仓库中对 go 做的词法分析，关键词和语法逻辑很少，比 C 还要少上一些，因为 Go 本身从语法规则上就杜绝你写那种神仙都看不懂的代码（比如 if else loop 三元表达式，奇怪的换行规则，分号）。在这个词法分析里 vb 竟然是词法相对来说比较复杂的语言。

这么简洁的 Go 中为什么需要泛型呢？[https://go.dev/blog/why-generics](https://go.dev/blog/why-generics)

可以更好地抽象代码的逻辑，不是目前的 interface 不能更好的抽象，只是泛型会更加好的抽象，并且在一些函数参数需要多态化的时候，会有更加好的表现，不论从代码逻辑还是性能上。（参数需要多态的时候我们总是传入一些 interface 然后 switch type，这其实会有一些性能损失的相对泛型来说，泛型可以在编译期间就可以将多态展开）。

Go 泛型最新的 proposal：[https://go.googlesource.com/proposal/+/refs/heads/master/design/43651-type-parameters.md](https://go.googlesource.com/proposal/+/refs/heads/master/design/43651-type-parameters.md)

Go 即将在 2022.2 发布新的 1.18 版本，带来完整的泛型体验。目前在 go 的源码中已经有关于反省的一些标准包了 [https://github.com/golang/go/blob/master/src/constraints/constraints.go](https://github.com/golang/go/blob/master/src/constraints/constraints.go)，并且还添加了两个关键字 any comparable。

any: 跟 typescript 里的一样代表任意类型，在编译期间不做任何的约束检查。

comparable: 在编译期间会做自动的类型检查，判断类型是否可以用作比较，但是目前这个东西实现的还有问题。

除此之外 go 在编译期间会做方法检查。

目前在 exp 的仓库里已经有两个包实现了泛型相关的标准库。

[https://github.com/golang/exp/blob/master/slices/slices.go](https://github.com/golang/exp/blob/master/slices/slices.go)

[https://github.com/golang/exp/blob/master/maps/maps.go](https://github.com/golang/exp/blob/master/maps/maps.go)

泛型为什么是中括号而不是尖括号？

以便于更好的做词法解释。

[https://go.googlesource.com/proposal/+/refs/heads/master/design/43651-type-parameters.md#why-not-use-the-syntax-like-c_and-java](https://go.googlesource.com/proposal/+/refs/heads/master/design/43651-type-parameters.md#why-not-use-the-syntax-like-c_and-java)

什么时候用 Go 的泛型呢？

泛型的缺点？

目前尚不成熟，可以明确的一点是编译时间会变长，增加 20%。

```go
package main

import (
	"fmt"
	// "reflect"

	"golang.org/x/exp/slices"
)

func Equal[T comparable](v1, v2 T) bool {
	// if !reflect.TypeOf(v1).Comparable() {
	// 	return false
	// }
	// if !reflect.TypeOf(v2).Comparable() {
	// 	return false
	// }
	return v1 == v2
}

func test1() {
	var a = []int{1, 2, 3, 4, 5}
	var b = []int{6, 7, 8, 9, 10}

	fmt.Printf("test1: %v\n", slices.Equal(a, b))
}

func test2() {
	var v1 = interface{}(func() {})
	var v2 = interface{}(func() {})
	fmt.Println(Equal(v1, v2))
}

func main() {
	test1()
	test2()
}
```
