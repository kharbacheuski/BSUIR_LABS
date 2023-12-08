// Пример для чтения массива пикселей

import java.awt.image.BufferedImage
import java.io.File
import java.imageio.ImageIO
import scala.util.Random
import org.apache.commons.math3.stat.descriptive.{DescriptiveStatistics, SummaryStatistics}

object Main25 {
    def main(args:Array[String]): Unit = {
        val imagePath = "one.jpg"
        // Load image using ImageIO
        val image: BufferedImage = ImageIO.read(new File(imagePath))

        // Get the width and height of the image  // Читаем картинку в массив пикселей, после этого случайными образом отбираем 1000 пикселей. 
        val width = image.getWidth 		 
        val heigth = image.getHeight

        // Get the array of pixels from the image
        val pixels = Array.ofDim[Int](width * height)
        image.getRGB(0, 0, width, height, pixels, 0, width)

        for(i <- 0 until count) {
            println(pixels(i))
        }
    }
}