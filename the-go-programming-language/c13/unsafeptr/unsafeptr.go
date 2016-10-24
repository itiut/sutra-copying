package main

import (
	"fmt"
	"math"
	"unsafe"
)

func main() {
	fmt.Printf("%#016x\n", math.Float64bits(1.0))

	var x struct {
		a bool
		b int16
		c []int
	}
	pb := (*int16)(unsafe.Pointer(uintptr(unsafe.Pointer(&x)) + unsafe.Offsetof(x.b)))
	*pb = 42
	fmt.Println(x.b)
}
