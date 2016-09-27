package main

func PopCount(x uint64) int {
	count := 0
	for ; x > 0; x &= x - 1 {
		count++
	}
	return count
}
