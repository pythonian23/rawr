package main

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
)

var (
	mainBox,
	buttonGrid,
	canvasImage,
	statusBar fyne.CanvasObject
)

func init() {
}

func UI() fyne.CanvasObject {
	buttonGrid = container.NewGridWithColumns(
		2,
		widget.NewButtonWithIcon("", resourcePenPng, nil),
		widget.NewButtonWithIcon("", resourceLinePng, nil),
		widget.NewButtonWithIcon("", resourceFillPng, nil),
		widget.NewButtonWithIcon("", resourceEraserPng, nil),
		widget.NewButtonWithIcon("", resourcePickerPng, nil),
	)
	canvasImage := canvas.NewImageFromResource(resourcePenPng)
	canvasImage.FillMode = canvas.ImageFillContain
	canvasImage.ScaleMode = canvas.ImageScalePixels
	statusBar = widget.NewLabel("rawr")

	mainBox = container.NewBorder(nil, nil, container.NewVScroll(buttonGrid), nil, container.NewScroll(canvasImage))

	return container.NewBorder(nil, statusBar, nil, nil, mainBox)
}
