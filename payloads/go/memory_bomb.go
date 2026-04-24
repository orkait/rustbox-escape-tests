package main

import "fmt"

func main() {
	var s [][]byte
	for {
		s = append(s, make([]byte, 1024*1024))
	}
	fmt.Println("ESCAPED", len(s))
}
