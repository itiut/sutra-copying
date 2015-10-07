package main

import (
	"golang.org/x/tour/wc"
	"strings"
	"unicode"
)

func WordCount(s string) map[string]int {
	m := make(map[string]int)
	for _, v := range strings.FieldsFunc(s, unicode.IsSpace) {
		m[v]++
	}
	return m
}

func main() {
	wc.Test(WordCount)
}
