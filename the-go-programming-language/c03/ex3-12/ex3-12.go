package main

import "fmt"

func isAnagrams(s1, s2 string) bool {
	if len(s1) != len(s2) {
		return false
	}
	s1Rules, s2Rules := make(map[rune]int), make(map[rune]int)
	for _, c := range s1 {
		s1Rules[c]++
	}
	for _, c := range s2 {
		s2Rules[c]++
	}
	for c, n1 := range s1Rules {
		n2, ok := s2Rules[c]
		if !ok {
			return false
		}
		if n1 != n2 {
			return false
		}
	}
	return true
}

func main() {
	fmt.Println(isAnagrams("aiueo", "ieuoa"))
	fmt.Println(isAnagrams("aiueo", "ieuoaa"))
	fmt.Println(isAnagrams("aiueo", "ieuok"))
	fmt.Println(isAnagrams("aiueo", "ieuoka"))
	fmt.Println(isAnagrams("aiueo", "ieuo"))
}
