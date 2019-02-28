package main 

import(
	"os"
	"strings"
	"net"
	"io"
	"log"
	"fmt"
)

func handleConnection(conn net.Conn, city string){
	for {
		buf := new(bytes.Buffer)
		_, err := buf.ReadFrom(conn)
		if(err != nil){
			log.Fatal(err)
		}
		s := buf.String() // Does a complete copy of the bytes in the buffer.
		output := city + " " + s;
		_, err = fmt.Fprint(os.Stdout, output)
		if(err != nil){
			log.Fatal(err)
		}
	}
}
func main(){
	process := make(chan int)
	for i:= 1; i<len(os.Args); i++{
		s := strings.Split(os.Args[i], "=")
		city := s[0]
		url := s[1]
		conn, err := net.Dial("tcp", url)
		if err != nil{
			log.Fatal(err)
		}
		defer conn.Close()
		go handleConnection(conn, city);
	}
	_ = <-process
	close(process)
}