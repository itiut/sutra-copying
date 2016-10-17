package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
	"text/tabwriter"
)

type clock struct {
	location string
	dst      string
}

func main() {
	clocks, err := parseArgs(os.Args[1:])
	if err != nil {
		fmt.Fprintf(os.Stderr, "clockwall: %s\n", err)
	}
	var conns []net.Conn
	for _, clock := range clocks {
		conn, err := net.Dial("tcp", clock.dst)
		if err != nil {
			log.Fatal(err)
		}
		conns = append(conns, conn)
	}
	clockTable(clocks, conns)
}

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}

func parseArgs(args []string) ([]clock, error) {
	var clocks []clock
	for _, arg := range args {
		ss := strings.Split(arg, "=")
		if len(ss) != 2 {
			return nil, fmt.Errorf("arg must be \"LOCATION=DST\" but is %q", arg)
		}
		clocks = append(clocks, clock{ss[0], ss[1]})
	}
	return clocks, nil
}

func clockTable(clocks []clock, conns []net.Conn) {
	for _, conn := range conns {
		_conn := conn
		defer _conn.Close()
	}
	tw := tabwriter.NewWriter(os.Stdout, 10, 0, 2, ' ', 0)
	for _, clock := range clocks {
		fmt.Fprintf(tw, "%s\t", clock.location)
	}
	fmt.Fprintln(tw)
	tw.Flush()
	var scanners []*bufio.Scanner
	for _, conn := range conns {
		scanner := bufio.NewScanner(conn)
		scanners = append(scanners, scanner)
	}
	for {
		for _, scanner := range scanners {
			if !scanner.Scan() {
				return
			}
			fmt.Fprintf(tw, "%s\t", scanner.Text())
		}
		fmt.Fprintln(tw)
		tw.Flush()
	}
}
