package icon

import (
	"image"
	"sync"
)

var loadIconsOnce sync.Once
var icons map[string]image.Image

func loadIcons() {
	icons = make(map[string]image.Image)
	icons["spades.png"] = loadIcon("spades.png")
	icons["hearts.png"] = loadIcon("hearts.png")
	icons["diamonds.png"] = loadIcon("diamonds.png")
	icons["clubs.png"] = loadIcon("clubs.png")
}

func Icon(name string) image.Image {
	loadIconsOnce.Do(loadIcons)
	return icons[name]
}

func loadIcon(name string) image.Image {
	return nil
}
