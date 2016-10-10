package main

import "golang.org/x/net/html"

func ElementsByTagName(doc *html.Node, names ...string) []*html.Node {
	elems := []*html.Node{}
	if doc.Type == html.ElementNode {
		for _, name := range names {
			if doc.Data == name {
				elems = append(elems, doc)
				break
			}
		}
	}
	for c := doc.FirstChild; c != nil; c = c.NextSibling {
		elems = append(elems, ElementsByTagName(c, names...)...)
	}
	return elems
}
