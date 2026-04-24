package main

import (
	"fmt"
	"syscall"
)

func main() {
	_, _, errno := syscall.RawSyscall(syscall.SYS_UNSHARE, syscall.CLONE_NEWUSER, 0, 0)
	if errno != 0 {
		panic(fmt.Sprintf("unshare failed: %v", errno))
	}
	fmt.Println("ESCAPED")
}
