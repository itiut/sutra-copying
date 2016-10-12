package main

import (
	"bytes"
	"fmt"
)

type tree struct {
	value       int
	left, right *tree
}

func (t *tree) String() string {
	if t == nil {
		return ""
	}
	var buf bytes.Buffer
	buf.WriteRune('[')
	t.traverse(func(v int) {
		if buf.Len() > 1 {
			buf.WriteRune(' ')
		}
		buf.WriteString(fmt.Sprint(v))
	})
	buf.WriteRune(']')
	return buf.String()
}

func (t *tree) traverse(valueFunc func(int)) {
	if t == nil {
		return
	}
	t.left.traverse(valueFunc)
	valueFunc(t.value)
	t.right.traverse(valueFunc)
}

func main() {
	values := []int{6, 3, 4, 2, 5, 7, 1, 9, 0}
	fmt.Println(values)
	Sort(values)
	fmt.Println(values)
}

func Sort(values []int) {
	var root *tree
	for _, v := range values {
		root = add(root, v)
	}
	fmt.Println(root)
	appendValues(values[:0], root)
}

func appendValues(values []int, t *tree) []int {
	if t != nil {
		values = appendValues(values, t.left)
		values = append(values, t.value)
		values = appendValues(values, t.right)
	}
	return values
}

func add(t *tree, value int) *tree {
	if t == nil {
		t = new(tree)
		t.value = value
		return t
	}
	if value < t.value {
		t.left = add(t.left, value)
	} else {
		t.right = add(t.right, value)
	}
	return t
}
