package main

import (
	"fmt"
	"os"
	"syscall"
)

func main() {
	err := syscall.PtraceAttach(os.Getpid())
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
}
