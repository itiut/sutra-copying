package main

import "fmt"

func main() {
	s := []int{0, 1, 2, 3, 4, 5}
	rotate(s, 2)
	fmt.Println(s)

	rotate(s, 3)
	fmt.Println(s)
}

func rotate(s []int, pos int) {
	reverse(s[pos:])
	reverse(s[:pos])
	reverse(s)
}

func reverse(s []int) {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
}
