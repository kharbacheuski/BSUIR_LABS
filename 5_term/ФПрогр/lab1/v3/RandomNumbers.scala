// Генератор случайных чисел 

object Gen {
    def main(args: Array[String]): Unit = {
        print("Enter the number: ")

        var a, b, z = "";
        var c, w = 0l 
        var rez: Float = 0.0

        z = scala.io.StdIn.readLine()

        if (z.length() < 10) {
            println("Incorrect number");
            sys.exit(0)  
        }

        for (i <- 1 to 3) {
            a = z.substring(0, 5)
            b = z.substring(5, 10)
            w = (b + a).toLong;

            c = ((z.toLong)*w).toLong

            if(c == 0l) {
                println("Incorrect number");
                sys.exit(0);
            }
            if(c < 0l) {
                c *= -1;
            }

            rez = c.toString().substring(0,3).toFloat / 1000

            println(rez); 

            z = c.toString()
        }
    }
}

