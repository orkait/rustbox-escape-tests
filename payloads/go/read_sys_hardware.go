package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func main() {
	err := filepath.Walk("/sys", func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return nil
		}
		if !info.IsDir() {
			fmt.Println("ESCAPED:", path)
		}
		return nil
	})
	if err != nil {
		panic(err)
	}
}
