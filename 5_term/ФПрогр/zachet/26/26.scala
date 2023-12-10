// Пример для сравнения двух картинок

import java.awt.image.BufferedImage
import java.io.File	
import javax.imageio.ImageIO
import scala.util.Random
import org.apache.commons.math3.stat.descriptive.{DescriptiveStatistics, SummaryStatistics}

object Main25 {
    def main(args:Array[String]): Unit = {
        val imagePath = "../one.jpg"
        // Load the image using ImageIO

        var image: BufferedImage = ImageIO.read(new File(imagePath))
        // Get the width and height of image
        val width = image.getWidth
        val height = image.getHeight
        // Get the array of pixels from the image
        val pixels = Array.ofDim[Int](width * height)
        image getRGB(0, 0, width, height, pixels, 0, width)

        val count = 1000
        var numbers = List[Double]()
        var nomers = List[Int]()
        val random = new Random()

        for(i <- 0 until count) {
            var j = random.nextInt(width * height)
            nomers = j :: nomers
            numbers = math.abs(pixels(j)) :: numbers
        }

        val stats1 = new DescriptiveStatistics()
        numbers.foreach(stats1.addValue)

        val mean = stats1.getMean()
        val stdDev = math.sqrt(stats1.getStandardDeviation())
        println(s"Mean value: ${mean}")
        println(s"Stdev: ${stdDev}")


        val imagePath2 = "../two.jpg"
        var image2: BufferedImage = ImageIO.read(new File(imagePath2))

        val pixels2 = Array.ofDim[Int](width * height)
        image2.getRGB(0, 0, width, height, pixels2, 0, width)

        var numbers2 = List[Double]()
        
        for (i <- 0 until count) {
            numbers2 = math.abs(pixels2(nomers(i))) :: numbers2
        }
            
        val stats2 = new DescriptiveStatistics()
        numbers2.foreach(stats2.addValue)
        val mean2 = stats2.getMean()
        val stdDev2 = math.sqrt(stats2.getStandardDeviation())

        println(s"Mean-2 value: ${mean2}") //  и дальше 
        println(s"Stdev-2: ${stdDev2}")   // выводим
    }
}