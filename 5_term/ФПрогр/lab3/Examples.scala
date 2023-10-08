import scala.util.matching.Regex

object Examples {

    def example1(): Unit = {
        val str = "Hello, World!"
        val newStr = str.replaceAll("o", "a")
        println(newStr) // "Hella, Warld!"
    }

    def example2(): Unit = {
        val str = "apple,banana,orange"
        val arr = str.split(",")
        println(arr.mkString(" ")) // "apple banana orange"
    }

    def example3(): Unit = {
        val str = "Hello, World!"
        println(str.startsWith("Hello")) // true
        println(str.endsWith("!")) // true
    }

    def example4(): Unit = {
        val str = "Hello, World!"
        val subStr = str.substring(7, 12)
        println(subStr) // "World"
    }

    def example5(): Unit = {
        val str = "Hello, World!"
        val arr = str.toCharArray()
        println(arr.mkString(" ")) // "H e l l o ,   W o r l d !"
    }

    def example6(): Unit = {
        val str = "Hello, World!"
        println(str.toLowerCase) // "hello, world!"
        println(str.toUpperCase) // "HELLO, WORLD!"
    }

    def example7(): Unit = {
        val str = "   Hello, World!   "
        println(str.trim) // "Hello, World!"
    }

    def example8(): Unit = {
        val str = "Hello, World!"
        println(str.indexOf("o")) // 4
        println(str.lastIndexOf("o")) // 8
    }

    def example9(): Unit = {
        val str = "Hello, World!"
        println(str.charAt(7)) // 'W'
    }

    def example10(): Unit = {
        val str =
        """
            |Hello,
            |World!
            |""".stripMargin
        println(str) // "Hello,\nWorld!\n"
    }

    def example11(): Unit = {
        val regex = """(\d{3})-(\d{2})-(\d{4})""".r

        val str1 = "123-45-6789"
        val str2 = "abc-12-3456"

        val match1 = regex.findFirstMatchIn(str1)
        val match2 = regex.findFirstMatchIn(str2)

        match1 match {
            case Some(m) => println(s"Match found: ${m.group(0)}")
            case None => println("No match found")
        }

        match2 match {
            case Some(m) => println(s"Match found: ${m.group(0)}")
            case None => println("No match found")
        }
    }

    def example12(): Unit = {
        val str = "The quick brown fox jumps over the lazy dog"
        val pattern = "fox".r
        val matches = pattern.findAllIn(str)

        matches.foreach(println)
    }


    def main(args: Array[String]): Unit = {

        println("\n\nExample 1: ")
        example1()
        println("\n\nExample 2: ")
        example2()
        println("\n\nExample 3: ")
        example3()
        println("\n\nExample 4: ")
        example4()
        println("\n\nExample 5: ")
        example5()
        println("\n\nExample 6: ")
        example6()
        println("\n\nExample 7: ")
        example7()
        println("\n\nExample 8: ")
        example8()
        println("\n\nExample 9: ")
        example9()
        println("\n\nExample 10: ")
        example10()
        println("\n\nExample 11: ")
        example11()
        println("\n\nExample 12: ")
        example12()
    }
}