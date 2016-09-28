package main

import (
	"log"
	"net/http"
	"strconv"
)

func main() {
	http.HandleFunc("/", handler)
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
	if err := r.ParseForm(); err != nil {
		log.Print(err)
	}
	x, y := 2, 2
	if val, err := strconv.Atoi(r.FormValue("x")); err == nil {
		x = val
	}
	if val, err := strconv.Atoi(r.FormValue("y")); err == nil {
		y = val
	}
	draw(w, x, y)
}
