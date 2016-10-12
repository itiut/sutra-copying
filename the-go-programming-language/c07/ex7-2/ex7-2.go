package main

import (
	"fmt"
	"io"
	"os"
)

type CountingWriter struct {
	w       io.Writer
	counter int64
}

func (cw *CountingWriter) Write(p []byte) (int, error) {
	n, err := cw.w.Write(p)
	cw.counter += int64(n)
	return n, err
}

func NewCountingWriter(w io.Writer) (io.Writer, *int64) {
	cw := CountingWriter{w, 0}
	return &cw, &cw.counter
}

func main() {
	cw, counter := NewCountingWriter(os.Stdout)
	fmt.Fprintln(cw, "aiueo")
	fmt.Println(*counter)
	fmt.Fprintln(cw, "kakikukeko")
	fmt.Println(*counter)
}
