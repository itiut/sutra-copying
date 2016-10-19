package main

import (
	"fmt"
	"time"
)

func main() {
	c0 := make(chan struct{})
	c1 := make(chan struct{})

	go pong(c0, c1)

	nPingPong := 0
	tick := time.Tick(1 * time.Second)
	for {
		select {
		case <-tick:
			fmt.Println(nPingPong)
			nPingPong = 0
		case <-c1:
			c0 <- struct{}{}
			nPingPong++
		}
	}
}

func pong(in <-chan struct{}, out chan<- struct{}) {
	for {
		out <- struct{}{}
		<-in
	}
}
