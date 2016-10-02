package main

import (
	"bytes"
	"fmt"
	"unicode"
)

func main() {
	s := " aiu    eo \t kakiku    \ti \naab\r"
	fmt.Printf("%q\n", squashSpaces(s))
}

func squashSpaces(s string) string {
	var buf bytes.Buffer
	isSpace := false
	for _, r := range s {
		if unicode.IsSpace(r) {
			isSpace = true
		} else {
			if isSpace {
				buf.WriteRune(' ')
				isSpace = false
			}
			buf.WriteRune(r)
		}
	}
	if isSpace {
		buf.WriteRune(' ')
	}
	return buf.String()
}
