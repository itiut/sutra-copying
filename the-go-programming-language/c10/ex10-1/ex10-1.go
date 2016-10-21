package main

import (
	"flag"
	"fmt"
	"image"
	"image/gif"
	"image/jpeg"
	"image/png"
	"io"
	"os"
)

var format = flag.String("format", "jpg", "output format: gif, jpg (jpeg), or png")

func main() {
	flag.Parse()
	if err := convert(os.Stdin, os.Stdout, *format); err != nil {
		fmt.Fprintf(os.Stderr, "ex10-1: %v\n", err)
		os.Exit(1)
	}
}

func convert(in io.Reader, out io.Writer, format string) error {
	img, kind, err := image.Decode(in)
	if err != nil {
		return err
	}
	fmt.Fprintln(os.Stderr, "Impur format = ", kind)
	switch format {
	case "gif":
		return gif.Encode(out, img, &gif.Options{NumColors: 256})
	case "jpg", "jpeg":
		return jpeg.Encode(out, img, &jpeg.Options{Quality: 95})
	case "png":
		return png.Encode(out, img)
	default:
		return fmt.Errorf("format must be one of gif, jpg (jpeg), or png but is %q", format)
	}
}
