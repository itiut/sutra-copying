package main

import (
	"crypto/sha256"
	"fmt"
)

func main() {
	c1 := sha256.Sum256([]byte("x"))
	c2 := sha256.Sum256([]byte("X"))
	fmt.Printf("%x\n%x\n%t\n%T\n", c1, c2, c1 == c2, c1)
	fmt.Println(DiffPopCount(c1, c2))
}

func DiffPopCount(a, b [32]byte) int {
	count := 0
	for i := range a {
		count += PopCount(a[i] ^ b[i])
	}
	return count
}

func PopCount(b byte) int {
	count := 0
	for ; b > 0; b &= b - 1 {
		count++
	}
	return count
}
