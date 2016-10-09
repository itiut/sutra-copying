package main

import (
	"fmt"
	"net/http"
	"os"
	"strings"

	"golang.org/x/net/html"
)

func main() {
	for _, url := range os.Args[1:] {
		words, images, err := CountWorsAndImages(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "ex5-5: %v\n", err)
			continue
		}
		fmt.Printf("%s: %d words, %d images\n", url, words, images)
	}
}

func CountWorsAndImages(url string) (words, images int, err error) {
	resp, err := http.Get(url)
	if err != nil {
		return
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		err = fmt.Errorf("parsing HTML: %s", err)
		return
	}
	words, images = countWordsAndImages(doc)
	return
}

func countWordsAndImages(n *html.Node) (words, images int) {
	if n.Type == html.ElementNode {
		if n.Data == "script" || n.Data == "style" {
			return
		}
		if n.Data == "img" {
			images = 1
			return
		}
	} else if n.Type == html.TextNode {
		words = len(strings.Fields(n.Data))
		return
	}

	for c := n.FirstChild; c != nil; c = c.NextSibling {
		_words, _images := countWordsAndImages(c)
		words += _words
		images += _images
	}
	return
}
