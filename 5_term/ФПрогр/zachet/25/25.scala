// Пример для определения статистических параметров картинки

import java.awt.image.BufferedImage
import java.io.File
import javax.imageio.ImageIO
import scala.util.Random
import org.apache.commons.math3.stat.descriptive.{DescriptiveStatistics, SummaryStatistics}

object Main25 {
    def main(args:Array[String]): Unit = {
        val imagePath = "../one.jpg"
        // Load image using ImageIO
        val image: BufferedImage = ImageIO.read(new File(imagePath))

        // Get the width and height of the image  // Читаем картинку в массив пикселей, после этого случайными образом отбираем 1000 пикселей. 
        val width = image.getWidth() 		 
        val height = image.getHeight()

        // Get the array of pixels from the image
        val pixels = Array.ofDim[Int](width * height)
        image.getRGB(0, 0, width, height, pixels, 0, width)

        val count = 1000
        var numbers = List[Double]() // Тут случайно выбранные пиксели хранятся в списке
        val random = new Random()

        for(i <- 0 until count) {
            var j = random.nextInt(width * height)
            numbers = math.abs(pixels(j)) :: numbers // Номера пикселей, пиксель j мы будем добавлять в список numbers
        }
            
        val stats1 = new DescriptiveStatistics() // Находим здесь среднее значение и стандартное отклонение  и дальше выводим
        numbers.foreach(stats1.addValue) 	// здесь среднее значение и стандартное отклонение 
        val mean = stats1.getMean()		//
        val stdDev = math.sqrt(stats1.getStandardDeviation) //
                        
        println(s"Mean value: ${mean}") //  и дальше 
        println(s"Stdev: ${stdDev}")   // выводим
    }
}