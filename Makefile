CODE = *.go

.PHONY: all format clean debug release package run

all:
	$(MAKE) format
	$(MAKE) debug

format: $(CODE) go.mod go.sum
	gofmt -w $(CODE)
	goimports -w $(CODE)
	go mod tidy

clean:
	rm -rf build

debug: TAGS = debug hints no_animations
debug: build/rawr

release: RELEASE = --release
release: build/rawr

package:
	$(MAKE) release
	$(MAKE) build/rawr.tar.xz

run:
	build/rawr

################################################################################

bundled.go: res/*
	fyne bundle -o bundled.go res

build:
	mkdir -p build

build/rawr: $(CODE) bundled.go | build
	cd build && fyne build -o rawr --tags "$(TAGS)" $(RELEASE) ../

build/rawr.tar.xz: PACKAGE_FLAGS = --exe rawr --name rawr --appVersion 0.0 --id com.github.pythonian23.rawr --icon ../first.png
build/rawr.tar.xz: build/rawr | build
	cd build && fyne package --target amd64 --target linux $(PACKAGE_FLAGS) --tags "$(TAGS)" $(RELEASE)
