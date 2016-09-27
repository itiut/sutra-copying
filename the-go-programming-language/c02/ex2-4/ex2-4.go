package popcount

func PopCount(x uint64) int {
	count := 0
	for ; x > 0; x >>= 1 {
		count += int(x & 1)
	}
	return count
}
