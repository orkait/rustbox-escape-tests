package main

import (
	"os/signal"
	"syscall"
)

func main() {
	signal.Ignore(syscall.SIGXCPU)
	for {
	}
}
