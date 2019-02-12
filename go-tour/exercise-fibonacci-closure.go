package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	last1 := 1
	last2 := -1
	aux := 1
	return func() int {
		aux = last1 + last2
		last2 = last1
		last1 = aux
		return aux
	}
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
