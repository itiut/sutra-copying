package main

import (
	"fmt"
	"log"
	"net/http"

	"github.com/itiut/sutra-copying/the-go-programming-language/c12/params"
)

func main() {
	http.HandleFunc("/search", search)
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func search(resp http.ResponseWriter, req *http.Request) {
	var data struct {
		Labals     []string `http:"l"`
		MaxResults int      `http:"max"`
		Exact      bool     `http:"x"`
	}
	data.MaxResults = 10

	if err := params.Unpack(req, &data); err != nil {
		http.Error(resp, err.Error(), http.StatusBadRequest)
		return
	}
	fmt.Fprintf(resp, "Search: %+v\n", data)
}
