package main

import (
	"flag"
	"fmt"
	"log"

	"github.com/itiut/sutra-copying/the-go-programming-language/c05/links"
)

var depth = flag.Int("depth", 3, "link depth")

func main() {
	flag.Parse()
	worklist := make(chan []string)

	go func() { worklist <- flag.Args() }()

	seen := make(map[string]bool)
	for ; *depth >= 0; *depth-- {
		list := <-worklist
		for _, link := range list {
			if !seen[link] {
				seen[link] = true
				go func(link string) {
					worklist <- crawl(link)
				}(link)
			}
		}
	}
}

var tokens = make(chan struct{}, 20)

func crawl(url string) []string {
	fmt.Println(url)
	tokens <- struct{}{}
	list, err := links.Extract(url)
	<-tokens
	if err != nil {
		log.Print(err)
	}
	return list
}
