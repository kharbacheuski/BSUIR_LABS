// Сформировать целое число из первых трех цифр шестизначного числа:

object Main22 {
    def main(args: Array[String]): Unit = {
        print("Enter the number: ")
        
        val number = scala.io.StdIn.readInt

        try {
            val numberString = number.toString
            val firstThreeDigits = if (numberString.length >= 3 && number >= 0) {
                numberString.substring(0, 3).toInt
            } 
            else {
                throw new Exception("Number does not have at least three digits or is negative")
            }

            println(firstThreeDigits)
        } 
        catch {
            case e: Exception => println(e.getMessage)
        }
    }
}
