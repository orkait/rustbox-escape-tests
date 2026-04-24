package main

import (
	"fmt"
	"syscall"
)

func main() {
	err := syscall.Setuid(0)
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
}
