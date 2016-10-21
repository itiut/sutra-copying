package main

import (
	"bufio"
	"bytes"
	"encoding/json"
	"fmt"
	"os"
	"os/exec"
	"strings"
)

type Package struct {
	ImportPath string
	Deps       []string
}

func main() {
	dependees, err := listPackages(os.Args[1:])
	if err != nil {
		fmt.Fprintf(os.Stderr, "ex10-4: %v\n", err)
		os.Exit(1)
	}
	if err := printDependers(dependees); err != nil {
		fmt.Fprintf(os.Stderr, "ex10-4: %v\n", err)
		os.Exit(1)
	}
}

func listPackages(args []string) ([]string, error) {
	command := []string{"go", "list", "-f", "{{.ImportPath}}"}
	command = append(command, args...)
	cmd := exec.Command(command[0], command[1:]...)
	var out bytes.Buffer
	cmd.Stdout = &out
	if err := cmd.Run(); err != nil {
		return nil, fmt.Errorf("running %q: %v", strings.Join(command, " "), err)
	}
	return strings.Split(strings.TrimSpace(out.String()), "\n"), nil
}

func listAllPackages() ([]Package, error) {
	command := []string{"go", "list", "-f", `{"ImportPath": "{{.ImportPath}}", "Deps": ["{{join .Deps "\", \""}}"]}`, "..."}
	cmd := exec.Command(command[0], command[1:]...)
	var out bytes.Buffer
	cmd.Stdout = &out
	if err := cmd.Run(); err != nil {
		return nil, fmt.Errorf("running %q: %v", strings.Join(command, " "), err)
	}

	var packages []Package
	input := bufio.NewScanner(bytes.NewReader(out.Bytes()))
	for input.Scan() {
		var pkg Package
		if err := json.NewDecoder(strings.NewReader(input.Text())).Decode(&pkg); err != nil {
			return nil, fmt.Errorf("decoding json: %v", err)
		}
		packages = append(packages, pkg)
	}
	return packages, nil
}

func printDependers(dependees []string) error {
	packages, err := listAllPackages()
	if err != nil {
		return err
	}

	dependers := make(map[string][]string)
	for _, pkg := range packages {
		for _, dep := range pkg.Deps {
			for _, dependee := range dependees {
				if dependee == dep {
					dependers[dependee] = append(dependers[dependee], pkg.ImportPath)
					break
				}
			}
		}
	}

	for _, dependee := range dependees {
		if dependers, ok := dependers[dependee]; ok {
			fmt.Printf("%s:\n", dependee)
			for _, depender := range dependers {
				fmt.Printf("\t%s\n", depender)
			}
			fmt.Println()
		}
	}
	return nil
}
