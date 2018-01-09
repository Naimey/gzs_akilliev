#include <LiquidCrystal.h> //Lcd kütüphanesi
//#include <SoftwareSerial.h>//bluetooth kütüphanesi
#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#include <Servo.h>  /* Servo kutuphanesi projeye dahil edildi */

#define DHT11PIN 44 // DHT11PIN olarak Dijital 44"yi belirliyoruz.
Servo servoNesnesi;  /* servo motor nesnesi oluşturuldu */

int sistrun = 26; //sistem çalışıyor ledi

//pır için atanan degerler
int pirPin = 35; // PIR pin
int pirled = 30;
int pirled2 = 31;
int pirled3 = 32;
int pirled4 = 33;
int deger = 0;


//mesafe durumunun tanımlamaları----------------------------
String mesafedurumu = "KAPALI";
int mescalled = 24; //mesafe gösteren led
int  kapiacik = 25;  //sıcaklığın çalıştığını gösteren led



//mesafe için atanan degerler
#define trigPin 36    //çalışıyor
#define echoPin 37


String kontrol = "";//sistemin ilk kez mi çalışıp çalışmadığını kontrol eden blok
String baslat = ""; // çalışıp çalışmadığının kontrolü

//lcd tanımlamalarının yapılıyor
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//sicaklik tanımlamaları-------------------
String sicaklikdurumu = "KAPALI";
dht11 DHT11;


int ilk = 0;
int i = 0;

void setup() {
  Serial.begin(9600);

  servoNesnesi.attach(28);
  
  //ledler---------------------
  pinMode(mescalled, OUTPUT);
  pinMode(kapiacik, OUTPUT);
  pinMode(sistrun, OUTPUT);
  
  //mesafe------------------------  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(pirPin, INPUT); // PIR Pin'i giriş yapılıyor
  
  // genel ayarların yapıldığı en başta çalışan blok  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Sicaklik=");
  lcd.setCursor(0,1);
  lcd.print("Mesafe=");
  

}

void loop() {
  
    //setupdan sonra çalışacak olan yer
  kontrol = Serial.readString();

    if(kontrol == "1"){
    baslat = "1";
  }
  else if(kontrol == "2"){
    baslat = "2";
  }

 if(baslat == "1"){
    if (ilk == 0){
      for(i = 0; i < 20; i++){
        
      deger = digitalRead(pirPin);
      int chk = DHT11.read(DHT11PIN);  
      long sure, mesafe;
      
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      sure = pulseIn(echoPin, HIGH);
      mesafe = (sure/2) / 29.1;
      
      
      sicaklikdurumu = "BEKLE";
      mesafedurumu = "BEKLE";
      
      temizle();
      yazdirma(sicaklikdurumu, mesafedurumu);   
    
    ilk++;
      }
    }
    else{
      deger = digitalRead(pirPin);
      int chk = DHT11.read(DHT11PIN);  
      long sure, mesafe;
      
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      sure = pulseIn(echoPin, HIGH);
      mesafe = (sure/2) / 29.1;
      
      Serial.print((float)DHT11.temperature, 2);
      Serial.print("#");
      Serial.print(mesafe);
      Serial.print("#");
      Serial.println(deger);
        sicaklikdurumu = (String)((float)DHT11.temperature);
        
         ////// mesafe yakınlaşınca kapının açılması durumu--------------
        if (mesafe > 10 && mesafe < 20){
          mesafedurumu= "YAKIN";
          temizle();
          yazdirma(sicaklikdurumu, mesafedurumu);
          digitalWrite(mescalled, HIGH);
         servo();
           }
        else if(mesafe <= 10){
          mesafedurumu= "COK YAKIN";
          temizle();
          yazdirma(sicaklikdurumu, mesafedurumu);
        }
        else {  
          mesafedurumu= "UZAK";
          temizle();
          yazdirma(sicaklikdurumu, mesafedurumu);   
          digitalWrite(mescalled, LOW);      
          }

      temizle();
      yazdirma(sicaklikdurumu, mesafedurumu);

      if (deger == HIGH) {
          digitalWrite(pirled, HIGH); // Eğer okunan değer 1 ise LED yakılıyor.
          digitalWrite(pirled4, HIGH); // Eğer okunan değer 1 ise LED yakılıyor.
          digitalWrite(pirled2, HIGH);
          digitalWrite(pirled3, HIGH);
      }
      else{
          digitalWrite(pirled, LOW); // Eğer okunan değer 0 ise LED söndürülüyor.
          digitalWrite(pirled4, LOW); // Eğer okunan değer 1 ise LED yakılıyor.
          digitalWrite(pirled2, LOW);
          digitalWrite(pirled3, LOW);
      }     

    }
 }
  else { 
    digitalWrite(mescalled, LOW);
    sistemkapali();
  }
  
delay(378);
}

void sistemkapali(){
  
    mesafedurumu = "KAPALI";
    sicaklikdurumu = "KAPALI";
    temizle();
    yazdirma(sicaklikdurumu, mesafedurumu); //alınan durumlar lcd ye yazılıyo
}
void servo(){
   servoNesnesi.write(10000);  /* Motorun mili 100. dereceye donuyor */
  delay(3780);
  servoNesnesi.write(-10 000);   /* Motor mili 20. dereceye donuyor */
  delay(1000);
  digitalWrite(mescalled, HIGH);//mesafe sınırları içine girdi kapı açıldığı için le yanar
}
void yazdirma(String m, String d){ //m mesafe durumu yazar,d sıcaklık durumu yazar
  lcd.setCursor(9,0);
  lcd.print(m);
  lcd.setCursor(7,1);
  lcd.print(d);
}

void temizle(){
  lcd.setCursor(9,0);
  lcd.print("           ");
  lcd.setCursor(7,1);
  lcd.print("          ");
}
