package main

import (
	"io"
	"log"
	"net"
	"os"
	"flag"
	//"strings"
	"fmt"
)

var name string
var server string



func main() {

	flag.StringVar(&name, "user", "karol", "user name")
	flag.StringVar(&server, "server", "localhost:8000", "server and port")
	flag.Parse()

	conn, err := net.Dial("tcp", server)
	if err != nil {
		log.Fatal(err)
	}
	done := make(chan struct{})
	go func() {
		fmt.Fprintf(conn, name+"\n")
		io.Copy(os.Stdout, conn) // NOTE: ignoring errors
		log.Println("done")
		done <- struct{}{} // signal the main goroutine
	}()
	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done // wait for background goroutine to finish
}

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}