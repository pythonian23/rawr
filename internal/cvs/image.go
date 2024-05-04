package cvs

import (
	"image"
	"image/color"
)

type Image struct{ *image.RGBA }

func (i Image) Line(x0, y0, x1, y1 int, c color.Color) {
	x0, x1 = min(x0, x1), max(x0, x1)
	y0, y1 = min(y0, y1), max(y0, y1)

	for x := x0; x <= x1; x++ {
		i.Set(x, x*(y0-y1)/(x0-x1), c)
	}
}
