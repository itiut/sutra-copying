package main

import (
	"encoding/xml"
	"fmt"
	"io"
	"os"
	"strings"
)

type Node interface{}

type CharData string

type Element struct {
	Type     xml.Name
	Attr     []xml.Attr
	Children []Node
}

func main() {
	decoder := xml.NewDecoder(os.Stdin)
	nodes := createTree(decoder)
	printTree(&nodes[0], 0)
}

func createTree(decoder *xml.Decoder) []Node {
	var nodes []Node
	for {
		token, err := decoder.Token()
		if err == io.EOF {
			return nodes
		} else if err != nil {
			fmt.Fprintf(os.Stderr, "ex7-18: %v\n", err)
			os.Exit(1)
		}

		switch token := token.(type) {
		case xml.StartElement:
			children := createTree(decoder)
			elem := Element{token.Name, token.Attr, children}
			nodes = append(nodes, elem)
		case xml.EndElement:
			return nodes
		case xml.CharData:
			if data := strings.TrimSpace(string(token)); len(data) > 0 {
				nodes = append(nodes, CharData(data))
			}
		}
	}
}

func printTree(node *Node, depth int) {
	switch node := (*node).(type) {
	case Element:
		fmt.Printf("%*s%s\n", depth*2, "", node.Type)
		for _, child := range node.Children {
			printTree(&child, depth+1)
		}
	case CharData:
		fmt.Printf("%*s%s\n", depth*2, "", node)
	}
}
