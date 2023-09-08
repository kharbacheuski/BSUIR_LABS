// Сумма цифр введенного числа

object Main22 {
    def main(args: Array[String]): Unit = {
        print("Enter the number: ")
        
        val a = scala.io.StdIn.readInt
        var sum = 0
        
        for (digit <- a.toString) {
            sum += digit.asDigit
        }

        println(sum)
    }
}
