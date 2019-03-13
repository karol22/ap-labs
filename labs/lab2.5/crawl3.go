// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 241.

// Crawl2 crawls web links starting with the command-line arguments.
//
// This version uses a buffered channel as a counting semaphore
// to limit the number of concurrent calls to links.Extract.
//
// Crawl3 adds support for depth limiting.
//
package main

import (
	"fmt"
	"log"
	"os"
	"flag"

	"gopl.io/ch5/links"
)

type linkElement struct {
	Depth int
	Url string
}

//!+sema
// tokens is a counting semaphore used to
// enforce a limit of 20 concurrent requests.
var tokens = make(chan struct{}, 20)
var maxDepth int

func crawl(current linkElement) []linkElement {
	fmt.Println("Depth: ", current.Depth, " URL: ", current.Url)
	if current.Depth >= maxDepth {
		return nil
	}
	tokens <- struct{}{}
	urls, err := links.Extract(current.Url)
	<-tokens
	if err != nil {
		log.Print(err)
	}
	elems := []linkElement{}
	for _, url := range urls{
		elems = append(elems, linkElement{current.Depth+1, url})
	}
	return elems
}

//!-sema

//!+
func main() {
	flag.IntVar(&maxDepth, "depth", 0, "Depth to crawl")
	flag.Parse()
	worklist := make(chan []linkElement)
	var n int // number of pending sends to worklist

	// Start with the command-line arguments.
	n++
	go func() {
		elems := []linkElement{}
		elems = append(elems, linkElement{0, os.Args[2]})
		worklist <- elems
	}()

	// Crawl the web concurrently.
	seen := make(map[string]bool)
	for ; n > 0; n-- {
		list := <-worklist
		for _, elem := range list {
			if !seen[elem.Url] {
				seen[elem.Url] = true
				n++
				go func(elem linkElement) {
					worklist <- crawl(elem)
				}(elem)
			}
		}
	}
}

//!-
