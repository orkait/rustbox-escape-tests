package main

import (
	"fmt"
	"os"
)

func main() {
	for i := 0; i < 20; i++ {
		os.Chdir("..")
	}
	data, err := os.ReadFile("etc/passwd")
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
	fmt.Println(string(data))
}
