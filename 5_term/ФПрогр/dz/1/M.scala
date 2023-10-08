import java.util.Date
import scala.math._

object M {

  def getRandomNumber(enter: Long, oldBase: Double): List[Double] = {
    val plus = log(enter)*100
    val mod = pow(plus, 3)

    var one = oldBase * enter;
    var two = one + plus;
    var newBase = two % mod;

    val randomNum = newBase/mod

    return List(randomNum, newBase)
  }

  def main(args: Array[String]): Unit = {
    val arr = Array[Double](0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    var i = 0;

    print("Enter first number: ")
    val enter = scala.io.StdIn.readLong()
    var base: Double = 12345.67;

    while(i < 10) {
      val answ = getRandomNumber(enter, base)
      
      base = answ.apply(1)
      val index = (answ.apply(0) * 10).toInt

      if(arr.apply(index) == 0.0) {
        arr(index) = answ.apply(0);
        i += 1
      }
    }
    
    print("Random numbers: \n\n")
    arr.map(item => println(item))
  }
}