/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sınıflar;

import databaseislem.baglan;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 *
 * @author loop
 */
public class VeritabaniEkle {
    PreparedStatement ps;
    
    public void sicaklikekle(String sicaklik, String kullanici) throws SQLException{
        
        baglan veritabiBaglan = new baglan();
        veritabiBaglan.veritabanibaglan();
        
        String sql = "insert into sicalik(sicaklik_deger, user_id)"
                + "values(?, (select user_id from users where username = ?))";
        ps = veritabiBaglan.conn.prepareStatement(sql);
        ps.setString(1, sicaklik);
        ps.setString(2, kullanici);
        ps.execute();
              
    }
    
     public void mesafeEkle(String mesafe, String kullanici, boolean acik) throws SQLException{
        
        baglan veritabiBaglan = new baglan();
        veritabiBaglan.veritabanibaglan();
        
        String sql = "insert into mesafe(mesafe_deger, user_id, acik_kapali)"
                + "values(?, (select user_id from users where username = ?), ?)";
        ps = veritabiBaglan.conn.prepareStatement(sql);
        ps.setString(1, mesafe);
        ps.setString(2, kullanici);
        ps.setBoolean(3, acik);
        ps.execute();
              
    }
}
