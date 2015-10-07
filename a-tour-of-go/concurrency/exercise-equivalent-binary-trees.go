package main

import (
	"fmt"
	"golang.org/x/tour/tree"
)

func RecWalk(t *tree.Tree, ch chan int) {
	if t == nil {
		return
	}
	RecWalk(t.Left, ch)
	ch <- t.Value
	RecWalk(t.Right, ch)
}

func Walk(t *tree.Tree, ch chan int) {
	RecWalk(t, ch)
	close(ch)
}

func Same(t1, t2 *tree.Tree) bool {
	ch1 := make(chan int)
	ch2 := make(chan int)
	go Walk(t1, ch1)
	go Walk(t2, ch2)
	for v1 := range ch1 {
		if v1 != <-ch2 {
			return false
		}
	}
	return true
}

func main() {
	t := Same(tree.New(1), tree.New(1))
	f := Same(tree.New(1), tree.New(2))
	fmt.Println(t, f)
}
