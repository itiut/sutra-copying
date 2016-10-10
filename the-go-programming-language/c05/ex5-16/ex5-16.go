package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(join(",", "a", "b", "c"))
}

func join(sep string, ss ...string) string {
	var buf bytes.Buffer
	for i, s := range ss {
		if i > 0 {
			buf.WriteString(sep)
		}
		buf.WriteString(s)
	}
	return buf.String()
}
