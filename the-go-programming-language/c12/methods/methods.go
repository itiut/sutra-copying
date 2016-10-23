package main

import (
	"fmt"
	"reflect"
	"strings"
	"time"
)

func main() {
	Print(time.Hour)
	fmt.Println()
	Print(new(strings.Replacer))
}

func Print(x interface{}) {
	v := reflect.ValueOf(x)
	t := v.Type()
	fmt.Printf("type %s\n", t)

	for i := 0; i < v.NumMethod(); i++ {
		methType := v.Method(i).Type()
		fmt.Printf("func (%s) %s%s\n", t, t.Method(i).Name, strings.TrimPrefix(methType.String(), "func"))
	}
}
