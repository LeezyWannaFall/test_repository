package main

import (
	"fmt"
	
)

func main() {
	var x, z float64
	fmt.Scan(&x, &z)	
	z -= (z*z - x) / (2*z)
	fmt.Println(x, z)
}