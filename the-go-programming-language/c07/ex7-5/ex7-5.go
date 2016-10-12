package main

import (
	"io"
	"log"
	"os"
	"strings"
)

type LimitReader struct {
	r     io.Reader
	limit int64
}

func (lr *LimitReader) Read(p []byte) (int, error) {
	if lr.limit <= 0 {
		return 0, io.EOF
	}
	if int64(len(p)) > lr.limit {
		p = p[0:lr.limit]
	}
	n, err := lr.r.Read(p)
	lr.limit -= int64(n)
	return n, err
}

func NewLimitReader(r io.Reader, n int64) io.Reader {
	return &LimitReader{r, n}
}

func main() {
	s := "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
	lr := NewLimitReader(strings.NewReader(s), 10)
	if _, err := io.Copy(os.Stdout, lr); err != nil {
		log.Fatal(err)
	}
}
