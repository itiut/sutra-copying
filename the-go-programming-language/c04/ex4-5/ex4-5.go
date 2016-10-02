package main

import "fmt"

func main() {
	ss := []string{"a", "b", "b", "b", "c", "c", "b", "d", "a"}
	ss = dedupAdjacents(ss)
	fmt.Println(ss)
}

func dedupAdjacents(ss []string) []string {
	i := 0
	for j := 1; j < len(ss); j++ {
		if ss[j] != ss[i] {
			i++
			ss[i] = ss[j]
		}
	}
	return ss[:i+1]
}
