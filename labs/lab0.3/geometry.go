package main

import (
	"fmt"
	"math"
)

type Point struct{ x, y float64 }

func (p Point) X() float64 {
	return p.x
}

func (p Point) Y() float64 {
	return p.y
}

func Distance(p, q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

type Path []Point

func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
		}
	}
	return sum
}

func printPoint(p Point) int {
	fmt.Println("The coordinates of the point are: ")
	fmt.Println(p.X())
	fmt.Println(p.Y())
	return 0
}

func main() {
	p1 := Point{2.3, 4.67}
	printPoint(p1)

}
