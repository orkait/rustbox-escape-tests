package main

import (
	"fmt"
	"os"
)

func main() {
	for i := 0; i < 100000; i++ {
		name := fmt.Sprintf("/tmp/inode_%d", i)
		err := os.WriteFile(name, []byte{}, 0644)
		if err != nil {
			panic(fmt.Sprintf("stopped at %d: %v", i, err))
		}
	}
	fmt.Println("ESCAPED")
}
