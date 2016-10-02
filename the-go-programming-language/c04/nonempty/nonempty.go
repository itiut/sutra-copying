package main

import "fmt"

func main() {
	data := []string{"one", "", "three"}
	fmt.Printf("%q\n", nonempty(data))
	fmt.Printf("%q\n", data)

	data = []string{"1", "", "3"}
	fmt.Printf("%q\n", nonempty2(data))
	fmt.Printf("%q\n", data)
}

func nonempty(ss []string) []string {
	i := 0
	for _, s := range ss {
		if s != "" {
			ss[i] = s
			i++
		}
	}
	return ss[:i]
}

func nonempty2(ss []string) []string {
	out := ss[:0]
	for _, s := range ss {
		if s != "" {
			out = append(out, s)
		}
	}
	return out
}
