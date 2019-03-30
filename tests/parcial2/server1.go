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
	"strings"
	"os"
	"time"
)

//!+broadcaster
type client chan<- string // an outgoing message channel


var users = make(map[string]string);
var uc = make(map[string]net.Conn);

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
)


func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			for cli := range clients {
				//fmt.Println(cli)
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
func handleConn(conn net.Conn, user string) {
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)
	who := conn.RemoteAddr().String()

	_, found := users[strings.TrimSuffix(user, "\n")]
	if(found){
		ch <- "There's already a user with that username"
		conn.Close()
		return

	}
	users[strings.TrimSuffix(user, "\n")] = who
	//users_chan[user] = conn
	uc[strings.TrimSuffix(user, "\n")] = conn
	fmt.Println("New connected user [" + strings.TrimSuffix(user, "\n") +"]")
	ch <- "Welcome to Simple IRC server"
	ch <- "irc-server > Your user [" + strings.TrimSuffix(user, "\n") + "] is successfully logged"

	messages <- strings.TrimSuffix(user, "\n") + " has arrived"
	entering <- ch

	

	input := bufio.NewScanner(conn)
	//ch <- strings.TrimSuffix(user, "\n") + "> "
	fmt.Println(input.Text());
	for input.Scan() {
		var s []string
		s = strings.Fields(input.Text())
		if(len(s) != 0){
		switch s[0] {
		case "/users":
			var u string
			for k, _ :=range users{
				u = u + k + ", "
			}
			ch <- u
		case "/user":
			if(len(s) == 2){
			var u string
			u = "not user found"
			for k, v :=range users{
				if(strings.Trim(k, " ") == strings.Trim(s[1], " ")){
					u = "username: " + k + " IP: " + v
				}
			}
			ch <- u
			}else{
				ch <- "irc-server > not enough arguments /user <username>"
			}
			
		case "/time":
			ch <- time.Now().Format("15:04:05\n")
		case "/msg":
			if(len(s) > 2){
				var u string
				for i, msg := range s{
					if(i > 1){
						u = u + msg + " "
					}

				}
				fmt.Println(u)
				if _,found := uc[strings.Trim(s[1], " ")]; found{
					fmt.Fprintln(uc[strings.Trim(s[1], " ")], strings.TrimSuffix(user, "\n") + ">" + u)
				}else{
					ch <- "irc-server > No such user"
				}
			}
		default:
			messages <- strings.TrimSuffix(user, "\n") + ": " + input.Text()
		}
		}
	}
	// NOTE: ignoring potential errors from input.Err()

	leaving <- ch
	messages <- "irc-server >" + strings.TrimSuffix(user, "\n") + " has left"
	fmt.Println("[" + strings.TrimSuffix(user, "\n") +"] left")
	delete(users, user)
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
	localhost:="localhost:"
	
	listener, err := net.Listen("tcp", localhost + os.Args[4])
	fmt.Println("Simple IRC Server started at "+ localhost + os.Args[4])
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()
	for {
		conn, err := listener.Accept()
		message,_:= bufio.NewReader(conn).ReadString('\n');
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn, string(message));
	}
}

//!-main