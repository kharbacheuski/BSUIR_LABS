object Main {

    def sum(arr: List[Int]): Int = {
        if(arr.isEmpty) 0
        else arr.head + sum(arr.tail)
    }

    // 1
    def sumOfElementsInRange(arr: List[Int]) = {
        val flteredList = arr.filter(item => item <= 5 && item >= 0)
        println("Answer: " + sum(flteredList))
    }
    // 2
    def sumOfElementsByIndexes(arr: List[Int]) = {
        print("Input indexes: ")
        val indexes = scala.io.StdIn.readLine().split(" ").map(_.toInt).toList

        var listForSum = indexes.map(i => arr.apply(i))

        println("Answer: " + sum(listForSum))
    }

    // 3
    def indexOfMin(arr: List[Int]) = {
        
        def calculate(arr: List[Int], currentIndex: Int, index: Int): Int = {
            if(currentIndex == arr.length - 1) index
            else {
                var newMinIndex: Int = index

                if(arr.apply(index) > arr.apply(currentIndex))
                    newMinIndex = currentIndex

                calculate(arr, currentIndex + 1, newMinIndex)
            }
        }
        println("Answer: " + calculate(arr, 0, 0))
    }

    // 4
    def areAllLessThan(arr: List[Int]) = {

        def calculate(arr: List[Int], num: Int): Boolean = {
            if(arr.isEmpty) true
            else {
                if (arr.head > num) false
                else calculate(arr.tail, num)
            }
        }

        print("Input  num: ")
        var num = scala.io.StdIn.readInt()

        println("Answer: " + calculate(arr, num))
    }

    // 5
    def countOfElementsThatLessThan(arr: List[Int]) = {

        def calculate(arr: List[Int], num: Int, count: Int): Int = {
            if(arr.isEmpty) count
            else {
                var newCount = count;
                if (arr.head <= num)
                    newCount += 1
                
                calculate(arr.tail, num, newCount)
            }
        }

        print("Input  num: ")
        val num = scala.io.StdIn.readInt()

        println("Answer: " + calculate(arr, num, 0))
    }

    def main(args: Array[String]): Unit = {

        println("1 - Sum of array range [0, 5]")
        println("2 - Sum of elements by indexes")
        println("3 - Index of min element")
        println("4 - Are all elements less than")
        println("5 - Count of elements that less than")
        println("0 - exit")

        print("Input list: ")
        var stringArrayOfInts = scala.io.StdIn.readLine().split(" ").map(item => item.toInt).toList

        val list = List(stringArrayOfInts: _*)

        var action = 1;

        while(action != 0) {
            print("Select action: ")
            action = scala.io.StdIn.readInt()

            action match
            case 1 => sumOfElementsInRange(list)
            case 2 => sumOfElementsByIndexes(list)
            case 3 => indexOfMin(list)
            case 4 => areAllLessThan(list)
            case 5 => countOfElementsThatLessThan(list)
            case 0 => {
                action = 0
                println("Exit...")
            }
        }
    }
}