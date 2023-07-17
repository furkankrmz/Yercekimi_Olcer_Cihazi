//------------------------------------------------------------------
// yerbukucu.ino
// Bu program ...
// yazar: Ahmet Furkan Kırmızı
// tarih: Aug 2018
//------------------------------------------------------------------
#include "SevSeg.h"
SevSeg sevseg;
int led=51; //51.pine Infrared ledi sistemimize tanıtıyoruz
int in3=52; //52.pine motor sürücünün pin tanımlamasını yapıyoruz
int in4=50; //50.pine motor sürücünün pin tanımlamasını yapıyoruz
int b1 =46; //46.pine butonun tanımlamasını yapıyoruz 
int b1d;//butona basılıp basılmadığını anlamak için de b1d yi sistemimize tanıtıyoruz

long int t1=0, t2=0, dt;//burada zamanı belirlemek için kullandığımız elemanları tanımlıyoruz
uint8_t limit=20;//sensörümüz yirmi değerini geçerse diğer işlemer gerçekleşeceği için sensörümüze bir limit değeri atadık
void setup() {
 Serial.begin(9600);//Serial portu başlattık 
 pinMode(b1,INPUT);//butonu giriş olarak tadık 
 pinMode(50, OUTPUT);//motorsürücü pinini çıkış olarak atadık 
 pinMode(52, OUTPUT);//motorsürücü pinini çıkış olarak atadık 
 digitalWrite(51,HIGH);//ledimiz cihaz çalıştığı sürece çalışacağı için şimdiden çalıştırıyoruz
 
 byte numDigits = 4;//+
 byte digitPins[] = {2, 3, 4, 5};
 byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};//+
 sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);//+
 sevseg.setBrightness(90);//+
 sevseg.setNumber(0);//burada seven segmentimize başlangıç olarak 0 yazmasını istiyoruz
 sevseg.refreshDisplay();
 //yukarıdaki satırsonlarında "+" olan kodlar seven segment kütüphanesinde yer alan seven segmentin bağlantılarının tanımlı olduğu kod satırları
}

void loop() {
  //int val = analogRead(A0);
  b1d = digitalRead(b1);//butonumuzun basılıp basılmadığını anlamak için butonumuzu b1d değerine atıyoruz
  digitalWrite(52,HIGH);//motor sürücü butona basılmadığında sürekli çalışmasını sağlamak için yazdığımız kod satırı
  digitalWrite(50,LOW);//motor sürücü butona basılmadığında sürekli çalışmasını sağlamak için yazdığımız kod satırı
  t1 = 0;

  if(b1d==HIGH)//eğer butona basılırsa
  {                       //butona bastığımızda seven segmente hala 0 olma komutu veriyoruz
     sevseg.setNumber(0);//eğer bunu yapmazsak seven segment hemen birşeyler yazmaya başlar ve biz de bunu istemediğimiz için için bu kodu yazıyoruz    
          
     sevseg.refreshDisplay();
     digitalWrite(52,LOW);//butona basıldığında lektro mıknatısa bağlı cismin düşmesi için motor sürücü pinlerine "LOW"komutu gönderiyoruz
     digitalWrite(50,LOW);//butona basıldığında lektro mıknatısa bağlı cismin düşmesi için motor sürücü pinlerine "LOW"komutu gönderiyoruz
     t1 = millis();//t1 değerini (milisaniye cinsinden ) başlatıyoruz
   
  }
  else{
     //digitalWrite(52,HIGH);
     //digitalWrite(50,LOW);
  }

  //eğer t1 değeri sıfırdan büyükse ve ayrıca aşağıda while dögüsünün olduğu satırı görmekteyiz bu ise 
  // koyduğumuz şart ile bağlantılı //eğer bu şart erçekleşir ve sensörün ölçdüğü değerler 20 den yani 
  // limit değerimizden küçük olursa hiç bişey yapma diyoruz
  if(t1>0)
  {       
    while(analogRead(A0)<limit){
      // bos dongu
    }
    t2 = millis();// t2 zamanını al 
    dt = t2-t1;    //zaman farkı 
    Serial.println(dt); // seri port ekranına yazdır

  }

    sevseg.setNumber(dt);//burada da dt değerini seven segmente yazdırıyoruz 
    sevseg.refreshDisplay();
}

