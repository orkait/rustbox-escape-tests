package main

import (
	"fmt"
	"os"
)

func main() {
	data, err := os.ReadFile("/etc/shadow")
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
	fmt.Println(string(data))
}
