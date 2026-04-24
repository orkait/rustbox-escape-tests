package main

import (
	"fmt"
	"os"
)

func main() {
	data, err := os.ReadFile("/proc/meminfo")
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
	fmt.Println(string(data))
}
