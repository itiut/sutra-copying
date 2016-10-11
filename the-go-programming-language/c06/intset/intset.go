package main

import (
	"bytes"
	"fmt"
)

const bitsize = 32 << (^uint(0) >> 63)

type IntSet struct {
	words []uint64
}

func (s *IntSet) Has(x int) bool {
	word, bit := x/64, uint(x%64)
	return word < len(s.words) && s.words[word]&(1<<bit) != 0
}

func (s *IntSet) Add(x int) {
	word, bit := x/64, uint(x%64)
	for word >= len(s.words) {
		s.words = append(s.words, 0)
	}
	s.words[word] |= 1 << bit
}

func (s *IntSet) String() string {
	var buf bytes.Buffer
	buf.WriteByte('{')
	for i, word := range s.words {
		if word == 0 {
			continue
		}
		for j := 0; j < 64; j++ {
			if word&(1<<uint(j)) != 0 {
				if buf.Len() > len("{") {
					buf.WriteByte(' ')
				}
				fmt.Fprintf(&buf, "%d", 64*i+j)
			}
		}
	}
	buf.WriteByte('}')
	return buf.String()
}

func (s *IntSet) Len() int {
	length := 0
	for _, word := range s.words {
		if word == 0 {
			continue
		}
		for i := 0; i < 64; i++ {
			if word&(1<<uint(i)) != 0 {
				length++
			}
		}
	}
	return length
}

func (s *IntSet) Remove(x int) {
	word, bit := x/64, uint(x%64)
	if word < len(s.words) {
		s.words[word] &^= 1 << bit
	}
}

func (s *IntSet) Clear() {
	s.words = []uint64{}
}

func (s *IntSet) Copy() *IntSet {
	t := IntSet{make([]uint64, len(s.words))}
	copy(t.words, s.words)
	return &t
}

func (s *IntSet) AddAll(values ...int) {
	for _, value := range values {
		s.Add(value)
	}
}

func (s *IntSet) UnionWith(t *IntSet) {
	for i, tword := range t.words {
		if i < len(s.words) {
			s.words[i] |= tword
		} else {
			s.words = append(s.words, tword)
		}
	}
}

func (s *IntSet) IntersectWith(t *IntSet) {
	for i, tword := range t.words {
		if i >= len(s.words) {
			break
		}
		s.words[i] &= tword
	}
}

func (s *IntSet) DifferenceWith(t *IntSet) {
	for i, tword := range t.words {
		if i >= len(s.words) {
			break
		}
		s.words[i] &^= tword
	}
}

func (s *IntSet) SymmetricDifference(t *IntSet) {
	for i, tword := range t.words {
		if i < len(s.words) {
			s.words[i] ^= tword
		} else {
			s.words = append(s.words, tword)
		}
	}
}

func (s *IntSet) Elems() []int {
	elems := []int{}
	for i, word := range s.words {
		if word == 0 {
			continue
		}
		for j := 0; j < 64; j++ {
			if word&(1<<uint(j)) != 0 {
				elems = append(elems, 64*i+j)
			}
		}
	}
	return elems
}

func main() {
	var x, y IntSet
	x.Add(1)
	x.Add(144)
	x.Add(9)
	fmt.Println(x.String())

	y.Add(9)
	y.Add(42)
	fmt.Println(y.String())

	x.UnionWith(&y)
	fmt.Println(x.String())
	fmt.Println(x.Has(9), x.Has(123))

	fmt.Println(&x)
	fmt.Println(x.String())
	fmt.Println(x)

	fmt.Println(x.Len())
	fmt.Println(y.Len())

	x.Remove(42)
	fmt.Println(&x)

	zptr := x.Copy()
	fmt.Println(zptr)
	zptr.Add(25)
	fmt.Println(&x)
	fmt.Println(zptr)

	x.AddAll(11, 22, 33)
	fmt.Println(&x)
}
