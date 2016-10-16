package main

import (
	"bytes"
	"encoding/xml"
	"fmt"
	"io"
	"os"
)

type elemStack []xml.StartElement

func main() {
	dec := xml.NewDecoder(os.Stdin)
	var stack elemStack
	for {
		tok, err := dec.Token()
		if err == io.EOF {
			break
		} else if err != nil {
			fmt.Fprintf(os.Stderr, "xmlselect: %v\n", err)
			os.Exit(1)
		}
		switch tok := tok.(type) {
		case xml.StartElement:
			stack = append(stack, tok)
		case xml.EndElement:
			stack = stack[:len(stack)-1]
		case xml.CharData:
			if containsAll(stack, os.Args[1:]) {
				fmt.Printf("%s: %s\n", stack, tok)
			}
		}
	}
}

func containsAll(stack elemStack, y []string) bool {
	for len(y) <= len(stack) {
		if len(y) == 0 {
			return true
		}
		if equal(stack[0], y[0]) {
			y = y[1:]
		}
		stack = stack[1:]
	}
	return false
}

func equal(elem xml.StartElement, selector string) bool {
	if len(selector) == 0 {
		return false
	}
	switch selector[0] {
	case '#':
		// id
		for _, attr := range elem.Attr {
			if attr.Name.Local == "id" {
				return attr.Value == selector[1:]
			}
		}
	case '.':
		// class
		for _, attr := range elem.Attr {
			if attr.Name.Local == "class" {
				return attr.Value == selector[1:]
			}
		}
	default:
		return elem.Name.Local == selector
	}
	return false
}

func (stack elemStack) String() string {
	var buf bytes.Buffer
	for i, elem := range stack {
		if i > 0 {
			buf.WriteRune(' ')
		}
		buf.WriteString(elem.Name.Local)
	}
	return buf.String()
}
