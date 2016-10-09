package main

import (
	"fmt"
	"regexp"
	"strings"
)

var r = regexp.MustCompile(`\$[[:alnum:]]+`)

func main() {
	fmt.Println(expand("$abc", add1))
	fmt.Println(expand("123 $abc 456", add1))
	fmt.Println(expand("123 $abc123-abc 456", add1))
}

func expand(s string, f func(string) string) string {
	repl := func(v string) string {
		return f(v[1:])
	}
	return r.ReplaceAllStringFunc(s, repl)
}

func add1(s string) string {
	return strings.Map(func(r rune) rune { return r + 1 }, s)
}
