import java.awt.event.{ActionEvent, ActionListener}
import javax.swing.{JButton, JFrame, JPanel, SwingUtilities}
import java.awt.Dimension
import javax.swing.{JFrame, JLabel, JTextField, JPanel, SwingUtilities, JTextArea }
import java.awt.Color
import java.awt.{Menu, MenuBar, MenuItem}

object Menu  {
  val frame = new JFrame("My Application")
  frame.setSize(800, 600)
  frame.setLayout(null)
  
  def main(args: Array[String]): Unit = {
    SwingUtilities.invokeLater(() => {
      val button1 = new JButton("Home")
      val button2 = new JButton("About")
      val button3 = new JButton("Contacts")
      val button4 = new JButton("Products")
      val button5 = new JButton("Close")
     
      
      button1.setBounds(20,80,120,20)
      
//      button1.setBackground(Color.PINK)
//      button1.setForeground(Color.GREEN)
      
      button2.setBounds(150,80,120,20)
      button3.setBounds(280,80,120,20)
      button4.setBounds(410,80,120,20)
      button5.setBounds(540,80,120,20)

      
      frame.add(button1)
      frame.add(button2)
      frame.add(button3)
      frame.add(button4)
      frame.add(button5)
      
        
      button1.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
              println("hello world")
          }
       })
       
       button2.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
              println("go back")
          }
       })
       button5.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
              frame.dispose()
          }
       })

      frame.setVisible(true)
    })
  }
}
