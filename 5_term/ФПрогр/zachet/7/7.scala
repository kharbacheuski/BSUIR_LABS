// Вывод из файла на консоль (Spark)

val conf = new org.apache.spark.SparkConf()
val lines = spark.read.textFile("D:\\Education\\BSUIR_LABS\\5_term\\ФПрогр\\zachet\\7\\example.txt")
val words = lines.flatMap(line => line.split(" "))
words.foreach(word => println(word))