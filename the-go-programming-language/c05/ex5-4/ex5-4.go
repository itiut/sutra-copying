package main

import (
	"fmt"
	"os"

	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "findlinks1: %v\n", err)
		os.Exit(1)
	}
	for _, link := range visit(nil, doc) {
		fmt.Println(link)
	}
}

func visit(links []string, n *html.Node) []string {
	if n.Type == html.ElementNode {
		if n.Data == "a" || n.Data == "link" {
			links = appendLinks(links, n, "href")
		} else if n.Data == "img" || n.Data == "script" {
			links = appendLinks(links, n, "src")
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		links = visit(links, c)
	}
	return links
}

func appendLinks(links []string, n *html.Node, key string) []string {
	for _, a := range n.Attr {
		if a.Key == key {
			links = append(links, a.Val)
		}
	}
	return links
}
