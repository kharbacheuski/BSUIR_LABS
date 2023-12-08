// Вывод из файла на консоль (Spark)

val conf = new org.apache.spark.SparkConf()
val lines = spark.read.textFile("D:\\unik\\sem5\\fprog\\lab4\\example.txt")
val words = lines.map(line => line.split(" "))
val longestSentence = lines.filter(line => line.split(" ").length >= 3).first()
val longestSentence2 = lines.foreach(line => println(line))