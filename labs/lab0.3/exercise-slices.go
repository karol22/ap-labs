package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
	k := make([][]uint8, dy)
	for i := range k {
		k[i] = make([]uint8, dx)
	}
	for y, r := range k {
		for x := range r {
			r[x] = uint8(x ^ y)
		}
	}
	return k
}

func main() {
	pic.Show(Pic)
}
