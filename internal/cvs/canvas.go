package cvs

import (
	"image"
	"image/color"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/canvas"
)

var _ fyne.CanvasObject = Canvas{}

func New() (c Canvas) {
	c.img = Image{image.NewRGBA(image.Rect(0, 0, 64, 64))}
	c.img.Line(0, 0, 32, 64, color.RGBA{0, 255, 255, 0})
	c.Raster = canvas.NewRaster(c.generate)
	return
}

type Canvas struct {
	*canvas.Raster
	img Image
}

func (c Canvas) generate(w, h int) image.Image {
	o := image.NewRGBA(image.Rect(0, 0, w, h))
	iw, ih := (c.img.Rect.Max.X - c.img.Rect.Min.X), (c.img.Rect.Max.Y - c.img.Rect.Min.Y)
	for x := 0; x < w; x++ {
		for y := 0; y < w; y++ {
			o.SetRGBA(x, y, c.img.RGBAAt(x*iw/w, y*ih/h))
		}
	}
	return o
}
