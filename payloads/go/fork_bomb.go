package main

import (
	"fmt"
	"os/exec"
)

func main() {
	for {
		cmd := exec.Command("/proc/self/exe")
		err := cmd.Start()
		if err != nil {
			panic(err)
		}
		fmt.Println("ESCAPED")
	}
}
