/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sınıflar;

import databaseislem.baglan;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 *
 * @author loop
 */
public class giris {
    PreparedStatement ps;
    ResultSet rs;
    
    public boolean sistemgirisi(String username, String password) throws SQLException{
        baglan veritabaniBaglan = new baglan();
        veritabaniBaglan.veritabanibaglan();
        
        String sorgu = "SELECT password FROM users WHERE username = ?";
        
        ps = veritabaniBaglan.conn.prepareStatement(sorgu);
        ps.setString(1, username);
        rs = ps.executeQuery();
        while(rs.next()){
            String dbPassword = rs.getString("password");
            if(dbPassword.equals(password)){
               
                return true;
            }
            else
                return false;
        }
        return false;
    }
    
}
