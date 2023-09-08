// Генератор случайных чисел 

object Main234 {
    def main(args: Array[String]): Unit = {
        print("Enter the number: ")

        
        var numberString =""
        var a, b, c, z = 0 
        var rez: Float = 0.0

        numberString = scala.io.StdIn.readLine()

        if (numberString.length() < 10) {
            println("Incorrect number");
            sys.exit(0)  
        }

        for (i <- 1 to 10) {
            a = numberString.substring(0, 5).toInt
            //println(numberString.length());
            
            b = numberString.substring(5, 10).toInt
            c = a*b
            rez = c.toString().substring(0,3).toFloat / 1000
            z += c 

            println(a);
            println(b);
            println(c);
            println(rez); 
            println("z="+ z)

            numberString= numberString.substring(1,numberString.length()-1)
            numberString="011"+z
    
        }
    }
}

