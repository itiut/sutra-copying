package main

import (
	"fmt"
	"strings"
	"time"
)

func main() {
	t0 := time.Now()
	join1()
	t1 := time.Now()
	fmt.Println(t1.Sub(t0))

	t0 = time.Now()
	join2()
	t1 = time.Now()
	fmt.Println(t1.Sub(t0))
}

func join1() {
	s, sep := "", ""
	for i := 0; i < 100000; i++ {
		s += sep + "aiueo"
		sep = " "
	}
}

func join2() {
	var arr [100000]string
	for i := range arr {
		arr[i] = "aiueo"
	}
	strings.Join(arr[:], " ")
}
