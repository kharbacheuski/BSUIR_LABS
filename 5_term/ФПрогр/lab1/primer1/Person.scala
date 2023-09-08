// Hello

class Person {
  def hello(name: String): Unit = println(s"Hello, $name!")
}

object Main22 {
  def main(args: Array[String]): Unit = {
    val x = new Person()
    x.hello("Alice")
    x.hello("Bob")
  }
}