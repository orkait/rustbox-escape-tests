package main

import (
	"fmt"
	"syscall"
)

func main() {
	err := syscall.Mount("none", "/tmp", "tmpfs", 0, "")
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
}
