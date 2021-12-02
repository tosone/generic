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
	// test2()
}
