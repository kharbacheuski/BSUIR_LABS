import scala.util.matching.Regex

object Main {

    def allVowels(text: String): Int = {
        val pattern = "[aeiouyAEIOUY]".r
        var vowels = pattern.findAllMatchIn(text)
        return vowels.size
    }

    def latinToNumbers(string: String): String = {
        val pattern: String = "[A-Za-z]"
        return string.replaceAll(pattern, "0");
    }

    def findWords(): String = {
        var words = "When executing the exercise extract all extra words".split(" ");
        val pattern = "ext"

        return words.filter(word => word.startsWith(pattern)).mkString(", ")
    }

    def reversWordsInText(text: String): String = {
        var array = text.split(" ")

        return array.map(word => word.reverse).mkString(" ")   
    }

    def main(args: Array[String]): Unit = {

        println("0 - All vowels")
        println("1 - Latin char to number")
        println("2 - Find words starts from 'ext'")
        println("3 - Replace 'the' to 'a'")
        println("4 - Reverse words in text")
        println("5 - Remove vowels")
        println("6 - Doubled letters")
        println("7 - Remove letter 'y'")
        println("8 - Add 'with hartness'")
        println("else - Exit\n\n")

        print("Enter text: ")
        var text = scala.io.StdIn.readLine();

        var msg = "Hello to everybody"

        var action = 1;

        while(action != -1) {
            print("\n\nSelect action: ")
            action = scala.io.StdIn.readInt()

            print("Answer: ");

            action match
            case 0 => {
                print(allVowels(text))
            }
            case 1 => {
                print(latinToNumbers(msg))
            }
            case 2 => {
                println("[" + findWords() + "]")
            }
            case 3 => {
                val answer = "A big round ball fall to the ground".replaceAll("the", "a")
                println(answer)
            }
            case 4 => {
                print(reversWordsInText(text))
            }
            case 5 => {
                print(msg.replaceAll("[aeiouyAEIOUY]", ""))
            }
            case 6 => {
                var answer: StringBuilder = StringBuilder();
                msg.map(ch => answer.append(ch.toString() + ch.toString()))
                print(answer.toString())
            }
            case 7 => {
                print(msg.replaceAll("y", ""))
            }
            case 8 => {
                val insertion = "with hartness "
                print(msg.substring(0, 6) + insertion + msg.substring(6, msg.length))
            }
            case default => {
                action = -1
                println("Exit...")
            }
        }
    }
}