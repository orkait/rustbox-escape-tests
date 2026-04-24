package main

import (
	"fmt"
	"os"
)

func main() {
	f, err := os.Create("/tmp/bomb")
	if err != nil {
		panic(err)
	}
	defer f.Close()

	chunk := make([]byte, 1024*1024)
	for i := 0; i < 1024; i++ {
		_, err := f.Write(chunk)
		if err != nil {
			panic(err)
		}
	}
	fmt.Println("ESCAPED")
}
