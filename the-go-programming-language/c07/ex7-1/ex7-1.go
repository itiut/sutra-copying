package main

import (
	"bufio"
	"bytes"
	"fmt"
)

type WordCounter int

func (c *WordCounter) Write(p []byte) (int, error) {
	scanner := bufio.NewScanner(bytes.NewReader(p))
	scanner.Split(bufio.ScanWords)
	count := 0
	for scanner.Scan() {
		count++
	}
	*c += WordCounter(count)
	return len(p), scanner.Err()
}

type LineCounter int

func (c *LineCounter) Write(p []byte) (int, error) {
	scanner := bufio.NewScanner(bytes.NewReader(p))
	count := 0
	for scanner.Scan() {
		count++
	}
	*c += LineCounter(count)
	return len(p), scanner.Err()
}

func main() {
	var wc WordCounter
	fmt.Fprint(&wc, "aa bb cc dd\nee ff")
	fmt.Println(wc)

	var lc LineCounter
	fmt.Fprint(&lc, "aa bb cc dd\nee ff\n")
	fmt.Println(lc)
}
