package main

import (
	"fmt"
	"os"
	"strings"

	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "outline: %v\n", err)
		os.Exit(1)
	}
	text(doc)
}

func text(n *html.Node) {
	if n.Type == html.ElementNode && (n.Data == "script" || n.Data == "style") {
		return
	}
	if n.Type == html.TextNode {
		if line := strings.TrimSpace(n.Data); line != "" {
			fmt.Println(line)
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		text(c)
	}
}
