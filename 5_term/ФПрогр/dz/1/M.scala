import java.util.Date
import scala.collection.mutable.ArrayBuffer



object Main {
  def main(args: Array[String]): Unit = {

    val numberOfIntervals = 10

    var seed: Double = 12345.0;

    val arr = ArrayBuffer(0,0,0,0,0,0,0,0,0,0);
    var i = 0;

    val mult = scala.io.StdIn.readLong()
    val plus = scala.io.StdIn.readLong()
    val mod = scala.io.StdIn.readLong()

    while(i < 10) {

        val um = seed * mult;

        var pl = um + plus;

        val del = pl % mod;

        seed = del

        val randomNum = seed/mod
        
        val index = (randomNum * 10).toInt

        if(arr(index) == 0)
        {
            println("Random: " + randomNum)
            arr(index) = 1
            i += 1
        }
    }
  }
}