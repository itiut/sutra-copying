package main

import (
	"image"
	"image/color"
	"image/png"
	"io"
	"math/cmplx"
)

func draw(w io.Writer, x, y int) {
	if x < 0 {
		x = -x
	}
	if y < 0 {
		y = -y
	}
	xmin, xmax, ymin, ymax := float64(-x), float64(x), float64(-y), float64(y)
	const (
		width, height = 1024, 1024
	)
	img := image.NewRGBA(image.Rect(0, 0, width, height))
	for py := 0; py < height; py++ {
		y := float64(py)/height*(ymax-ymin) + ymin
		for px := 0; px < width; px++ {
			x := float64(px)/width*(xmax-xmin) + xmin
			z := complex(x, y)
			img.Set(px, py, mandelbrot(z))
		}
	}
	png.Encode(w, img)
}

func mandelbrot(z complex128) color.Color {
	const iterations = 200
	const contrast = 15

	var v complex128
	for n := uint8(0); n < iterations; n++ {
		v = v*v + z
		if cmplx.Abs(v) > 2 {
			return color.Gray{255 - contrast*n}
		}
	}
	return color.Black
}
