package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"unicode"
)

func main() {
	nLetters := 0
	nDigits := 0
	nOthers := 0
	invalid := 0

	in := bufio.NewReader(os.Stdin)
	for {
		r, n, err := in.ReadRune()
		if err == io.EOF {
			break
		}
		if err != nil {
			fmt.Fprintf(os.Stderr, "charcount: %v\n", err)
			os.Exit(1)
		}
		if r == unicode.ReplacementChar && n == 1 {
			invalid++
			continue
		}
		switch {
		case unicode.IsLetter(r):
			nLetters++
		case unicode.IsDigit(r):
			nDigits++
		default:
			nOthers++
		}
	}
	fmt.Printf("letters\t%d\n", nLetters)
	fmt.Printf("digits\t%d\n", nDigits)
	fmt.Printf("others\t%d\n", nOthers)

	if invalid > 0 {
		fmt.Printf("\n%d invalid UTF-8 characters\n", invalid)
	}
}
