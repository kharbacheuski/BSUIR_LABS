// Пример чтения-записи в файл

import scala.io.Source
import java.io.PrintWriter

object FileInputOutputExample {
    def main(args:Array[String]): Unit = {
        // Reading from a file
        val filename "example.txt"
        val file = Source.fromFile(filename)

        for(line <- file.getlines) {
            println(line)
        }

        file.close()

        // Writing to a file
        val outputFilename = "output.txt"
        val writer = new PrintWriter(outputFilename)

        writer.write("Hello, world!\n")
        writer.write("This is an example of writing to file")
    }
}