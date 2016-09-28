package main

import (
	"bytes"
	"fmt"
	"strings"
)

func comma(s string) string {
	var buf bytes.Buffer
	if s != "" && s[0] == '-' {
		buf.WriteByte(s[0])
		s = s[1:]
	}
	var fraction string
	if idx := strings.Index(s, "."); idx != -1 {
		fraction = s[idx:]
		s = s[:idx]
	}
	for i := len(s) % 3; i <= len(s); i += 3 {
		if i == 0 {
			continue
		}
		j := i - 3
		if j < 0 {
			j = 0
		}
		if j > 0 {
			buf.WriteByte(',')
		}
		buf.WriteString(s[j:i])
	}
	buf.WriteString(fraction)
	return buf.String()
}

func main() {
	fmt.Println(comma("123456"))
	fmt.Println(comma("1234567"))
	fmt.Println(comma("12345678"))
	fmt.Println(comma("-123456"))
	fmt.Println(comma("-1234567"))
	fmt.Println(comma("-12345678"))
	fmt.Println(comma("123456.1234"))
	fmt.Println(comma("1234567.12345"))
	fmt.Println(comma("12345678.123456"))
	fmt.Println(comma("-123456.1234"))
	fmt.Println(comma("-1234567.12345"))
	fmt.Println(comma("-12345678.123456"))
}
