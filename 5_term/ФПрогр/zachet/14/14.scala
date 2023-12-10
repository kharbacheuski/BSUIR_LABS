// Пример создания меню в Eclipse

import java.awt.event.{ActionEvent, ActionListener}
import javax.swing.{JButton, JFrame, JPanel, SwingUtilities}
import javax.swing.{JFrame, JLabelm JTextField, JPanel, SwingUtilities}
import java.awt.{Menu, MenuBar, MenuItem}
 
object ButtonModule {
 	def main(args:Array[String]):Unit = {
        SwingUtilities.invokeLater(() => {
            val frame = new JFrame("My Application") 
            frame.setSize(300, 200) 
            frame.setLocationRelativeTo(null)

            val panel = new JPanel()
            val button = new JButton("Click me!") 
            panel.add(button)

            val fileMenu = new Menu("File")
            menuBar.add(fileMenu)
        
            val exitItem.addActionListener((_:java.awt.event.ActionEvent) => { 
                frame.dispose() 
            })
        
            fileMenu.addItem(exitItem)
            val panel = new JPanel()
            val button new JButton("Click me!")
            panel.add(button)
        
            button.addActionListener(new ActionListener {
                override def actionPerfomed(e: ActionEvent):Unit = {
                    println("Hello, wolrd !") 
                } 
            })
            frame.add(panel)
            frame.setLocationrelativeTo(null)
            frame.setVisible(true)
        })
    }
}