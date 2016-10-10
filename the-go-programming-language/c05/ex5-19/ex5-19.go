package main

import "fmt"

func main() {
	fmt.Println(ret1())
}

func ret1() (result int) {
	type noret struct{}
	defer func() {
		switch p := recover(); p {
		case noret{}:
			result = 1
		default:
			panic(p)
		}
	}()
	panic(noret{})
}
