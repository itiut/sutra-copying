package main

import (
	"image"
	"image/color"
	"image/png"
	"math/cmplx"
	"os"
)

func main() {
	const (
		xmin, ymin, xmax, ymax = -2, -2, +2, +2
		width, height          = 1024, 1024
	)
	img := image.NewRGBA(image.Rect(0, 0, width, height))
	for py := 0; py < height; py++ {
		y0 := float64(py)/height*(ymax-ymin) + ymin
		y2 := float64(py+1)/height*(ymax-ymin) + ymin
		y1 := (y0 + y2) / 2
		for px := 0; px < width; px++ {
			x0 := float64(px)/width*(xmax-xmin) + xmin
			x2 := float64(px+1)/width*(xmax-xmin) + xmin
			x1 := (x0 + x2) / 2
			colors := []color.Color{
				mandelbrot(complex(x0, y0)),
				mandelbrot(complex(x0, y1)),
				mandelbrot(complex(x1, y0)),
				mandelbrot(complex(x1, y1)),
			}
			r, g, b, a := uint32(0), uint32(0), uint32(0), uint32(0)
			for i := 0; i < len(colors); i++ {
				_r, _g, _b, _a := colors[i].RGBA()
				r += _r
				g += _g
				b += _b
				a += _a
			}
			r /= 4
			g /= 4
			b /= 4
			a /= 4
			img.Set(px, py, color.RGBA{byte(r), byte(g), byte(b), byte(a)})
		}
	}
	png.Encode(os.Stdout, img)
}

func mandelbrot(z complex128) color.Color {
	const iterations = 200
	const contrast = 15

	var v complex128
	for n := uint8(0); n < iterations; n++ {
		v = v*v + z
		if cmplx.Abs(v) > 2 {
			return color.RGBA{contrast * n, contrast * n, 255 - contrast*n, 0xff}
		}
	}
	return color.Black
}
