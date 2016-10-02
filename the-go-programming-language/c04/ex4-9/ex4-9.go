package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	counts := make(map[string]int)
	input := bufio.NewScanner(os.Stdin)
	input.Split(bufio.ScanWords)
	for input.Scan() {
		word := input.Text()
		counts[word]++
	}
	for word, count := range counts {
		fmt.Printf("%d\t%s\n", count, word)
	}
}
