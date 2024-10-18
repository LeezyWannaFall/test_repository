package main

import (
	"fmt"

)

func main() {
	var x, y float64
	var operator string
	fmt.Println("Введите первое число: ")
	fmt.Scan(&x)
	fmt.Println("Введите второе число: ")
	fmt.Scan(&y)
	fmt.Println("Введите оператор (+, -, *, /, %): ")
	fmt.Scan(&operator)

	switch operator {
	case "+":
		fmt.Println("Результат:", x + y)
	case "-":
		fmt.Println("Результат:", x - y)
	case "*":
		fmt.Println("Результат:", x * y)
	case "/":
		if y == 0 {
			fmt.Println("Ошибка, делить на 0 нельзя!")
		} else {
			fmt.Println("Результат:", x / y)
		}
	case "%":
		if y == 0 {
			fmt.Println("Ошибка: деление на ноль!")
		} else {
			fmt.Println("Результат:", int(x) % int(y))
		}
	default:
		fmt.Println("Неизвестный оператор")
	}
}