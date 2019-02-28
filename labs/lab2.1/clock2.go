// Clock2 is a concurrent TCP server that periodically writes the time.
package main

import (

	//"fmt"
	"flag"
	"os"
	"io"
	"log"
	"net"
	"time"
)

func handleConn(c net.Conn) {
	defer c.Close()
	for {
		loc, _ := time.LoadLocation(os.Getenv("TZ"))
		//fmt.Println(thatTime.Format("15:04:05\n"))
		_, err := io.WriteString(c, time.Now().In(loc).Format("15:04:05\n"))
		if err != nil {
			return // e.g., client disconnected
		}
		time.Sleep(time.Second)
	}
}

func main() {	
	portPtr := flag.String("port", "8080", "a port")
	flag.Parse()
	//fmt.Println("port:", *portPtr)
	//fmt.Println(env)
	//env := os.Getenv("TZ")
	listener, err := net.Listen("tcp", "localhost:"+ *portPtr)
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn) // handle connections concurrently
	}
}