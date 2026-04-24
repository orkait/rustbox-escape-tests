package main

import (
	"fmt"
	"os"
)

func main() {
	err := os.WriteFile("/bin/evil", []byte("#!/bin/sh\necho pwned"), 0755)
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
}
