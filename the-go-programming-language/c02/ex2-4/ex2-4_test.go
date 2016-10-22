package popcount

import "testing"

func benchmark(b *testing.B, x uint64) {
	for i := 0; i < b.N; i++ {
		PopCount(x)
	}
}

func BenchmarkPopCount1k(b *testing.B) { benchmark(b, 1000) }
func BenchmarkPopCount1M(b *testing.B) { benchmark(b, 1000000) }
func BenchmarkPopCount1G(b *testing.B) { benchmark(b, 1000000000) }
func BenchmarkPopCount1T(b *testing.B) { benchmark(b, 1000000000000) }
