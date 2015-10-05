package main

import (
	"fmt"
	"math"
)

func Sqrt(x float64) float64 {
	const EPS = 1e-10
	z := 1.0
	for i := 0; i < 1000; i++ {
		zn := z - ((z*z)-x)/(2*z)
		if math.Abs(zn-z) < EPS {
			return zn
		}
		z = zn
	}
	return z
}

func main() {
	fmt.Println(Sqrt(2))
}
