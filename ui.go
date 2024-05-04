package main

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
	"github.com/pythonian23/rawr/internal/cvs"
)

var (
	mainBox,
	buttonGrid,
	statusBar fyne.CanvasObject
	canvasImage cvs.Canvas
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
	canvasImage = cvs.New()
	statusBar = widget.NewLabel("rawr")

	mainBox = container.NewBorder(nil, nil, container.NewVScroll(buttonGrid), nil, canvasImage.Raster)

	return container.NewBorder(nil, statusBar, nil, nil, mainBox)
}
