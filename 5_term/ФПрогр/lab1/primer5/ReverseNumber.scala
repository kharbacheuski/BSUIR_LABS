// Сформировать целое число из первых трех цифр шестизначного числа:

object Reverse {
    def main(args: Array[String]): Unit = {
        print("Enter the number: ")
        
        val number = scala.io.StdIn.readInt

        val reversedNumber = number.toString.reverse.toInt

        println(reversedNumber)
    }
}

