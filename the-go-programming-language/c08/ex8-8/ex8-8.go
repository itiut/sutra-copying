package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"strings"
	"time"
)

func main() {
	listener, err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

func echo(c net.Conn, shout string, delay time.Duration) {
	fmt.Fprintln(c, "\t", strings.ToUpper(shout))
	time.Sleep(delay)
	fmt.Fprintln(c, "\t", shout)
	time.Sleep(delay)
	fmt.Fprintln(c, "\t", strings.ToLower(shout))
}

func handleConn(c net.Conn) {
	defer c.Close()

	tick := time.NewTicker(1 * time.Second)
	defer func() { tick.Stop() }()

	input := bufio.NewScanner(c)
	message := make(chan string)
	go func() {
		for input.Scan() {
			message <- input.Text()
		}
	}()

	sinceLastMessage := 0
	for {
		select {
		case <-tick.C:
			sinceLastMessage++
			if sinceLastMessage > 10 {
				return
			}
		case message := <-message:
			go echo(c, message, 1*time.Second)
		}
	}
}
