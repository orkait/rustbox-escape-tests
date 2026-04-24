package main

import (
	"fmt"
	"os"
)

func main() {
	var files []*os.File
	for {
		f, err := os.Open("/dev/null")
		if err != nil {
			panic(fmt.Sprintf("stopped at %d fds: %v", len(files), err))
		}
		files = append(files, f)
		fmt.Println("ESCAPED:", len(files))
	}
}
