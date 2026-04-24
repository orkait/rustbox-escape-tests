package main

import (
	"fmt"
	"sync"
)

func main() {
	var wg sync.WaitGroup
	for {
		wg.Add(1)
		go func() {
			defer wg.Done()
			select {}
		}()
		fmt.Println("ESCAPED")
	}
}
