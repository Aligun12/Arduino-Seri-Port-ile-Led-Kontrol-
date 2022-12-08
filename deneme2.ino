int led1 = 13,yanma=300,sonme=2000,baudrate=115200; 
String okunan = "";
bool durum=true;
bool okundu=false;

void setup() {
  pinMode(led1, OUTPUT); //ledin çıkış olarak ayarlanması
  Serial.begin(baudrate); //seri haberleşmenin başlatılması
}
 
void loop() {
  
  if(okundu){ // Seri bilginin okundu kontrolü
  if(okunan=="stop"){ // stop komutu 
    durum=false;
    Serial.print("DURDURULDU\nGelen Veri: "+okunan+"\n");}
  if(okunan=="start"){ // start komutu
    durum=true; 
    Serial.print("BASLATILDI\nGelen Veri: "+okunan+"\n");}
  if (okunan.indexOf("ledon")!=-1) { //gelen string içerisinde ledon içerme kontrolü
    String deger = okunan.substring(6); // eşittirden sonrasını ayırma
    Serial.print("ACIK DURUMU ICIN GIRILEN SURE: "+deger+" \nGelen Veri: "+okunan+"\n");
    int aaa=deger.toInt(); // ayrılan değeri int çevirme
    yanma=aaa; // yanma değerine girlen değeri atama
    } 
  if (okunan.indexOf("ledoff")!=-1) {//gelen string içerisinde ledoff içerme kontrolü
    String deger = okunan.substring(7);// eşittirden sonrasını ayırma
    Serial.print("KAPALI DURUMU ICIN GIRILEN SURE: "+deger+" \nGelen Veri: "+okunan+"\n");
    int bbb=deger.toInt();// ayrılan değeri int çevirme
    sonme=bbb; // sönme değerine girilen değeri atama
    }
  if (okunan.indexOf("baudrate")!=-1) {//gelen string içerisinde ledoff içerme kontrolü
    String deger = okunan.substring(9);// eşittirden sonrasını ayırma
    Serial.print("KAPALI DURUMU ICIN GIRILEN SURE: "+deger+" \nGelen Veri: "+okunan+"\n");
    int bb=deger.toInt();// ayrılan değeri int çevirme
    baudrate=bb; // sönme değerine girilen değeri atama
  }
  if(okunan=="help"){ // yardım komutu
    Serial.print("Sistemi durdurmak icin 'stop' komutunu kullanınız.\nSistemi baslatmak icin 'start' komutunu kullanınız.\nLed yanma süresini ayarlamak icin 'ledon=sure' yaziniz.\nLed sonme suresini ayarlamak icin 'ledoff=sure' yaziniz\n");
  }
  else{Serial.print("Yanlıs Komut Girdiniz! Komutlara Erismek Icin help yaziniz.\n");} //yanlış komut girildğinde gelicek uyarı
  okunan = ""; // gelen stringin atandığı değerin temizlenmesi
  okundu=false; // okundu bilgisinin false olması
  }


  if(durum){ // durum kontrolü
    digitalWrite(led1,HIGH); // ledin yanması
    delay(yanma); //bekleme
    digitalWrite(led1,LOW); //ledin sönmesi
    delay(sonme); //beklene
  }
  else{
    digitalWrite(led1, !digitalRead(led1));//ledin karşı değere geçmesi
    delay(1000); // 1 sn bekleme
  }

}

void serialEvent() { // Seri Porttan bilgi geldiğinde interrupt uygulayan arduino fonksiyonu.
  if (Serial.available() > 0) {//Seri Bilgi Geliyormu
    okunan = Serial.readString();//okunan bilgiyi string olarak tutma
    okundu=true;  //okundu bilgisi
  }
}