package main

import "fmt"

func main() {
	s := []byte("012345")
	s = reverse(s)
	fmt.Printf("%s\n", s)

	s = []byte("012345")
	reverse(s[:2])
	reverse(s[2:])
	reverse(s)
	fmt.Printf("%s\n", s)
}

func reverse(s []byte) []byte {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
	return s
}
