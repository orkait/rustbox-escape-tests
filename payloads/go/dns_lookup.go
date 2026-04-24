package main

import (
	"fmt"
	"net"
)

func main() {
	addrs, err := net.LookupHost("google.com")
	if err != nil {
		panic(err)
	}
	fmt.Println("ESCAPED")
	fmt.Println(addrs)
}
