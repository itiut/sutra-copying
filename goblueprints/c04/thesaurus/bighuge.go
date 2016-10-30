package thesaurus

import (
	"encoding/json"
	"fmt"
	"net/http"
)

type BigHuge struct {
	APIKey string
}

type synonyms struct {
	Noun *words `json:"noun"`
	Verb *words `json:"verb"`
}

type words struct {
	Syn []string `json:"syn"`
}

func (b *BigHuge) Synonyms(term string) ([]string, error) {
	var syns []string
	response, err := http.Get("http://words.bighugelabs.com/apisample.php?v=2&format=json")
	if err != nil {
		return nil, fmt.Errorf("bighuge: failed to search synonyms of %q: %v", term, err)
	}
	var data synonyms
	defer response.Body.Close()
	if err := json.NewDecoder(response.Body).Decode(&data); err != nil {
		return nil, err
	}
	syns = append(syns, data.Noun.Syn...)
	syns = append(syns, data.Verb.Syn...)
	return syns, nil
}
