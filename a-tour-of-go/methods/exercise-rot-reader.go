package main

import (
	"io"
	"os"
	"strings"
	"unicode"
)

type rot13Reader struct {
	r io.Reader
}

func (r rot13Reader) Read(b []byte) (int, error) {
	n, err := r.r.Read(b)
	if err == nil {
		for i := range b {
			b[i] = rot13(b[i])
		}
	}
	return n, err
}

func rot13(b byte) byte {
	var base byte
	switch {
	case unicode.IsLower(rune(b)):
		base = byte('a')
	case unicode.IsUpper(rune(b)):
		base = byte('A')
	default:
		return b
	}
	return (b-base+13)%26 + base
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
}
