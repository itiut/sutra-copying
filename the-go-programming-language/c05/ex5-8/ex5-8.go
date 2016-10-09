package main

import (
	"fmt"
	"net/http"
	"os"

	"golang.org/x/net/html"
)

func main() {
	if len(os.Args) != 3 {
		fmt.Fprintf(os.Stderr, "usage: %s url id\n", os.Args[0])
		os.Exit(1)
	}
	url := os.Args[1]
	id := os.Args[2]
	doc, err := fetchHTML(url)
	if err != nil {
		fmt.Fprintf(os.Stderr, "ex5-8: %v\n", err)
		os.Exit(1)
	}
	elem, ok := ElementById(doc, id)
	if !ok {
		fmt.Fprintf(os.Stderr, "ex5-8: no such id \"%s\"\n", id)
		os.Exit(1)
	}
	fmt.Println(elem)
}

func fetchHTML(url string) (*html.Node, error) {
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return nil, fmt.Errorf("parsing HTML: %s", err)
	}
	return doc, nil
}

func ElementById(doc *html.Node, id string) (*html.Node, bool) {
	isTarget := func(n *html.Node) bool {
		if n.Type == html.ElementNode {
			for _, a := range n.Attr {
				if a.Key == "id" {
					return a.Val == id
				}
			}
		}
		return false
	}
	return forEachNode(doc, isTarget, nil)
}

func forEachNode(n *html.Node, pre, post func(*html.Node) bool) (*html.Node, bool) {
	if pre != nil {
		if ok := pre(n); ok {
			return n, ok
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		if elem, ok := forEachNode(c, pre, post); ok {
			return elem, ok
		}
	}
	if post != nil {
		if ok := post(n); ok {
			return n, ok
		}
	}
	return nil, false
}
