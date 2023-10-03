import scala.math._
import scala.collection.mutable.ArrayBuffer

object Main {
    def getRate(number: Int): Int = {
        var counter: Int = 0;
        var nmb: Int = number

        while(nmb > 0) {
            nmb = (nmb/10).toInt;

            counter += 1;
        }

        return counter;
    }

    def newBase(prevRez: Double): Int = {
        var newBase: Int = prevRez.toString().substring(2, 10).toInt
        println(s"new base = $newBase");
        return newBase;
    }

    def getRandomNumber(base: String, count: Int = 10): Double = {
        var first, second, degree = 0;
        
        var rez: Double = 0.0;

        first = base.substring(0, 3).toInt;
        second = base.substring(3, 6).toInt;
        degree = base.substring(6, 7).toInt;

        if(degree == 0) degree = 2

        rez = log(pow(first*second, degree));

        println(s"rez = $rez");

        return rez
    }

    def main(args: Array[String]): Unit = {
        println("Enter the base number: (7)")

        var base = "";

        base = scala.io.StdIn.readLine()

        if (base.length() < 7)  {
            println("Incorrect number");
            sys.exit(0)  
        }

        var results: Array[Double] = Array(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); 

        var i = 0;
        var maxIterationsCount = 500;

        while (i < 10 && maxIterationsCount > 0) {
            var rez = getRandomNumber(base);

            val index = (rez * 10).toInt

            if(results(index) == 0.0) {
                results(index) = rez;
                i +=1;
            }

            maxIterationsCount -= 1;

            base = newBase(rez).toString();
        }

        if(maxIterationsCount == 0)
            println("Cycle iterations limit (500)");

        results.map(item => println(item));

    }
}