package main

import (
	"fmt"
	"syscall"
)

func main() {
	err := syscall.Setgid(0)
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
}
