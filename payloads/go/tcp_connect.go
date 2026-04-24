package main

import (
	"fmt"
	"net"
	"time"
)

func main() {
	conn, err := net.DialTimeout("tcp", "8.8.8.8:53", 2*time.Second)
	if err != nil {
		panic(err)
	}
	defer conn.Close()
	fmt.Println("ESCAPED")
}
