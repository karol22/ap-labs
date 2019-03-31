package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	//"io"
	"strings"
	//"os"
	//"bytes"
	"time"
)

type client chan<- string


var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
)


var users = make(map[string]*net.Conn)
var addresses = make(map[string]string)


func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			for  cli := range clients {
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

func handleConn(conn net.Conn, user string) {
	if _, ok := users[user]; ok {
		fmt.Fprintf(conn, "irc-server > That user already exists\n")
		conn.Close()
		return
	}
	users[user] = &conn
	addresses[user] = conn.RemoteAddr().String()
	ch := make(chan string) // outgoing client messages
	
	go clientWriter(conn, ch)
	fmt.Println("irc-server > New user "+user)
	ch <- "Welcome to Simple IRC server"
	ch <- "irc-server > Your user "+user+" is successfully logged"

	messages <- user + " has arrived"
	entering <- ch

	input := bufio.NewScanner(conn)
	for input.Scan() {
		words := strings.Fields(input.Text())
		if(len(words)>0){
			var res string
			switch words[0]{
			case "/users":
				res:="irc-server > "
				for x, _ := range users{
					res +=x+", "
				}
				res = res[:len(res)-1]
				ch <- res
			case "/time":
				ch <- "irc-server > Time: " + time.Now().Format(time.RFC1123)
			case "/user":
				
				if(len(words)==2){
					if val, ok := addresses[words[1]]; ok {
						res = "irc-server > username: " + words[1] + ", IP: " + val
						ch <- res
					} else {
						ch <- "That user does not exist. "
					}
				} else {
					ch <- "Invalid number of arguments. "
				}
			case "/msg":
				if(len(words) > 2){
					if val, ok := users[words[1]]; ok {
						res= user + " > "
						for i :=2; i<len(words); i++ {
							res += words[i] + " "
						}
						fmt.Fprintln(*val, res)
					} else{
						ch <- "irc-server > That user does not exist. "
					}
				} else {
					ch <- "irc-server > Invalid number of arguments"
				}
			}	
		}
	}
	leaving <- ch
	messages <- "irc-server >" + user + " has left"
	fmt.Println("irc-server > " + user + " left")
	delete(users, user)
	delete(addresses, user)
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}



func main() {
	listener, err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("irc-server > Simple IRC Server started at localhost:9000\nirc-server > Ready for receiving new clients")
	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go func(){
			user,_:= bufio.NewReader(conn).ReadString('\n');
			user = user[:len(user)-1]
			handleConn(conn, user)	
		}()
	}
}