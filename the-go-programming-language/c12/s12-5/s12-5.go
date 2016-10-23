package main

import (
	"fmt"
	"os"
	"reflect"
)

func main() {
	f1()
	f2()
	f3()
}

func f1() {
	x := 2
	a := reflect.ValueOf(2)
	b := reflect.ValueOf(x)
	c := reflect.ValueOf(&x)
	d := c.Elem()
	fmt.Println(a.CanAddr())
	fmt.Println(b.CanAddr())
	fmt.Println(c.CanAddr())
	fmt.Println(d.CanAddr())
}

func f2() {
	x := 2
	d := reflect.ValueOf(&x).Elem()
	px := d.Addr().Interface().(*int)
	*px = 3
	fmt.Println(x)

	d.Set(reflect.ValueOf(4))
	fmt.Println(x)

	d.SetInt(5)
	fmt.Println(x)
}

func f3() {
	stdout := reflect.ValueOf(os.Stdout).Elem()
	fmt.Println(stdout.Type())
	fd := stdout.FieldByName("fd")
	fmt.Println(fd.Int())
	fmt.Println(fd.CanAddr(), fd.CanSet())
}
