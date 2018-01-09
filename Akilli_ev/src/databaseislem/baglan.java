/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package databaseislem;

import java.sql.Connection;
import java.sql.DriverManager;
import javax.swing.JOptionPane;

/**
 *
 * @author loop
 */
public class baglan {
    private String url ="jdbc:mysql://localhost:3306/";
    private String driver ="com.mysql.jdbc.Driver";
    private String dbname ="db_akilli";
    private String username ="root";
    private String password ="";
    
    public Connection conn;
    
     public void veritabanibaglan(){
        try{
            
            Class.forName(driver).newInstance();
            conn = (Connection)DriverManager.getConnection(url+dbname,
                    username, password);
            System.out.println("Bağlantı Başarılı.");
            
        }
        catch(Exception e){
            JOptionPane.showMessageDialog(null, "Bağlantı Başarısız Hata: "
                    + e);
            System.out.println("Bağlantı Başarısız Hata: "+ e);
        }
    }
}
