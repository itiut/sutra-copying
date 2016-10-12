package main

import (
	"flag"
	"fmt"

	"github.com/itiut/sutra-copying/the-go-programming-language/c07/tempconv"
)

var temp = tempconv.CelsiusFlag("temp", 20.0, "the temperature")

func main() {
	flag.Parse()
	fmt.Println(*temp)
}
