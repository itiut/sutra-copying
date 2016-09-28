package main

import (
	"bytes"
	"fmt"
)

func comma(s string) string {
	var buf bytes.Buffer
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
	return buf.String()
}

func main() {
	fmt.Println(comma("123456"))
	fmt.Println(comma("1234567"))
	fmt.Println(comma("12345678"))
	fmt.Println(comma("123456789"))
}
