package main

import (
	"fmt"
	"os"

	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "outline: %v\n", err)
		os.Exit(1)
	}
	elems := nElements(map[string]int{}, doc)
	for elem, count := range elems {
		fmt.Printf("%s\t%d\n", elem, count)
	}
}

func nElements(elems map[string]int, n *html.Node) map[string]int {
	if n.Type == html.ElementNode {
		elems[n.Data]++
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		elems = nElements(elems, c)
	}
	return elems
}
