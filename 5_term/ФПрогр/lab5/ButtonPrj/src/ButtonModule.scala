import java.awt.event.{ActionEvent, ActionListener}
import javax.swing.{JButton, JFrame, JPanel, SwingUtilities}
import java.awt.Dimension
import javax.swing.{JFrame, JLabel, JTextField, JPanel, SwingUtilities, JTextArea }
import java.sql.{Connection, DriverManager, ResultSet}
import java.awt.Color

object ButtonModule  {
  val frame = new JFrame("My Application")
  frame.setSize(800, 600)
  frame.setLayout(null)
  
  def main(args: Array[String]): Unit = {
    SwingUtilities.invokeLater(() => {
    
      val label1 = new JLabel("Title")
      val label2 = new JLabel("Price")
      val label3 = new JLabel("Count")
      val label4 = new JLabel("Answer")
      
      label1.setBounds(50,120,100,20)
      label2.setBounds(200,120,70,20)
      label3.setBounds(350,120,70,20)
      label4.setBounds(50,180,70,20)
      
      val button1 = new JButton("Insert")
      val button2 = new JButton("Select")
      val button3 = new JButton("Best product")
      val button4 = new JButton("> count")
      val button5 = new JButton("Sum of elems")
      val button6 = new JButton("Any")
      val textField = new JTextField(20)
      val textField2 = new JTextField(20)
      val textField3 = new JTextField(20)
      val textArea = new JTextArea("")
      
      textArea.setLineWrap(true);
      textArea.setWrapStyleWord(true);
      
      button1.setBounds(20,80,120,20)
      
      button1.setBackground(Color.PINK)
      button1.setForeground(Color.GREEN)
      
      
      button2.setBounds(150,80,120,20)
      button3.setBounds(280,80,120,20)
      
      button3.setBackground(Color.PINK)
      button3.setForeground(Color.GREEN)
      
      button4.setBounds(410,80,120,20)
      button5.setBounds(540,80,120,20)
      button6.setBounds(670,80,120,20)
      textField.setBounds(20,150,130,20)
      textField2.setBounds(160,150,130,20)
      textField3.setBounds(300,150,130,20)
      textArea.setBounds(20,210,260,200)

      
      frame.add(button1)
      frame.add(button2)
      frame.add(button3)
      frame.add(button4)
      frame.add(button5)
      frame.add(button6)
      frame.add(label1)
      frame.add(label2)
      frame.add(label3)
      frame.add(label4)
      frame.add(textField)
      frame.add(textField2)
      frame.add(textField3)
      frame.add(textArea)
      
      val url = "jdbc:mysql://localhost:3306/scala"
      val username = "root"
      val password = "******"
      Class.forName("com.mysql.cj.jdbc.Driver")
      
        
      button1.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
            val conn = DriverManager.getConnection(url, username, password)
     
            try {
              val stmt = conn.createStatement()
              val rs = stmt.execute("INSERT INTO sklad(product, price, count) VALUES ('" + textField.getText + "', '" + textField2.getText + "', '" + textField3.getText + "')")
            
              textField2.setText("")
              textArea.setText("Record added")
            } 
            finally {
              conn.close()
            }
          }
       })
       
       button2.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
            val conn = DriverManager.getConnection(url, username, password)
     
            try {
              val stmt = conn.createStatement()
              val prod_name= textField.getText().toString().trim()
              val rs = stmt.executeQuery("SELECT * FROM sklad WHERE product = '" + prod_name + "'")
            
               while (rs.next()) {
                   val name = rs.getString("product")
                   val real_price = rs.getInt("price")
                   val count = rs.getInt("count")
                   
                   textArea.append("\n" + "name: " + name + ", price: " + real_price + ", count: " + count)
               }
            } 
            finally {
              conn.close()
            }
          }
       })

       button4.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
            val conn = DriverManager.getConnection(url, username, password)
        
            try {
               val stmt = conn.createStatement()
               val price = textField2.getText().toString()
               
               val rs = stmt.executeQuery("SELECT * FROM sklad WHERE price > " + price )
               
               textArea.setText("")
               
               while (rs.next()) {
                   val name = rs.getString("product")
                   val real_price = rs.getInt("price")
                   val count = rs.getInt("count")
                   
                   textArea.append("\n" + "name: " + name + ", price: " + real_price + ", count: " + count)
               }
             } 
             finally {
                conn.close()
             }
        }
      })
      
      
      button3.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
            val conn = DriverManager.getConnection(url, username, password)
     
            try {
              val stmt = conn.createStatement()
              val rs = stmt.executeQuery("SELECT product, MAX(price*count) AS max_price FROM sklad GROUP BY product");
            
              textArea.setText("");
              
              while (rs.next()) {
                val name = rs.getString("product")
                val mx = rs.getInt("max_price")

                textArea.append("\n" + name + " price: " + mx)
              }

            } 
            finally {
              conn.close()
            }
          }
       })
       
       button5.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
            val conn = DriverManager.getConnection(url, username, password)
     
            try {
              val stmt = conn.createStatement()
              val rs = stmt.executeQuery("SELECT product, SUM(price) as sumpr FROM sklad group by product")
              
              textArea.setText("");
              
              while (rs.next()) {
                val price = rs.getInt("sumpr")
                val name = rs.getString("product")
           
                textArea.append("\nname: " + name + ", price = " + price)
              }
            } 
            finally {
              conn.close()
            }
          }
       })
       
       
      button6.addActionListener(new ActionListener {
          override def actionPerformed(e: ActionEvent): Unit = {
            val conn = DriverManager.getConnection(url, username, password)
     
            try {
              val stmt = conn.createStatement()
              val rs = stmt.executeQuery("SELECT product FROM sklad WHERE id = ANY (SELECT id FROM sklad where price > 100)")
              
              textArea.setText("");
              
              while (rs.next()) {
                val product_name = rs.getString("product")
           
                textArea.append("\nname = " + product_name)
              }
            } 
            finally {
              conn.close()
            }
          }
       })

      frame.setLocationRelativeTo(null)
      frame.setVisible(true)
      frame.getContentPane.setBackground(Color.ORANGE)
    })
  }
}
