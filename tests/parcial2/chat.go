// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"io"
	"strings"
)

//!+broadcaster
type client chan<- string // an outgoing message channel
type User struct{
	name string
	flow client
}
var clients map[client]bool // all connected clients
var clientsNames map[string]bool // all connected clients

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
)

func broadcaster() {
	for {
		select {
			case msg := <-messages:
				//fmt.Println(msg)
				// Broadcast incoming message to all
				// clients' outgoing message channels.
				for cli := range clients {
					cli <- msg
				}

			case cli := <-entering:
				clients[cli] = true

			case cli := <-leaving:
				delete(clients, cli)
				close(cli)
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn) {
	//.Println("new user")
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)
	who := conn.RemoteAddr().String()
	ch <- "You are " + who
	//messages <- who + " has arrived"
	//entering <- ch

	input := bufio.NewScanner(conn)
	//output := bufio.NewWriter(conn)
	first := true
	for input.Scan() {
		//messages <- who + ": " + input.Text()
		if(first){
			clientsNames[input.Text()] = true
			first = false
		} else if(input.Text()=="/users"){
			s := ""
			for k, v := range clientsNames {
				if(v) {
					s+=k+" ";
				}
			}
			ww := strings.NewReader(s)
			mustCopy(conn, ww)

		}	
	}
	
	// NOTE: ignoring potential errors from input.Err()

	leaving <- ch
	messages <- who + " has left"
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

//!+main
func main() {
	clients = make(map[client]bool)
	clientsNames = make(map[string]bool)
	listener, err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}
	
	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

//!-main

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}