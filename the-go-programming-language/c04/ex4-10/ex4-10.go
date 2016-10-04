package main

import (
	"fmt"
	"log"
	"os"
	"time"

	"github.com/itiut/sutra-copying/the-go-programming-language/c04/github"
)

func main() {
	result, err := github.SearchIssues(os.Args[1:])
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%d issues:\n", result.TotalCount)
	for _, item := range result.Items {
		age := toAge(item.CreatedAt)
		fmt.Printf("#%-5d %s %9.9s %.55s\n", item.Number, age, item.User.Login, item.Title)
	}
}

func toAge(t time.Time) string {
	duration := time.Since(t)
	switch {
	case duration < 30*24*time.Hour:
		return "< month"
	case duration < 365*24*time.Hour:
		return "< year "
	default:
		return "> year "
	}
}
