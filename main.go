package main

import (
	"fmt"

	"fyne.io/fyne/v2/app"
)

func main() {
	rApp := app.NewWithID("com.github.pythonian23.rawr")
	rWin := rApp.NewWindow("rawr x3")

	rWin.SetContent(UI())
	defer deinit()

	rWin.ShowAndRun()
}

func deinit() {
	fmt.Println("Goodbye!")
}
