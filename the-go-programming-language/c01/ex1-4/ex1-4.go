package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	counts := make(map[string]int)
	for _, filename := range os.Args[1:] {
		f, err := os.Open(filename)
		if err != nil {
			fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
			continue
		}
		countLines(f, counts)
		f.Close()
	}
	for data, n := range counts {
		if n > 1 {
			s := strings.Split(data, "\n")
			filename, line := s[0], s[1]
			fmt.Printf("%s:%d\t%s\n", filename, n, line)
		}
	}
}

func countLines(f *os.File, counts map[string]int) {
	input := bufio.NewScanner(f)
	for input.Scan() {
		counts[fmt.Sprintf("%s\n%s", f.Name(), input.Text())]++
	}
}
