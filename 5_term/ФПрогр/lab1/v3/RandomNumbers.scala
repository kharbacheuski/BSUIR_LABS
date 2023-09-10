// Генератор случайных чисел 

object Gen {
    def main(args: Array[String]): Unit = {
        print("Enter the number: ")

        var z = "";
        var a, b, c, w = 0l 
        var rez: Float = 0.0

        z = scala.io.StdIn.readLine()

        if (z.length() < 10) {
            println("Incorrect number");
            sys.exit(0)  
        }

        for (i <- 1 to 3) {
            a = z.substring(0, 5).toLong 
            b = z.substring(5, 10).toLong
            w = (b.toString() + a.toString()).toLong;

            c = (z.toLong)*w

            z.toString()

            rez = c.toString().substring(0,3).toFloat / 1000

            println(rez); 

            z = c.toString()

            z = z.substring(1,z.length()-1)
            z = "011"+z
        }
    }
}

