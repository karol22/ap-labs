package main

import (
	"strings"

	"golang.org/x/tour/wc"
	//"fmt"
)

func WordCount(s string) map[string]int {
	//create map
	m := make(map[string]int)
	//create map and ignore the index
	for _, f := range strings.Fields(s) {
		//fmt.Println(i)
		m[f]++
	}
	return m
}

func main() {
	wc.Test(WordCount)
}
