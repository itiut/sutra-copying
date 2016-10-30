package main

import (
	"bufio"
	"fmt"
	"log"
	"os"

	"github.com/itiut/sutra-copying/goblueprints/c04/thesaurus"
)

func main() {
	// apiKey := os.Getenv("BHT_APIKEY")
	apiKey := ""
	thesaurus := &thesaurus.BigHuge{APIKey: apiKey}
	s := bufio.NewScanner(os.Stdin)
	for s.Scan() {
		word := s.Text()
		syns, err := thesaurus.Synonyms(word)
		if err != nil {
			log.Fatalf("synonyms: %v", err)
		}
		if len(syns) == 0 {
			log.Fatalf("synonyms: there is no synonyms of %q", word)
		}
		for _, syn := range syns {
			fmt.Println(syn)
		}
	}
}
