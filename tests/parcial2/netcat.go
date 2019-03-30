
// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 227.

// Netcat is a simple read/write client for TCP servers.
package main

import (
	"io"
	"log"
	"net"
	"os"
	"flag"
	//"fmt"
	"strings"
)
var name string
var server string

//!+
func main() {
	flag.StringVar(&name, "user", "karol", "user name")
	flag.StringVar(&server, "server", "localhost:8000", "server and port")
	flag.Parse()
	//fmt.Println(name, server)
	k := strings.NewReader(name)

	conn, err := net.Dial("tcp", server)
	if err != nil {
		log.Fatal(err)
	}
	done := make(chan struct{})
	mustCopy(conn, k)
	go func() {
		io.Copy(os.Stdout, conn) // NOTE: ignoring errors
		log.Println("done")
		done <- struct{}{} // signal the main goroutine
	}()
	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done // wait for background goroutine to finish
}

//!-

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}