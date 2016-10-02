package main

import (
	"bufio"
	"crypto/sha256"
	"crypto/sha512"
	"flag"
	"fmt"
	"os"
)

var bit = flag.Int("b", 256, "sha bit length: one of 256, 384, or 512")

func main() {
	flag.Parse()
	scanner := bufio.NewScanner(os.Stdout)
	for scanner.Scan() {
		line := scanner.Text()
		switch *bit {
		case 256:
			fmt.Printf("%x\n", sha256.Sum256([]byte(line)))
		case 384:
			fmt.Printf("%x\n", sha512.Sum384([]byte(line)))
		case 512:
			fmt.Printf("%x\n", sha512.Sum512([]byte(line)))
		default:
			fmt.Fprintln(os.Stderr, "sha bit length must be one of 256, 384, or 512")
			os.Exit(1)
		}
	}
}
