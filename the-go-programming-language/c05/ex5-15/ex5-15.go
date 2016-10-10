package main

import "fmt"

func main() {
	fmt.Println(max(0))
	fmt.Println(max(10, 4, 2, 6, 8, 0))
	fmt.Println(min(0))
	fmt.Println(min(10, 4, 2, 6, 8, 0))
}

func max(v0 int, values ...int) int {
	_max := v0
	for _, value := range values {
		if value > _max {
			_max = value
		}
	}
	return _max
}

func min(v0 int, values ...int) int {
	_min := v0
	for _, value := range values {
		if value < _min {
			_min = value
		}
	}
	return _min
}
