#include<avr/wdt.h>

#include <Wire.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ExtEEPROM.h>
#include <EEPROMAnything2.h>
#include "RTClib.h"
#include <DS3231.h>

#include <EEPROM.h>
#include <Time.h>  
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//#include <LiquidCrystal.h>
//LiquidCrystal lcd (7, 6, 5, 4, 3, 2);



RTC_DS3231 rtc;
DS3231 clock;
RTCDateTime dt;





/*-----( Declare Constants and Pin Numbers )-----*/
#define ONE_WIRE_BUS_PIN 12
OneWire oneWire(ONE_WIRE_BUS_PIN);

DallasTemperature sensors(&oneWire);

//Peti
/*
DeviceAddress KOLL = { 0x28, 0xF2, 0xAF, 0x4D, 0x08, 0x00, 0x00, 0x06 };
DeviceAddress KINT = { 0x28, 0x82, 0x2F, 0x4E, 0x08, 0x00, 0x00, 0xDD };
DeviceAddress PT4 = { 0x28, 0x30, 0x88, 0x4E, 0x08, 0x00, 0x00, 0xD6 };
DeviceAddress PT3 = { 0x28, 0x80, 0x6B, 0x4D, 0x08, 0x00, 0x00, 0xCD };
DeviceAddress PK2 = { 0x28, 0xA7, 0x8B, 0x4D, 0x08, 0x00, 0x00, 0x24 };
DeviceAddress PA1 = { 0x28, 0xCB, 0xEE, 0x4D, 0x08, 0x00, 0x00, 0x59 };
*/

//munka

DeviceAddress KOLL = { 0x28, 0x98, 0x3C, 0x79, 0xA2, 0x01, 0x03, 0x0F }; 
DeviceAddress KINT = { 0x28, 0xE1, 0xE7, 0x79, 0xA2, 0x01, 0x03, 0x2F };
DeviceAddress PT4 = { 0x28, 0x29, 0x16, 0x43, 0x98, 0x05, 0x00, 0x44 }; 
DeviceAddress PT3 = { 0x28, 0x19, 0xE7, 0x79, 0xA2, 0x00, 0x03, 0x38 };
DeviceAddress PK2 = { 0x28, 0xAF, 0x96, 0x79, 0xA2, 0x00, 0x03, 0x2D };
DeviceAddress PA1 = { 0x28, 0xFF, 0xFF, 0xC8, 0x6D, 0x18, 0x01, 0xD5 };


//otthon
/*
DeviceAddress KOLL = { 0x28, 0x59, 0x30, 0x79, 0xA2, 0x01, 0x03, 0x86 }; 
DeviceAddress KINT = { 0x28, 0x55, 0x5E, 0x79, 0xA2, 0x00, 0x03, 0x8C };
DeviceAddress PT4 = { 0x28, 0x6D, 0xEC, 0x79, 0xA2, 0x00, 0x03, 0x0C };
DeviceAddress PT3 = { 0x28, 0x4B, 0x83, 0x79, 0xA2, 0x00, 0x03, 0x76 };
DeviceAddress PK2 = { 0x28, 0x67, 0xFB, 0x79, 0xA2, 0x00, 0x03, 0xEE };
DeviceAddress PA1 = { 0x28, 0x8F, 0xBE, 0x79, 0xA2, 0x00, 0x03, 0x5D };
*/


//encoder
int encoder0PinA = 7;
int encoder0PinB = 6;
int encoder0PinALast = LOW;
int ZSIK = LOW;
//

int ev = 2020;
byte honap = 03;
byte nap = 21;
byte ora = 03;
byte perc = 12;
 
 

#define PwmKim 11
int led = 13;
byte KL  = 0;
byte KLA  = 0;

byte E ;
byte val = 3;
byte valI = 0;
byte valA = 0;
byte valB = 0;

byte ZZSO = 0;
byte ELEKTFBEKI;
byte FUTESBEKI; 
byte FOLYSZAK; //folyamatosan, vagy szakaszosan menjen a ház fűtése




byte A = 0;
byte B = 0;
byte C = 0;
//byte D = 0;
byte BB;  //menny időzitést szeretnél
byte I; 
//byte z;

byte G; //unixkiirhoz hogy csak eccer fusson le



byte teszt = 128;
//byte memory = 128;
byte x;
//byte q = 1;
byte n;
byte m;

byte ORA;
byte PERC;
//byte y = 1;




byte b = 0;


byte PUFFIT1B = EEPROM.read(1);
byte PUFFIT2B = EEPROM.read(2);
byte PUFFIKB = EEPROM.read(10);
byte PUFFIAB = EEPROM.read(4);
byte KOLLEKTORB = EEPROM.read(5);
byte KOLLHISZB = EEPROM.read(6);
byte PUFFMAX = EEPROM.read(20);

byte OraI;      //Óra Indul Elektromos Fűtés
byte PercI;
byte OraV;      //Óra vége Elektromos Fűtés 
byte PercV;



byte AA;
//byte AramSZ = 1;
//byte Aram[] = {1,2,3,4,5,6,7,8,9,10,11,12};


byte BEKI[] = {1,2,3,4,5,6,7,8,9,10,11,12};
byte OraIF[] = {1,2,3,4,5,6,7,8,9,10,11,12};
byte PercIF[] = {1,2,3,4,5,6,7,8,9,10,11,12};
byte OraVF[] = {1,2,3,4,5,6,7,8,9,10,11,12};       //Óra vége Keringető Fűtés
byte PercVF[] = {1,2,3,4,5,6,7,8,9,10,11,12};   //Perc vége Keringető Fűtés

byte OraIndulElektromosFutes;
byte PercIndulElektromosFutes;
byte OraVegeElektromosFutes;
byte PercVegeElektromosFutes;

unsigned long IAO2;
unsigned long IIO2;
unsigned long IVO2;





unsigned long ardup;
byte ORAAktualis;
byte PercAktualis;
byte SecAktualis;
unsigned long ido;
//float RTCTemp ;
unsigned long UniX;
//unsigned long UniXAktIdo;
//unsigned long UniXKIIdo;
byte KK1,KK2,KK3,KK4,KK5,KK6,KK7,KK8,KK9,KK10;
//byte WW1,WW2,WW3,WW4,WW5,WW6,WW7,WW8,WW9,WW10;

unsigned long CC; // megoldottam "UL" kell írni a az osztó szmok után  pl: 6 * 10000= 60000 de ő ezt "int" nek veszi a "10000UL" -el már jó 
byte CC1,CC2,CC3,CC4,CC5; 
//unsigned long XX[]= {1,2,3,4,5,6,7,8,9,10,11,12};//teszt

unsigned long IAO;//teszt
unsigned long IIO[]= {1,2,3,4,5,6,7,8,9,10,11,12};//teszt
unsigned long IVO[]= {1,2,3,4,5,6,7,8,9,10,11,12};//teszt
byte HH;
byte UU;

//byte ZZ1,ZZ2,ZZ3,ZZ4,ZZ5;

//byte SOK;
byte MENUV;
byte VISSZA;
//byte QQ = 0;
//byte ZZS = 1;
byte BEARMSZ;



//unsigned long FF;
//unsigned long EE;
byte DD = 0 ;
//unsigned long IDOmpBen1,IDOmpBen2,IDOmpBen3,IDOmpBen4,IDOmpBen5,IDOmpBen6,IDOmpBen7,IDOmpBen8,IDOmpBen9,IDOmpBen10,IDOmpBen11,IDOmpBen12;



byte PwmKitolt = 50;
byte SENSOR ;
byte PUFFKISENSOR ;


const byte RELEKE = A0;    //rele keringeto haz felé
const byte RELEFUTES = A1;    //elektromos fűtéshez a relé
const byte Pityogo = A2;      //az 2es kemeneten relé ki lett kotve mert ott megy ki a pwm aszem a 11es lábon
const byte PIROSLED = A3;    //piros led
//A4 SDA I2C
//A5 SDC I2C
//A6 csak bement lehet
//A7 csak bement lehet


const byte MINUS = 10;      //gomb minusz
const byte ENTER = 9;      //gomb enter
const byte PLUS = 8;        //gomb plusz


//https://omerk.github.io/lcdchargen/



//ennyi lehet max, az valamelyik betüt kicseréltem 

byte uu[8] = {
	0b00101,
	0b01010,
	0b00000,
	0b10001,
	0b10001,
	0b10001,
	0b11111,
	0b00000
};


byte uz[8] = {
	0b00000,
	0b01010,
	0b00000,
	0b10001,
	0b10001,
	0b10001,
	0b11111,
	0b00000
};


byte oo[8] = {
	0b00010,
	0b00100,
	0b01000,
	0b11111,
	0b00010,
	0b10100,
	0b10000,
	0b11100
};
byte aa[8] = {
	0b00010,
	0b00100,
	0b01110,
	0b00001,
	0b01111,
	0b10001,
	0b01111,
	0b00000
};
byte oa[8] = {
	0b01010,
	0b00000,
	0b01110,
	0b10001,
	0b10001,
	0b10001,
	0b01110,
	0b00000
};
byte ee[8] = {
	0b00010,
	0b00100,
	0b01110,
	0b10001,
	0b11111,
	0b10000,
	0b01110,
	0b00000
};
byte oi[8] = {
	0b00010,
	0b00100,
	0b01110,
	0b10001,
	0b10001,
	0b10001,
	0b01110,
	0b00000
};
byte ii[8] = {
	0b00010,
	0b00100,
	0b01100,
	0b00100,
	0b00100,
	0b00100,
	0b01110,
	0b00000
};





void setup()   /****** SETUP: RUNS ONCE ******/
{
  // start serial port to show results
 Serial.begin(9600);
 Wire.begin();
 clock.begin();
 wdt_enable (WDTO_8S);// az állási idő behatárolása
 lcd.init();                      // initialize the lcd 
 lcd.backlight();
 
 
  sensors.begin();
  
  // set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
  sensors.setResolution(KOLL, 10);  
  sensors.setResolution(KINT, 10);
  sensors.setResolution(PT4, 10);
  sensors.setResolution(PT3, 10);
  sensors.setResolution(PK2, 10);
  sensors.setResolution(PA1, 10);
  
  //bemenet kimenet beallitasa
  pinMode(PLUS,INPUT);    //gommb plusz bemenet
  pinMode(ENTER,INPUT);      // gomb enter bement
  pinMode(MINUS,INPUT);      //gomb minus bement
  pinMode(RELEKE,OUTPUT);    //rele keringetö haz felé
  pinMode(RELEFUTES,OUTPUT);   //Rele napkollektor
  pinMode(PIROSLED, OUTPUT);   //hiba jelző led
  pinMode(Pityogo, OUTPUT);
  pinMode (encoder0PinA, INPUT);  //encoder
  pinMode (encoder0PinB, INPUT);  //encoder
   
  
  
  
  

EEPROM_readAnything(33, BB); //mennyi időzités van beállítva
EEPROM_readAnything(34, A);  //hol ált  a relé, behúzott, vagy elengedett
EEPROM_readAnything(35, OraI);  //Óra Indul Elektromos Fűtés
EEPROM_readAnything(36, PercI);
EEPROM_readAnything(37, OraV);      //Óra vége Elektromos Fűtés 
EEPROM_readAnything(38, PercV);
EEPROM_readAnything(39, ELEKTFBEKI);
EEPROM_readAnything(40, FUTESBEKI);
EEPROM_readAnything(41, FOLYSZAK);
EEPROM_readAnything(42, AA);
//EEPROM_readAnything(43, SOK); //változott-e valami az időzitésben
//44üres
//45-tól 5tösével az időzitésben megadott idő másodpercben
//104ig
//110-114ig  Unix aktualis ido utolsó 5 karaktere
    
  
  
  
  

//kimenetek 0-ra húzása
digitalWrite (RELEKE, LOW); 
digitalWrite (RELEFUTES, LOW);

 
  lcd.createChar(7, uu); //ű betű
  lcd.createChar(6, oo); //megbasz az áram jel
  lcd.createChar(5, aa); //á betű
  lcd.createChar(4, oa); //ö betű
  lcd.createChar(3, uz); //ü betű
  lcd.createChar(2, ee); //é betű
  lcd.createChar(1, oi); //ó betű
  
  

  lcd.begin(20,4);
  lcd.clear();
  //lcd.setCursor(6,0);
  //lcd.print("Heged\007s");
  //lcd.setCursor(4,1);
  //lcd.print("Sufni_tuning");
  //delay(2000);
  //lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Creadted by HST"); 
  //lcd.setCursor(1,2);
  //lcd.print("hokusz22@gmail.com");
  lcd.setCursor(7,3);
  lcd.print(":-)");
  delay(2000);
  lcd.clear();  
  
  
  

 
  wdt_reset();
  
  
  
 //venti frekvencia megnovelneni mert nyoszorog alap 490Hz nyomjuk meg phase-correct-re az 31372.55 Hz

TCCR2B = TCCR2B & 0b11111000 | 0x03; //csak a 11-es es a 3-as labra vonatkozik, ha mas lab kell a TCCRxB kell valtoztattni a weboldal szerint
                                     // de ha a TCCR0B labbat akarod(5,6) akkor elmaszik az idozites ferkveniafuggon  delay(64000) or 64000 millis() ~ 1 second (Default: delay(1000) or 1000 millis() ~ 1 second)
//http://playground.arduino.cc/Main/TimerPWMCheatsheet
  
  /*Pins 11 and 3: controlled by timer 2 in phase-correct PWM mode (cycle length = 510)
Setting 	Divisor 	Frequency
0x01 	 	1  		31372.55
0x02 	 	8 	 	3921.16
0x03  		32  		980.39-
0x04 	 	64 	 	490.20   <--DEFAULT
0x05 	 	128  		245.10
0x06  		256  		122.55
0x07 	 	1024  		30.64

TCCR2B = (TCCR2B & 0b11111000) | <setting>;*/

//ezt is szedd ki
//rtc.adjust(DateTime(2018, 8, 18, 10, 59, 30));




}//--(end setup )---



void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
 
DateTime now = rtc.now();  
dt = clock.getDateTime(); //RTC idő
//clock.forceConversion();  //RTC hőmérséklet 
sensors.requestTemperatures();  //ds18B20

ORAAktualis = dt.hour;
PercAktualis = dt.minute;
SecAktualis = dt.second;
UniX = dt.unixtime;
ardup = millis();

//Serial.println(ardup);

if ( ardup >  604800000UL ){
    asm volatile ("  jmp 0");   //soft reset
    }

//float RTCTemp = clock.readTemperature();



//if (digitalRead(ENTER) == HIGH && digitalRead(PLUS) == HIGH && digitalRead(MINUS) == LOW)
if (digitalRead(ENTER) == HIGH)
  {
    
       
    lcd.clear();
          lcd.print("Engedd el !!!");
          delay(2000);
          
          wdt_disable();
          do
          {
           lcd.clear();
            lcd.setCursor(2,0);
            lcd.print("Homerseklet_Beall."); 
            lcd.setCursor(2,1);
            lcd.print("Elektromos Fu.Idoz");
            lcd.setCursor(2,2);
            lcd.print("Haz Fu.Idozito");
            
            
            do
            {              
                    ZSIK = digitalRead(encoder0PinA);
                    if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                    {
                       if (digitalRead(encoder0PinB) == HIGH)
                       {
                        MENUV ++;                                           
                        } 
                          else 
                          {
                            MENUV --; 
                          }
                    }
                    encoder0PinALast = ZSIK;
                    
                    if (MENUV == 1)
                    {
                        lcd.setCursor(0,0);
                        lcd.print(">");
                        lcd.setCursor(0,1);
                        lcd.print(" ");
                        lcd.setCursor(0,2);
                        lcd.print(" ");
                    }
                    if (MENUV == 2)
                    {
                        lcd.setCursor(0,0);
                        lcd.print(" ");
                        lcd.setCursor(0,1);
                        lcd.print(">");
                        lcd.setCursor(0,2);
                        lcd.print(" ");
                      }
                    if (MENUV == 3)
                      {
                        lcd.setCursor(0,0);
                        lcd.print(" ");
                        lcd.setCursor(0,1);
                        lcd.print(" ");
                        lcd.setCursor(0,2);
                        lcd.print(">");
                      }
                        
                    if (MENUV > 3 ){
                      MENUV = 1;}
                      
                    if (MENUV < 1 ){
                      MENUV = 3;}    
      
           }while(digitalRead(ENTER) == LOW);
            }while(digitalRead(ENTER) == LOW);
          delay(1000);
          
          
          
          
          
//innen service menu
//innen service menu de benne kell lenni az elozo menuben, mert alapbol nem megy              
if (digitalRead(ENTER) == HIGH && digitalRead(PLUS) == LOW && digitalRead(MINUS) == HIGH)                  
   {       
     lcd.clear();
     lcd.print("Ereszted el !!!");  
     delay(4000); 
                  do
                  {      
                    lcd.clear(); 
                           
                                  do
                                { 
                              lcd.setCursor(0,0);
                              lcd.print("Datum:20");                               
                              lcd.setCursor(6,0);
                              lcd.print(ev);
                              
                              delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                    {
                                       ev = ev + 1;
                                    if (ev > 2050){ ev = 2018; }  
                                     }
          
          
                                    if (digitalRead(MINUS) == HIGH)
                                      {
                                        ev = ev - 1 ;
                                      if (ev < 2018){ ev = 2050; }
                                       }    
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(500);
                              
                                 
                                 
                               
                                  do
                                { 
                              lcd.setCursor(10,0);
                              lcd.print("-");
                              
                              lcd.setCursor(11,0);
                              lcd.print(honap);
                              
                              if ( honap < 10 )
                              {
                                lcd.setCursor(12,0);
                                lcd.print(honap);
                                lcd.setCursor(11,0);
                                lcd.print("0");
                              }
                              
                           
                               delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                    {
                                       honap = honap + 1;
                                    if (honap > 12){ honap = 1; }  
                                     }
          
          
                                    if (digitalRead(MINUS) == HIGH)
                                      {
                                        honap = honap - 1 ;
                                      if (honap < 1){ honap = 12; }
                                       }
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(500);
                                 
                                                             
                                 
                                  do
                                { 
                              lcd.setCursor(13,0);
                              lcd.print("-");
                              
                              lcd.setCursor(14,0);
                              lcd.print(nap);
                              if ( nap < 10 )
                              {
                                lcd.setCursor(15,0);
                                lcd.print(nap);
                                lcd.setCursor(14,0);
                                lcd.print("0");
                              }
                              
                               delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                    {
                                       nap = nap + 1;
                                    if (nap > 31){ nap = 1; }  
                                     }
          
          
                                    if (digitalRead(MINUS) == HIGH)
                                      {
                                        nap = nap - 1 ;
                                      if (nap < 1){ nap = 31; }
                                       }
                                       
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(500);
                                 
                                 
                                 
                                 
                                  do
                                { 
                              lcd.setCursor(0,1);
                              lcd.print("Ora:");
                              lcd.setCursor(4,1);
                              lcd.print(ora);
                              if ( ora < 10 )
                              {
                                lcd.setCursor(5,1);
                                lcd.print(ora);
                                lcd.setCursor(4,1);
                                lcd.print("0");
                              }
                               delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                    {
                                       ora = ora + 1;
                                    if (ora > 23){ ora = 0; }  
                                     }
          
          
                                    if (digitalRead(MINUS) == HIGH)
                                      {
                                        ora = ora - 1 ;
                                      if (ora < 0){ ora = 23; }
                                      if (ora == 255){ ora = 23; } 
                                       }
      
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(500);
                                 
                                 
                                  do
                                { 
                              lcd.setCursor(6,1);
                              lcd.print(":");
                              lcd.setCursor(7,1);
                              lcd.print(perc);
                              if ( perc < 10 )
                              {
                                lcd.setCursor(8,1);
                                lcd.print(perc);
                                lcd.setCursor(7,1);
                                lcd.print("0");
                              }
                               delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                    {
                                       perc = perc + 1;
                                    if (perc > 59){ perc = 1; }  
                                     }
          
          
                                    if (digitalRead(MINUS) == HIGH)
                                      {
                                        perc = perc - 1 ;
                                      if (perc < 0){ perc = 59; }
                                      if (perc == 255){ perc = 59; } 
                                       }
      
                                 }while(digitalRead(ENTER) == LOW); 
                                 lcd.clear();
                                 delay(500);
                                 
                                rtc.adjust(DateTime(ev, honap, nap, ora, perc, 00));
                                //Serial.println("-----sadsda");


                                
                                 do
                                 {
                              lcd.setCursor(0,0);
                              lcd.print("Puffer Teteje_2:");
                              lcd.setCursor(7,1);
                              lcd.print(PUFFIT2B);
                              lcd.setCursor(0,2);
                              lcd.print("Service");
                              delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                  {
                                    PUFFIT2B= PUFFIT2B + 1;
                                      if (PUFFIT2B > 90){ PUFFIT2B= 1; }  
                                  }
          
                                  if (digitalRead(MINUS) == HIGH)
                                  {
                                  PUFFIT2B= PUFFIT2B - 1;
                                  if (PUFFIT2B < 1){ PUFFIT2B= 90; }
                                  }
                                 }while(digitalRead(ENTER) == LOW);
                                 delay(5);
                                 EEPROM.write(2,PUFFIT2B);
                                 delay(500);
                                 
                                 lcd.clear();
                                 delay(500);
                                
                                 
                             
                              
                                 do
                                {
                              lcd.setCursor(0,0);
                              lcd.print("Puffer Alja:");
                              lcd.setCursor(7,1);
                              lcd.print(PUFFIAB);
                              lcd.setCursor(0,2);
                              lcd.print("Service");
                              delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                  {
                                    PUFFIAB= PUFFIAB + 1;
                                      if (PUFFIAB > 90){ PUFFIAB= 1; }  
                                  }
          
                                  if (digitalRead(MINUS) == HIGH)
                                  {
                                  PUFFIAB= PUFFIAB - 1;
                                  if (PUFFIAB < 1){ PUFFIAB= 90; }
                                  }
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(5);
                                 EEPROM.write(4,PUFFIAB);
                                 delay(500);
                                 
                                 lcd.clear();
                                 delay(500);
                                 
                                 
                                 
                                 do
                                { 
                              lcd.setCursor(0,0);
                              lcd.print("Futes_Rele:");
                              lcd.setCursor(7,1);
                              lcd.setCursor(0,2);
                              lcd.print("Service");
                              delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                  {
                                  digitalWrite (RELEKE, HIGH);
                                  lcd.setCursor(0,3);
                                  lcd.print("F\007tes:BE");
                                  }
          
                                  if (digitalRead(MINUS) == HIGH)
                                  {
                                  digitalWrite (RELEKE, LOW);
                                  lcd.setCursor(0,3);
                                  lcd.print("F\007tes:KI");
                                  }
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(500);
                                 
                                 lcd.clear();
                                 delay(500);
                                 
                                 
                                 
                                 
                                 do
                                { 
                              lcd.setCursor(0,0);
                              lcd.print("Elektrom_Futes_Rele:");
                              lcd.setCursor(7,1);
                              lcd.setCursor(0,2);
                              lcd.print("Service");
                              delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                  {
                                  digitalWrite (RELEFUTES, HIGH);
                                  lcd.setCursor(0,3);
                                  lcd.print("Futes:BE");
                                  }
          
                                  if (digitalRead(MINUS) == HIGH)
                                  {
                                  digitalWrite (RELEFUTES, LOW);
                                  lcd.setCursor(0,3);
                                  lcd.print("Futes:KI");
                                  }
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(500);
                                 
                                 lcd.clear();
                                 delay(500);
                                 
                                 do
                                { 
                              lcd.setCursor(0,0);
                              lcd.print("PWM:");
                              lcd.setCursor(7,1);
                              lcd.setCursor(0,2);
                              lcd.print("Service");
                              delay(200);
                                  if (digitalRead(PLUS) == HIGH)
                                    {
                                       PwmKitolt = PwmKitolt + 5;
                                       lcd.clear();
                                    if (PwmKitolt > 250){ PwmKitolt = 60; }  
                                     }
          
          
                                    if (digitalRead(MINUS) == HIGH)
                                      {
                                        PwmKitolt = PwmKitolt - 10 ;
                                        lcd.clear();
                                      if (PwmKitolt < 60){ PwmKitolt = 250; }
                                       }
                                    
                                  analogWrite(PwmKim, PwmKitolt);
                                  lcd.setCursor(4,0);     
                                  lcd.print(PwmKitolt);
                                  
                                       
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(500);
                                 
                                 lcd.clear();
                                 delay(500);
                                 
                                 
                          
                                 
                  }while(digitalRead(ENTER) == LOW);                  
                  lcd.clear();
                  lcd.print("Vissza az elozo menube");
                  delay(1500);
                  lcd.clear();
                  } 
                  //service vege
                  //service vege                
         
          
    
 if (MENUV == 1)
 {
           do
            {
              
              
                   lcd.clear();
                    do
                    {  
                      lcd.setCursor(0,0);
                      lcd.print("Puffer Maximum:"); 
                     // lcd.setCursor(0,1);
                     // lcd.print("MIN/MAX:60-90");
                      lcd.setCursor(5,2);             
                      lcd.print(PUFFMAX); 
                      
                      
                      do
                      {
                                           

                     ZSIK = digitalRead(encoder0PinA); 
                    if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                    {
                       if (digitalRead(encoder0PinB) == HIGH)
                       {
                         PUFFMAX = PUFFMAX + 1;
                         if (PUFFMAX > 90){ PUFFMAX = 10; }
                         lcd.setCursor(5,2);             
                         lcd.print(PUFFMAX);
                       } 
                       
                         else
                          {
                            PUFFMAX= PUFFMAX - 1;
                            if (PUFFMAX < 10){ PUFFMAX = 90; }
                             lcd.setCursor(5,2);             
                             lcd.print(PUFFMAX);
                          }
                    }
                    encoder0PinALast = ZSIK;
                   
 
                   
                   
                    }while(digitalRead(ENTER) == LOW);
                    }while(digitalRead(ENTER) == LOW);
                    delay(5);
                    EEPROM.write(20,PUFFMAX);
                    delay(500);
              
              
                    
                               lcd.clear();
                                do
                                {
                              lcd.setCursor(0,0);
                              lcd.print("Puffer Teteje_1:");
                             // lcd.setCursor(0,2);
                            //  lcd.print("30C \002s 90C k\004z\004tt");
                           //   lcd.setCursor(0,3);
                            //  lcd.print("\005llithat\001.");
                              lcd.setCursor(7,1);
                              lcd.print(PUFFIT1B);
                              do
                              {
                              
                              
                              ZSIK = digitalRead(encoder0PinA);
                                if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                                {
                                 if (digitalRead(encoder0PinB) == HIGH)
                                   {
                                 
                                    PUFFIT1B= PUFFIT1B + 1;
                                    if (PUFFIT1B > 90){ PUFFIT1B= 10; }  
                                    lcd.setCursor(7,1);
                                    lcd.print(PUFFIT1B);
                                   } 
                                    else 
                                        {
                                       
                                         PUFFIT1B= PUFFIT1B - 1;
                                        if (PUFFIT1B < 10){ PUFFIT1B= 90; }
                                        lcd.setCursor(7,1);
                                        lcd.print(PUFFIT1B);
                                      }
                                 }
                                  encoder0PinALast = ZSIK;
                              
                 
                 
                                 }while(digitalRead(ENTER) == LOW);
                                 }while(digitalRead(ENTER) == LOW); 
                                 delay(5);
                                 EEPROM.write(1,PUFFIT1B);
                                 delay(500);
                                 
                                 lcd.clear();
                                 delay(500);
                                 
                                 
                                 do
                                 {
                              lcd.setCursor(0,0);
                              lcd.print("Puffer Teteje_2:");
                              lcd.setCursor(0,2);
                              lcd.print("Elektromos f\007t\002s ");
                              lcd.setCursor(0,3);
                              lcd.print("ezt n\002ziMIN:30MAX:90");
                              lcd.setCursor(7,1);
                              lcd.print(PUFFIT2B);
                              
                              do
                              {
                                                            
                              ZSIK = digitalRead(encoder0PinA);
                                if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                                {
                                 if (digitalRead(encoder0PinB) == HIGH)
                                     {
                                     
                                     PUFFIT2B= PUFFIT2B + 1;
                                     if (PUFFIT2B > 90){ PUFFIT2B= 10; }  
                                     lcd.setCursor(7,1);
                                     lcd.print(PUFFIT2B);
                                     } 
                                    else 
                                        {                              
                                         PUFFIT2B= PUFFIT2B - 1;
                                        if (PUFFIT2B < 10){ PUFFIT2B= 90; }
                                        lcd.setCursor(7,1);
                                        lcd.print(PUFFIT2B);
                                        }
                                 }
                                  encoder0PinALast = ZSIK;
                              
                 
                 
                                 }while(digitalRead(ENTER) == LOW);
                                 }while(digitalRead(ENTER) == LOW);
                                 delay(5);
                                 EEPROM.write(2,PUFFIT2B);
                                 delay(500);
                                 
                                 lcd.clear();
                                 delay(500);
                                 
                                 
                                 
                                 
                                 do
                                 {
                              lcd.setCursor(0,0);
                              lcd.print("Puffer K\004zepe:");
                             // lcd.setCursor(0,2);
                            //  lcd.print("30C \002s 90C k\004z\004tt");
                             // lcd.setCursor(0,3);
                             // lcd.print("\005llithat\001.");
                              lcd.setCursor(7,1);
                              lcd.print(PUFFIKB);
                              
                              do
                              {
                               
                              ZSIK = digitalRead(encoder0PinA);
                                if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                                {
                                 if (digitalRead(encoder0PinB) == HIGH)
                                     {
                                     PUFFIKB= PUFFIKB + 1;
                                      if (PUFFIKB > 90){ PUFFIKB= 10; } 
                                      lcd.setCursor(7,1);
                                      lcd.print(PUFFIKB);
                                     } 
                                    else 
                                        {
                                         PUFFIKB= PUFFIKB - 1;
                                         if (PUFFIKB < 10){ PUFFIKB= 90; }
                                         lcd.setCursor(7,1);
                                         lcd.print(PUFFIKB);
                                        }
                                 }
                                  encoder0PinALast = ZSIK;
                              
                 
                 
                                 }while(digitalRead(ENTER) == LOW);
                                 }while(digitalRead(ENTER) == LOW);
                                 delay(5);
                                 EEPROM.write(10,PUFFIKB);
                                 delay(500);
                                 
                                 lcd.clear();
                                 delay(500);
                                 
                                 
                              
         
           do
           {
            lcd.setCursor(0,0);
            lcd.print("Puffer Alja:");
           // lcd.setCursor(0,2);
           // lcd.print("\"20C \002s 90C k\004z\004tt");
           // lcd.setCursor(0,3);
          //  lcd.print("\005llithat\001.AlapBe.40\"");
            lcd.setCursor(7,1);
            lcd.print(PUFFIAB);
            
            do
           {   
                                 ZSIK = digitalRead(encoder0PinA);
                                if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                                {
                                 if (digitalRead(encoder0PinB) == HIGH)
                                     {
                                     PUFFIAB= PUFFIAB + 1;
                                     if (PUFFIAB > 90){ PUFFIAB= 10; } 
                                    lcd.setCursor(7,1);
                                    lcd.print(PUFFIAB); 
                                     } 
                                    else 
                                        {
                                         PUFFIAB= PUFFIAB - 1;
                                         if (PUFFIAB < 10){ PUFFIAB= 90; }
                                         lcd.setCursor(7,1);
                                         lcd.print(PUFFIAB);
                                        }
                                 }
                                  encoder0PinALast = ZSIK; 
                  
              }while(digitalRead(ENTER) == LOW);
              }while(digitalRead(ENTER) == LOW); 
              delay(5);
              EEPROM.write(4,PUFFIAB);
              delay(500);
              
          
     
       
   
            lcd.clear();
          do
          {  
          lcd.setCursor(0,0);
          lcd.print("Napkollkektor min."); 
          lcd.setCursor(0,1);
          lcd.print("bekap.hom.:20-95");
          lcd.setCursor(5,2);
          lcd.print(KOLLEKTORB);
          
          do
          {
          ZSIK = digitalRead(encoder0PinA);
                                if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                                {
                                 if (digitalRead(encoder0PinB) == HIGH)
                                     {
                                      KOLLEKTORB= KOLLEKTORB + 1;
                                      if (KOLLEKTORB > 95){ KOLLEKTORB= 20; } 
                                      lcd.setCursor(5,2);
                                      lcd.print(KOLLEKTORB);
                                     } 
                                  else 
                                        {
                                         KOLLEKTORB= KOLLEKTORB - 1;
                                         if (KOLLEKTORB < 20){ KOLLEKTORB= 95; }
                                         lcd.setCursor(5,2);
                                         lcd.print(KOLLEKTORB);
                                        }
                                 }
                                  encoder0PinALast = ZSIK; 
          
          }while(digitalRead(ENTER) == LOW);                   
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM.write(5,KOLLEKTORB);
          delay(500);
          
          
           
                
          
          lcd.clear();
           do
           {
           lcd.setCursor(0,0);
           lcd.print("Napkollektor Hisz.:");
           lcd.setCursor(0,2);
           lcd.print("\"5C \002s 50C k\004z\004tt");
           lcd.setCursor(0,3);
           lcd.print("\005llithat\001."); 
           lcd.setCursor(7,1);
           lcd.print(KOLLHISZB);
           
           do
           {
           ZSIK = digitalRead(encoder0PinA);
                                if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                                {
                                 if (digitalRead(encoder0PinB) == HIGH)
                                     {
                                     KOLLHISZB= KOLLHISZB + 1;
                                     if (KOLLHISZB > 50){ KOLLHISZB= 5; } 
                                      lcd.setCursor(7,1);
                                      lcd.print(KOLLHISZB);
                                     } 
                                  else 
                                        {
                                         KOLLHISZB= KOLLHISZB - 1;
                                         if (KOLLHISZB < 5){ KOLLHISZB= 50; }
                                          lcd.setCursor(7,1);
                                          lcd.print(KOLLHISZB);
                                        }
                                        
                                 }
                                  encoder0PinALast = ZSIK; 
                                if (KOLLHISZB < 10 )
                                  {
                                   lcd.setCursor(8,1);
                                   lcd.print(" ");
                                  }    
                                  
                                  
          
          }while(digitalRead(ENTER) == LOW);               
          }while(digitalRead(ENTER) == LOW); 
           delay(5);
           EEPROM.write(6,KOLLHISZB);
           delay(500);  
         
                      
                                  
             }while(digitalRead(ENTER) == LOW);
             lcd.clear();
             wdt_enable (WDTO_8S);
  } //if MENU ==1   vége    
    
    

if(MENUV == 2) 
  {
   wdt_disable();
   
                    
          delay(500); 
          valI = 0;
          digitalWrite (RELEFUTES, LOW);  
          
         
          
     do
     {
         lcd.clear();
         
         lcd.setCursor(0,3);       
         if (ELEKTFBEKI == 1){
         lcd.print("Igen");}
         else{
         lcd.print("Nem");}
         
         
          do
          {
          lcd.setCursor(0,0);
          lcd.print("Szeretnel idozitest");
          lcd.setCursor(0,1);
          lcd.print("a puffer elektromos");
          lcd.setCursor(0,2);
          lcd.print("futeshez? (Nem/Igen)");
          
          do
          {
           ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      ELEKTFBEKI = 1 ;
                      lcd.setCursor(0,3);
                      lcd.print("Igen");
                     } 
                    else 
                       {
                        ELEKTFBEKI = 0; 
                        lcd.setCursor(3,3);
                        lcd.print(" ");
                        lcd.setCursor(0,3);
                        lcd.print("Nem");                        
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);
          }while(digitalRead(ENTER) == LOW);
          delay(50);
          EEPROM_writeAnything(39, (byte)ELEKTFBEKI);
          delay(500);
        
          
       
        if ( ELEKTFBEKI == 1 )
        {
         lcd.clear();
          do
          {  
          lcd.setCursor(0,0);
          lcd.print("ElektromosFutes:");  
          lcd.setCursor(0,1);
          lcd.print("Indul:");
          if ( OraI < 10 )
                         {
                          lcd.setCursor(7,1);
                          lcd.print(OraI);
                          lcd.setCursor(6,1);
                          lcd.print("0");
                         }
                      if ( OraI >= 10 )
                         {              
                          lcd.setCursor(6,1);
                          lcd.print(OraI);
                         }
          
         do
          { 
          
        
           ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      OraI = OraI + 1;
                      if (OraI > 23){ OraI = 0; } 
                      if ( OraI < 10 )
                         {
                          lcd.setCursor(7,1);
                          lcd.print(OraI);
                          lcd.setCursor(6,1);
                          lcd.print("0");
                         }
                      if ( OraI >= 10 )
                         {              
                          lcd.setCursor(6,1);
                          lcd.print(OraI);
                         }
                     } 
                    else 
                       {
                        OraI = OraI - 1;
                        if (OraI < 0){ OraI = 23; }
                        if (OraI == 255){ OraI = 23; }
                        if ( OraI < 10 )
                         {
                          lcd.setCursor(7,1);
                          lcd.print(OraI);
                          lcd.setCursor(6,1);
                          lcd.print("0");
                         }
                         if ( OraI >= 10 )
                         {
                          lcd.setCursor(6,1);
                          lcd.print(OraI);
                         }
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);     
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(35, (byte)OraI);
          delay(500);
          
          
          lcd.setCursor(8,1);
          lcd.print(":");
          if ( PercI < 10 )
                          {
                            lcd.setCursor(10,1);
                            lcd.print(PercI);
                            lcd.setCursor(9,1);
                            lcd.print("0");
                           }
                       if ( PercI >= 10 )    
                       {
                      lcd.setCursor(9,1);
                      lcd.print(PercI);
                       }
                       
                       
          do
          {   
          do
          {
           ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      PercI = PercI + 1;
                      if (PercI > 59){ PercI = 0; } 
                        if ( PercI < 10 )
                          {
                            lcd.setCursor(10,1);
                            lcd.print(PercI);
                            lcd.setCursor(9,1);
                            lcd.print("0");
                           }
                       if ( PercI >= 10 )    
                       {
                      lcd.setCursor(9,1);
                      lcd.print(PercI);
                       }
                      
                     } 
                    else 
                       {
                        PercI = PercI - 1;
                        if (PercI < 0){ PercI = 59; }
                        if (PercI == 255){ PercI = 59; }                     
                          if ( PercI < 10 )
                          {
                            lcd.setCursor(10,1);
                            lcd.print(PercI);
                            lcd.setCursor(9,1);
                            lcd.print("0");
                           }
                       if ( PercI >= 10 )    
                       {
                        lcd.setCursor(9,1);
                        lcd.print(PercI);
                       }
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);                  
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(36, (byte)PercI);
          delay(500);
       //----------------     
      
          do
          {    
          lcd.setCursor(0,2);
          lcd.print("Vege:");
          if ( OraV < 10 )
                         {
                          lcd.setCursor(6,2);
                          lcd.print(OraV);
                          lcd.setCursor(5,2);
                          lcd.print("0");
                        }
                     if ( OraV >= 10 )
                         {
                           lcd.setCursor(5,2);
                           lcd.print(OraV);
                         }
       
         do
          { 
 
           ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      OraV = OraV + 1;
                      if (OraV > 23){ OraV = 0; } 
                      if ( OraV < 10 )
                         {
                          lcd.setCursor(6,2);
                          lcd.print(OraV);
                          lcd.setCursor(5,2);
                          lcd.print("0");
                        }
                     if ( OraV >= 10 )
                         {
                           lcd.setCursor(5,2);
                           lcd.print(OraV);
                         }
                        
                        
                     } 
                    else 
                       {
                        OraV = OraV - 1;
                        if (OraV < 0){ OraV = 23; }
                        if (OraV == 255){ OraV = 23; }
                        if ( OraV < 10 )
                         {
                          lcd.setCursor(6,2);
                          lcd.print(OraV);
                          lcd.setCursor(5,2);
                          lcd.print("0");
                        }
                     if ( OraV >= 10 )
                         {
                           lcd.setCursor(5,2);
                           lcd.print(OraV);
                         }                   
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);  
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(37, (byte)OraV);
          delay(500);
          lcd.setCursor(7,2);
          lcd.print(":");
       

          do
          {  
            if ( PercV < 10 )
                         {
                          lcd.setCursor(9,2);
                          lcd.print(PercV);
                          lcd.setCursor(8,2);
                          lcd.print("0");
                         }
                      if ( PercV >= 10 )
                         {
                          lcd.setCursor(8,2);
                          lcd.print(PercV);
                         }
           
            do
          { 
           ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      PercV = PercV + 1;
                      if (PercV > 59){ PercV = 0; }
                      if ( PercV < 10 )
                         {
                          lcd.setCursor(9,2);
                          lcd.print(PercV);
                          lcd.setCursor(8,2);
                          lcd.print("0");
                         }
                      if ( PercV >= 10 )
                         {
                          lcd.setCursor(8,2);
                          lcd.print(PercV);
                         }
                     } 
                    else 
                       {
                        PercV = PercV - 1;
                        if (PercV < 0){ PercV = 59; }
                        if (PercV == 255){ PercV = 59; }
                        if ( PercV < 10 )
                         {
                          lcd.setCursor(9,2);
                          lcd.print(PercV);
                          lcd.setCursor(8,2);
                          lcd.print("0");
                         }
                      if ( PercV >= 10 )
                         {
                          lcd.setCursor(8,2);
                          lcd.print(PercV);
                         }                
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW); 
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(38, (byte)PercV);
          delay(500);
        }
       
             
           
     }while(digitalRead(ENTER) == LOW);
     lcd.clear();
     wdt_enable (WDTO_8S);
     
   
 }//MENUV == 2 Vege
    
    
 if (MENUV == 3)
 {
   
   
   delay(500); 
   digitalWrite (RELEKE, LOW);
   do
   { 
 lcd.clear();
       
       lcd.setCursor(0,3);       
         if (FUTESBEKI == 1){
         lcd.print("Igen");}
         else{
         lcd.print("Nem");}
       
       do
          {
          lcd.setCursor(0,0);
          lcd.print("Szeretnel idozitest");
          lcd.setCursor(0,1);
          lcd.print("a haz futesehez?");
          lcd.setCursor(0,2);
          lcd.print("(Nem/Igen)");
          
          do
          {
          ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                     FUTESBEKI = 1 ;
                     lcd.setCursor(0,3);
                     lcd.print("Igen");
                     } 
                    else 
                       {
                        FUTESBEKI = 0; 
                        lcd.setCursor(3,3);
                        lcd.print(" ");
                        lcd.setCursor(0,3);
                        lcd.print("Nem");               
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW); 
          }while(digitalRead(ENTER) == LOW);
          {
          delay(50);
          EEPROM_writeAnything(40, (byte)FUTESBEKI);
          delay(500);
          
          }
       
       
       
       if (FUTESBEKI == 1 )
       {       
         lcd.clear();        

////////////////////////////////////////////////////////////////////////////////////////////////////////////  

          lcd.clear();
          teszt = 128 ;
        
         EEPROM_readAnything(33, BB); 
          do
          {  
          lcd.setCursor(0,0);
          lcd.print("Mennyi iozitest"); 
          lcd.setCursor(0,1);
          lcd.print("szeretnel:(1-12)");
           if ( BB < 10 )
                         {
                          lcd.setCursor(0,2);
                          lcd.print("0");
                          lcd.setCursor(1,2);
                          lcd.print(BB);
                        } 
                        if ( BB >= 10 )
                         {
                          lcd.setCursor(0,2);
                          lcd.print(BB);
                         } 
          do
          {
            
          
          ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      BB = BB + 1;
                      if (BB > 12){ BB = 1; }
                      if ( BB < 10 )
                         {
                          lcd.setCursor(0,2);
                          lcd.print("0");
                          lcd.setCursor(1,2);
                          lcd.print(BB);
                        } 
                        if ( BB >= 10 )
                         {
                          lcd.setCursor(0,2);
                          lcd.print(BB);
                         } 
                     } 
                    else 
                       {
                        BB = BB - 1;
                        if (BB < 1){ BB = 12; }
                        if ( BB < 10 )
                         {
                          lcd.setCursor(0,2);
                          lcd.print("0");
                          lcd.setCursor(1,2);
                          lcd.print(BB);
                        } 
                        if ( BB >= 10 )
                         {
                          lcd.setCursor(0,2);
                          lcd.print(BB);
                         }             
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);       
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(33, (byte)BB);
          delay(500);
          lcd.clear();  
          
          if ( BB >= 1 && BB < 12)
          { 
            switch (BB) {
            case 1:
            for (n = 137; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); ////137,142,147,152,157,162,167,172,177,182,187 kéne hogy legyen
            delay(50);
            }
            break;   
       
            
            case 2:
            for (n = 142; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //142,147,152,157,162,167,172,177,182,187 kéne hogy legyen
            delay(50);
            }        
            break;          
            
            
            case 3:
            for (n = 147; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //147,152,157,162,167,172,177,182,187 kéne hogy legyen
            delay(50);
            }
            break;   
             
             
            case 4:
            for (n = 152; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //152,157,162,167,172,177,182,187 kéne hogy legyen
            delay(50);
            }
            break;  
            
            
            case 5:
            for (n = 157; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //157,162,167,172,177,182,187 kéne hogy legyen
            delay(50);
            }
            break;  
            
            
            case 6:
            for (n = 162; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //162,167,172,177,182,187 kéne hogy legyen
            delay(50);
            }
            break;  
       
           
            case 7:
            for (n = 167; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //167,172,177,182,187 kéne hogy legyen
            delay(50);
            }
            break;
            
            
            case 8:
            for (n = 172; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //172,177,182,187 kéne hogy legyen
            delay(50);
            }
            break;
             
             
            case 9:
            for (n = 177; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //177,182,187 kéne hogy legyen
            delay(50);
            }
            break;
            
  
            case 10:
             for (n = 182; n <= 187; n = n + 5)
            {
            EEPROM_writeAnything(n, (byte)0); //182,187 kéne hogy legyen
            delay(50);
            }
            break;
   
             
            case 11:
            EEPROM_writeAnything(187, (byte)0);
            delay(50);
            break;
            }//switch vége
              
          }//if vége
          
       

       x = 1; 
       while (x <= BB )
       {
          EEPROM_readAnything(teszt, ORA);  
          do
          {  
          lcd.setCursor(0,0);
          lcd.print("Idozites:"); 
          lcd.setCursor(10,0);
          lcd.print(x);
          lcd.setCursor(0,1);
          lcd.print("Kezd:");
          if ( ORA < 10 )
                         {
                          lcd.setCursor(6,1);
                          lcd.print(ORA);
                          lcd.setCursor(5,1);
                          lcd.print("0");
                         }
                      if ( ORA >= 10 )
                         {
                          lcd.setCursor(5,1);
                          lcd.print(ORA);
                         }
          
          do
          {
          ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      ORA = ORA + 1;
                      if (ORA > 23){ ORA = 0; }
                      if ( ORA < 10 )
                         {
                          lcd.setCursor(6,1);
                          lcd.print(ORA);
                          lcd.setCursor(5,1);
                          lcd.print("0");
                         }
                      if ( ORA >= 10 )
                         {
                          lcd.setCursor(5,1);
                          lcd.print(ORA);
                         }
                     } 
                    else 
                       {
                        ORA = ORA - 1;
                        if (ORA < 0){ ORA = 23; }
                        if (ORA == 255){ ORA = 23; }
                        if ( ORA < 10 )
                         {
                          lcd.setCursor(6,1);
                          lcd.print(ORA);
                          lcd.setCursor(5,1);
                          lcd.print("0");
                         }
                      if ( ORA >= 10 )
                         {
                          lcd.setCursor(5,1);
                          lcd.print(ORA);
                         }           
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);             
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(teszt, (byte)ORA);
          delay(500);
          
         /* Serial.println(teszt);
          Serial.println(ORA);
          Serial.println("------------");*/
          
          
          teszt++;
          
          
          
         EEPROM_readAnything(teszt, PERC);  
          
          do
          {  
          lcd.setCursor(7,1);
          lcd.print(":");
          if ( PERC < 10 )
                         {
                          lcd.setCursor(9,1);
                          lcd.print(PERC);
                          lcd.setCursor(8,1);
                          lcd.print("0");
                         } 
                         if ( PERC >= 10 )
                         {
                          lcd.setCursor(8,1);
                          lcd.print(PERC);
                         }
         
          
          
          do
          {      
           ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      PERC = PERC + 1;
                      if (PERC > 59){ PERC = 0; }                     
                      if ( PERC < 10 )
                         {
                          lcd.setCursor(9,1);
                          lcd.print(PERC);
                          lcd.setCursor(8,1);
                          lcd.print("0");
                         } 
                         if ( PERC >= 10 )
                         {
                          lcd.setCursor(8,1);
                          lcd.print(PERC);
                         }
                     } 
                    else 
                       {
                        PERC = PERC - 1;
                        if (PERC < 0){ PERC = 59; }
                        if (PERC == 255){ PERC = 59; }
                        if ( PERC < 10 )
                         {
                          lcd.setCursor(9,1);
                          lcd.print(PERC);
                          lcd.setCursor(8,1);
                          lcd.print("0");
                         } 
                         if ( PERC >= 10 )
                         {
                          lcd.setCursor(8,1);
                          lcd.print(PERC);
                         }          
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);    
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(teszt, (byte)PERC);
          delay(500);
          
         /* Serial.println(teszt);
          Serial.println(PERC);
          Serial.println("------------");*/
          
          teszt++;
          
          
          EEPROM_readAnything(teszt, ORA); 
          do
          {  
          lcd.setCursor(0,2);
          lcd.print("Vege:");
          if ( ORA < 10 )
                         {
                          lcd.setCursor(6,2);
                          lcd.print(ORA);
                          lcd.setCursor(5,2);
                          lcd.print("0");
                         } 
                      if ( ORA >= 10 )
                         {
                          lcd.setCursor(5,2);
                          lcd.print(ORA);
                         }  
                     
          
         
          do
          {
           ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      ORA = ORA + 1;
                      if (ORA > 23){ ORA = 0; }
                      if ( ORA < 10 )
                         {
                          lcd.setCursor(6,2);
                          lcd.print(ORA);
                          lcd.setCursor(5,2);
                          lcd.print("0");
                         } 
                      if ( ORA >= 10 )
                         {
                          lcd.setCursor(5,2);
                          lcd.print(ORA);
                         }  
                     } 
                    else 
                       {
                        ORA = ORA - 1;
                        if (ORA < 0){ ORA = 23; }
                        if (ORA == 255){ ORA = 23; } 
                        if ( ORA < 10 )
                         {
                          lcd.setCursor(6,2);
                          lcd.print(ORA);
                          lcd.setCursor(5,2);
                          lcd.print("0");
                         } 
                      if ( ORA >= 10 )
                         {
                          lcd.setCursor(5,2);
                          lcd.print(ORA);
                         }        
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);     
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(teszt, (byte)ORA);
          delay(500);
          
          /*Serial.println(teszt);
          Serial.println(ORA);
          Serial.println("------------");*/
          
          
          teszt++;
          
         
          
          EEPROM_readAnything(teszt, PERC); 
          
          do
          {
          lcd.setCursor(7,2);
          lcd.print(":");
          if ( PERC < 10 )
                         {
                          lcd.setCursor(9,2);
                          lcd.print(PERC);
                          lcd.setCursor(8,2);
                          lcd.print("0");
                         }
                      if ( PERC >= 10 )
                         {
                          lcd.print(PERC);
                          lcd.setCursor(8,2); 
                         }
          
          
          do
          {

          ZSIK = digitalRead(encoder0PinA);
           if ((encoder0PinALast == LOW) && (ZSIK == HIGH)) 
                 {
                   if (digitalRead(encoder0PinB) == HIGH)
                    {
                      PERC = PERC + 1;
                      if (PERC > 59){ PERC = 0; }
                      if ( PERC < 10 )
                         {
                          lcd.setCursor(9,2);
                          lcd.print(PERC);
                          lcd.setCursor(8,2);
                          lcd.print("0");
                         }
                      if ( PERC >= 10 )
                         {
                          lcd.print(PERC);
                          lcd.setCursor(8,2); 
                         }
                     } 
                    else 
                       {
                        PERC = PERC - 1;
                        if (PERC < 0){ PERC = 59; }
                        if (PERC == 255){ PERC = 59; } 
                        if ( PERC < 10 )
                         {
                          lcd.setCursor(9,2);
                          lcd.print(PERC);
                          lcd.setCursor(8,2);
                          lcd.print("0");
                         }
                      if ( PERC >= 10 )
                         {
                          lcd.print(PERC);
                          lcd.setCursor(8,2); 
                         }    
                        }
                                        
                     }
            encoder0PinALast = ZSIK;
            
          }while(digitalRead(ENTER) == LOW);   
          }while(digitalRead(ENTER) == LOW);
          delay(5);
          EEPROM_writeAnything(teszt, (byte)PERC);
          delay(500);
          
          /*Serial.println(teszt);
          Serial.println(PERC);
          Serial.println("------------");*/
          
          
          teszt++;        
   
          delay(5);
          EEPROM_writeAnything(teszt, (byte)1);
          delay(500);
          lcd.clear();
          
          EEPROM_readAnything(teszt, I);
          
          /*Serial.println(teszt);
          Serial.println(I);
          Serial.println("------------");*/
      
          
          teszt++;  
          
          x++;
          lcd.clear();
          delay(200);
          
          
          }//while vége
        
         x = 1;
         //SOK = 1;
         //EEPROM_writeAnything(43, (byte)SOK);     
         //delay(100);
       
         
  }
        
        
             
        }while(digitalRead(ENTER) == LOW);
         delay(5);
         lcd.clear();
          
                  
          wdt_enable (WDTO_8S);
          delay(500);
          //asm volatile ("  jmp 0");   //soft reset
  
  
} //MENUV == 3 vege  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
    
    
    
    
    
 
} //if ENTER   vége  
  
   

int KOLLM = sensors.getTempC(KOLL);
//byte KOLLM = 55;

int KINTM = sensors.getTempC(KINT);
//int KINTM = -35.5;

byte PF4M = sensors.getTempC(PT4);   
//byte PF4M = 55;

byte PF3M = sensors.getTempC(PT3);
//byte PF3M = 54;

byte PF2M = sensors.getTempC(PK2);
//byte PF2M = 52;

byte PF1M = sensors.getTempC(PA1);
//byte PF1M = 45;



//ITT ÁLLÍTOD BE HOGY ÉPP MELYIK ÉRZEKELŐT FIGYELJE A FELTÉTEL HOGY ELINDULJON A NAPKOLLEKTOR  
SENSOR = PF1M ;           //HA EZT VÁLTOZTATOD
PUFFKISENSOR = PUFFIAB ;  //AKKOR EZ IS KELL !!!!!!!!!!!


//napkollektor keringető pwm kitöltes erteke
if (KOLLM >= SENSOR + 5 )
{ 
  PwmKitolt = 64; //25%
  E = 25;
  
  
     if (KOLLM >= SENSOR + 6  )
     {
      PwmKitolt = 76; //30%
      E = 30;
       
       if (KOLLM >= SENSOR + 7  )
       {
         PwmKitolt = 89; //35%
         E = 35;
         
         if (KOLLM >= SENSOR + 8  )
         {
           PwmKitolt = 102; //40%
           E = 40;
         
           if (KOLLM >= SENSOR + 9  )
           {
             PwmKitolt = 114; //45%
             E = 45;
            
              if (KOLLM >= SENSOR + 10 )
              {
                 PwmKitolt = 127; //50%
                 E = 50;
          
                if (KOLLM >= SENSOR + 11 )
                {
                   PwmKitolt = 140; //55%
                   E = 55;
                   
                   if (KOLLM >= SENSOR + 12 )
                   {
                     PwmKitolt = 153; //60%
                     E = 60;
                     
                     if (KOLLM >= SENSOR + 13 )
                     {
                       PwmKitolt = 165; //65%
                       E = 65;
                       
                       if (KOLLM >= SENSOR + 14 )
                       {
                         PwmKitolt = 178; //70%
                         E = 70;
                         
                         if (KOLLM >= SENSOR + 15 )
                         {
                           PwmKitolt = 191; //75%
                           E = 75;
                                                     
                            if (KOLLM >= SENSOR + 16 )
                            {
                               PwmKitolt = 204; //80%
                               E = 80;
                               
                               if (KOLLM >= SENSOR + 17 )
                               {
                                 PwmKitolt = 216; //85%
                                 E = 85;

                                  if (KOLLM >= SENSOR+ 18 )
                                  {
                                   PwmKitolt = 229; //90%
                                   E = 90;

                                      if (KOLLM >= SENSOR + 19 )
                                      {
                                        PwmKitolt = 242; //95%
                                        E = 95;
                                       
                                         if (KOLLM >= SENSOR + 20 )
                                         {
                                           PwmKitolt = 255; //100%
                                           E = 100;
                                         }
                                      }
                                  }
                               }
                            }
                         }
                       }
                     }
                   }
                }
              }
           }
         }
       }
     }
}





//napkollektor keringető feltételek

//   60        5          55      60        55           30          55      80 
if (KOLLM - KOLLHISZB >= SENSOR && KOLLM - KOLLHISZB >= KOLLEKTORB && SENSOR < PUFFKISENSOR && PF4M < PUFFMAX)
{
  val = 1;
  lcd.setCursor(9,3);
  lcd.print("Koll:BE "); 
  if ( E < 100)
    {
      lcd.setCursor(17,3);
      lcd.print(E);
      lcd.setCursor(19,3);
      lcd.print("%");
    }
    
      if ( E == 100)
        {
          lcd.setCursor(16,3);
          lcd.print(E);
          lcd.setCursor(19,3);
          lcd.print("%");
         }
         
  delay(50);
  analogWrite(PwmKim, PwmKitolt);
  
 

  
  //Serial.println("PWM_BE");
 
  

}


else
{
//       60       55      60       55          60        30           5           55       80
  if ( KOLLM <= SENSOR || KOLLM <= SENSOR + 2 || KOLLM <= KOLLEKTORB - KOLLHISZB || SENSOR >= PUFFKISENSOR || PF4M >= PUFFMAX )
    {
      val = 0;
      lcd.setCursor(9,3);
      lcd.print("Koll:KI    ");
      delay(50);
      analogWrite(PwmKim, 0);
 
  //Serial.println("PWM_KI");
    }
}


//olyan vészleállító szerüség ha az előző feltételre nem lenne igaz semmi
if ( SENSOR >= PUFFKISENSOR || PF4M >= PUFFMAX )
    {
      lcd.setCursor(9,3);
      lcd.print("Koll:KI    ");
      delay(50);
      analogWrite(PwmKim, 0);
    }




if (val == 1)
{
lcd.setCursor(9,3);
  lcd.print("Koll:BE "); 
  if ( E < 100)
    {
      lcd.setCursor(17,3);
      lcd.print(E);
      lcd.setCursor(19,3);
      lcd.print("%");
    }
    
      if ( E == 100)
        {
          lcd.setCursor(16,3);
          lcd.print(E);
          lcd.setCursor(19,3);
          lcd.print("%");
         }
         delay(50);
  analogWrite(PwmKim, PwmKitolt);
}         

if (val == 3)
{
lcd.setCursor(9,3);
  lcd.print("Koll:HIBA "); 
}  





//*******************************************************************************************
//fűtés keringető feltételek
//+ időztés



//szakaszos(kezd)---------------------------------------------------------------------------------------------------------
wdt_reset();      
if ( FUTESBEKI == 1 ) //A1 if kezd
{
 

 
 if ( (SecAktualis >= 50 && SecAktualis < 59) && B != 1)
       {
         B = 0;
         //Serial.println("!!VPerc Vesz!!! Olvasas!!");

       }
     
       if ( (SecAktualis >= 0 && SecAktualis < 5) || B == 0)
      { 
           n = 128; 
            for ( m = 1; m <= 12; m++){
                  EEPROM_readAnything(n, OraIF[m]); 
                  n = n + 5;  }
           
           n = 129; 
           for (m = 1; m <= 12; m = m + 1){
                 EEPROM_readAnything(n, PercIF[m]); 
               n = n + 5;}
          
        
           n = 130; 
           for (m = 1; m <= 12; m = m + 1){
              EEPROM_readAnything(n, OraVF[m]); 
              n = n + 5;}
            
        
         n = 131; 
         for (m = 1; m <= 12; m = m + 1){
              EEPROM_readAnything(n, PercVF[m]); 
              n = n + 5;}
                  
         n = 132; 
         for (m = 1; m <= 12; m = m + 1){
              EEPROM_readAnything(n, BEKI[m]); 
              n = n + 5;}
              
          B = 1;
  // Serial.println("Sima Olvasas!!");
       
        for (m = 1; m <= 12; m = m +1)
          {
           IIO[m] = (long)((OraIF[m] * 3600UL) + (PercIF[m] *60)) ;
            //Serial.print("Indul: ");Serial.println(IIO[m]);
            
            IVO[m] = (long)((OraVF[m] * 3600UL) + (PercVF[m] * 60));
           //Serial.print("Vege: ");Serial.println(IVO[m]);
          }
    
     IAO = (long)((ORAAktualis * 3600UL) + (PercAktualis * 60));
     //Serial.print("OraAktualis ");Serial.println(IAO);   



      for (m = 1; m <= 12; m = m +1)
          {
            
            
            //Serial.print("(");Serial.print(IAO);Serial.print(">=");Serial.print(IIO[m]);Serial.print("&&");Serial.print(IAO);Serial.print("<=");Serial.print(IVO[m]);Serial.print(")");Serial.print("&&");Serial.print(BEKI[m]);Serial.print("==");Serial.println("1");
            //delay(500);delay(500);
            if ( (IAO >= IIO[m] && IAO < IVO[m]) && BEKI[m] == 1 )
                {
                  if ( PF4M >= PUFFIT1B && PF2M >= PUFFIKB ){
                  G = 1;}
                  else{
                    G = 0;}
                    if ( G== 1){
                   FutesBE();}
                      VISSZA = 1;
                      A = 1;
                      AA = m ;   
                      
                     // Serial.println("------V1-------");                 
                }
                            
              if (m < BB )
                  {
                  if ( IAO < IIO[m+1] && IAO >= IVO[m] ) 
                      {
                    FutesKI();
                    
                    A = 0;
                    AA = m ;
                    VISSZA = 0;
                    //AramSZ = 0;
                    //Serial.println("BBBBBBBBBBBBBBBBBBB:");
                 } 
                  }
                  
              if (m == BB )
                  {
                  if ( IAO >= IVO[m]  ) 
                      {
                    FutesKI();
                    A = 0;
                    AA = m ;
                    VISSZA = 0;
                    //Serial.println("CCCCCCCCCCCCCCcc:");
                 } 
                  }    
                  
               EEPROM_readAnything(34, HH);  
               EEPROM_readAnything(42, UU);
                   
                   if ( HH != A ){
                   EEPROM_writeAnything(34, (byte)A);
                      delay(50);}
                   
                   if ( UU != AA){
                   EEPROM_writeAnything(42, (byte)AA);
                      delay(50);}  
                  
                  
                  
            }//for vége
  
      }
  
  



      if ( A == 1 )
        {
          lcd.setCursor(9,2);
          lcd.print("F\007tes:BEP");
          lcd.setCursor(18,2);
          lcd.print(AA);
          if (AA < 10)
          {
          lcd.setCursor(19,2);
          lcd.print(AA);  
          lcd.setCursor(18,2);
          lcd.print("0");
          }
        }

       if ( A == 0 || ZZSO == 1)
           {
            lcd.setCursor(9,2);
            lcd.print("F\007tes:KIP");
            lcd.setCursor(18,2);
            lcd.print(AA);
            if (AA < 10)
              {
                lcd.setCursor(19,2);
                lcd.print(AA);
                lcd.setCursor(18,2);
                lcd.print("0");
              }
          
          }  


 if ( PF4M < PUFFIT1B || PF2M < PUFFIKB ) 
      {
        NMV2();
        if ( SecAktualis > 55 ){
        Pity();}
      }
      else if (VISSZA == 1){
        FutesBE();}
          


 

}//szakszos if vége

//szakaszos(vége)---------------------------------------------------------------------------------------------------------



wdt_reset(); 

//allandó ha nincs időzítés(kezd)-------------------------------------------------------------------------------------------------

if ( FUTESBEKI == 0 )
{

  if ( PF4M >= PUFFIT1B && PF2M >= PUFFIKB )
{
  digitalWrite (RELEKE, HIGH);
  lcd.setCursor(16,2);
  lcd.print("  ");
  lcd.setCursor(9,2);
  lcd.print("F\007tes:BE FF");
 // AramSZ = 0;
  
}


if ( PF4M < PUFFIT1B || PF2M < PUFFIKB ) 
      {
        NMV();
        if ( SecAktualis > 55 ){
        Pity();}
      }


}

//allandó ha nincs időzítés(vége)--------------------------------------------------------------------------------------





//--------------------------------------------------------------------------------------
//Elektromos fűtéshez a relé

//időzités
          //****************************************




   
          
if (ELEKTFBEKI == 1)
{   
            
       
  if ( SecAktualis >= 0 && SecAktualis < 5 )
      { 
         EEPROM_readAnything(35, OraIndulElektromosFutes);
         EEPROM_readAnything(36, PercIndulElektromosFutes); 
         EEPROM_readAnything(37, OraVegeElektromosFutes);
         EEPROM_readAnything(38, PercVegeElektromosFutes);
         
          
         IIO2 = (long)((OraIndulElektromosFutes * 3600UL) + (PercIndulElektromosFutes *60)) ;
         //Serial.print("Indul: ");Serial.println(IIO2);
         
         IVO2 = (long)((OraVegeElektromosFutes * 3600UL) + (PercVegeElektromosFutes * 60));
         //Serial.print("Vege: ");Serial.println(IVO2);
         
         IAO2 = (long)((ORAAktualis * 3600UL) + (PercAktualis * 60));
         //Serial.print("OraAktualis ");Serial.println(IAO2);
         
         if ( IAO2 >= IIO2 && IAO2 < IVO2  )
                {
                  valI = 1; 
                }
         else 
         {
           valI = 0;
         }
         
      }
         
if ( PF3M < PUFFIT2B  && PF4M < PUFFMAX && valI == 1)
    {
      digitalWrite (RELEFUTES, HIGH);
      lcd.setCursor(9, 1);
      lcd.print("F");
      valB = 1;
      //Serial.println("EL=1 BEkapcs");
    }
           
            
if ( PF3M >= PUFFIT2B + 10 || PF4M >= PUFFMAX || valI == 0)
   {
     digitalWrite (RELEFUTES, LOW);
     lcd.setCursor(9, 1);
     lcd.print(" ");
     valB = 0;
     //Serial.println("EL=1 KIkapcs");
    }


if (valI == 1 && valB == 1) 
 {
   lcd.setCursor(9, 1);
   lcd.print(" ");
   lcd.setCursor(9, 1);
   lcd.print("F");
 }

         
         
         
         
             
 
 
 
          
}          
/*if (ELEKTFBEKI == 1)
{
  
  
    if ( ORAAktualis == OraI && PercAktualis == PercI )
      {
        valI = 1;       
       // AramSZ = 0;
      }

      if ( ORAAktualis == OraV && PercAktualis == PercV)
        {
         valI = 0;
         //AramSZ = 0;
        }
              
        
if ( PF3M < PUFFIT2B  && PF4M < PUFFMAX && valI == 1)
            {
              digitalWrite (RELEFUTES, HIGH);
              lcd.setCursor(9, 1);
              lcd.print("F");
              valB = 1;
              //Serial.println("EL=1 BEkapcs");
            }
           
            
if ( PF3M >= PUFFIT2B + 10 || PF4M >= PUFFMAX || valI == 0)
             {
                digitalWrite (RELEFUTES, LOW);
                lcd.setCursor(9, 1);
                lcd.print(" ");
                valB = 0;
                //Serial.println("EL=1 KIkapcs");
             }

if (valI == 1 && valB == 1) 
 {
   lcd.setCursor(9, 1);
   lcd.print(" ");
   lcd.setCursor(9, 1);
   lcd.print("F");
 }

             
             
}
//Serial.println(ELEKTFBEKI);

*/

if (ELEKTFBEKI == 0)
{
  
 
 if ( PF3M < PUFFIT2B && PF4M < PUFFMAX)
            {
              digitalWrite (RELEFUTES, HIGH);
              lcd.setCursor(9, 1);
              lcd.print(" ");
              lcd.setCursor(9, 1);
              lcd.print("F");
              valA = 1;
              //Serial.println("EL=0 BEkapcs");
            }
           

if ( PF3M >= PUFFIT2B + 10 || PF4M >= PUFFMAX )
             {
                digitalWrite (RELEFUTES, LOW);
                lcd.setCursor(9, 1);
                lcd.print(" ");
                valA = 0;
                //Serial.println("EL=0 KIkapcs");
             }


if (valA == 1) 
 {
   lcd.setCursor(9, 1);
   lcd.print(" ");
   lcd.setCursor(9, 1);
   lcd.print("F");
 }             
             
             
  
}

             
//-----------------------------------------------------------------------



//ezt szed ki ha vége a tesztnek
 /* lcd.setCursor(16, 3);
  byte mint = now.minute();
   if (mint < 10)
   {
     lcd.setCursor(16, 3);
     lcd.print("0");
   }
   lcd.print(now.minute(), DEC);
   
   lcd.setCursor(18, 3);
  byte sec = now.second();
   if (sec < 10)
   {
     lcd.setCursor(18, 3);
     lcd.print("0");
   }
   lcd.print(now.second(), DEC);*/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   




KL++;
KLA = KL / 5;

//  kiírás a kijelzőre

  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("PT1:");
  printTemperature(PT4);  
  lcd.setCursor(0, 1);
  lcd.print("PT2:");
  printTemperature(PT3);
  lcd.setCursor(0, 2);
  lcd.print("PK:");
  printTemperature(PK2); 
  lcd.setCursor(0, 3);
  lcd.print("PA:");
  printTemperature(PA1);
  if ( KL == (KLA * 5) )
  {
    lcd.setCursor(11, 0);
    byte hour = now.hour();
   if (hour < 10)
   {
     lcd.print("0");
   }
    lcd.print(now.hour(), DEC);
    lcd.setCursor(13,0);
    lcd.print(":");
    
    lcd.setCursor(14, 0);
    byte minute = now.minute();
    if (minute < 10)
       {
         lcd.print("0");
       }
         lcd.print(now.minute(), DEC);
         lcd.setCursor(16, 0);
         lcd.print("    ");
  }
  else
  {  
  lcd.setCursor(11, 0);
  lcd.print("K\003l:");
  printTemperature(KINT);
  }
  
  lcd.setCursor(11, 1);
  lcd.print("Kol:");
  printTemperature(KOLL);
  delay(1000);
  
  
  
  
  
  
wdt_reset(); 



/*Serial.print(KL);
Serial.print("---");
Serial.print(KOLLM);
Serial.print("---");
Serial.print(PwmKitolt);
Serial.print("---");
Serial.println(KOLLEKTORB);*/



wdt_reset(); 



if ( KL == (KLA * 5)  )
{
digitalWrite(led, HIGH);
}
else{
digitalWrite(led, LOW);  }


/*
if (KL == 101) //101volt
{ 
 
  lcd.clear();
  KL = 0;
  
  //lcd.setCursor(0,0);
  //lcd.print(clock.dateFormat("H:i ", dt));
  
  //delay(3000);
  //lcd.clear();
  
lcd.setCursor(0,0);
  byte hour = now.hour();
   if (hour < 10)
   {
     lcd.print("0");
   }
    lcd.print(now.hour(), DEC);
    
    
   lcd.setCursor(2,0);
    lcd.print(":");
  
  lcd.setCursor(3,0);
  byte minute = now.minute();
   if (minute < 10)
   {
     lcd.print("0");
   }
   lcd.print(now.minute(), DEC);
   
   
    if (hour == 0 && minute == 1)  //hogy ejfelkor rendesen irja ki a napot
    {
      b = b +1;
      
      if (b > 35)
      {
        lcd.clear();
        b = 0;
      }
     //Serial.println(b);
    }
    else
    {
      b = 0;
    }
    
       
  lcd.setCursor(0,1);
    lcd.print(now.year(), DEC);
  
  lcd.setCursor(4,1);
    lcd.print("-");
  
  
  lcd.setCursor(5,1);
  byte month = now.month();
   if (month < 10)
   {
     lcd.print("0");
   }
    lcd.print(now.month(), DEC);
    
   lcd.setCursor(7,1);
    lcd.print("-");
     
  lcd.setCursor(8,1);  
    lcd.print(now.day(), DEC);
    
    
    
    
  int dow = now.dayOfTheWeek();                  
  lcd.setCursor(0,2);
  switch(dow){
     case 1:
     lcd.print("Hetfo");
     break;
     case 2:
     lcd.print("Kedd");
     break;
     case 3:
     lcd.print("Szerda");
     break;
     case 4:
     lcd.print("Csutortok");
     break;
     case 5:
     lcd.print("P\002ntek");
     break;
     case 6:
     lcd.print("Szombat");
     break;
     case 0:
     lcd.print("Vasarnap");
     
     break;}
 
  delay(3000);
  lcd.clear();
  
  
    
}
*/


if ( KL >= 230){
KL = 0;}




wdt_reset();
   
  
}//--(end main loop )---
/*-----( Declare User-written Functions )-----*/
void printTemperature(DeviceAddress deviceAddress)
{

float tempC = sensors.getTempC(deviceAddress);

   if (tempC == -127.00) 
   {
   Serial.print("Error getting temperature  ");  
   } 
   else
   {
   lcd.print(tempC);
   }
}// End printTemperature



void NMV()
{
        digitalWrite (RELEKE, LOW);
        lcd.setCursor(9,2);
        lcd.print("F\007tes:KI");
        lcd.setCursor(17,2);
        lcd.print("NMV");
        delay(500);
        lcd.setCursor(17,2);
        lcd.print("FF ");
        delay(500);
        digitalWrite (PIROSLED, HIGH);
        delay(50);
        digitalWrite (PIROSLED, LOW);
        delay(100);
        digitalWrite (PIROSLED, HIGH);
        delay(50);
        digitalWrite (PIROSLED, LOW);
        lcd.setCursor(17,2);
        lcd.print("   ");   
}

void NMV2()
{
        digitalWrite (RELEKE, LOW);
        lcd.setCursor(9,2);
        lcd.print("F\007tes:");
        lcd.setCursor(17,2);
        lcd.print("NMV");
        delay(500);
        lcd.setCursor(17,2);
          lcd.print("P");
          lcd.setCursor(18,2);
          lcd.print(AA);
          if (AA < 10)
          {
          lcd.setCursor(19,2);
          lcd.print(AA);  
          lcd.setCursor(18,2);
          lcd.print("0");
          }
        delay(500);
        digitalWrite (PIROSLED, HIGH);
        delay(50);
        digitalWrite (PIROSLED, LOW);
        delay(100);
        digitalWrite (PIROSLED, HIGH);
        delay(50);
        digitalWrite (PIROSLED, LOW);
        
        lcd.setCursor(17,2);
        lcd.print("   ");   
}

void FutesBE()
{
  digitalWrite (RELEKE, HIGH);
  //Serial.println("FutesKer:BE");
}

void FutesKI()
{
  digitalWrite (RELEKE, LOW);
  //Serial.println("FutesKer:KI");
}


void Pity()
{
    tone(Pityogo, 1000); // Send 1KHz sound signal...
    delay(50);  
    noTone(Pityogo);     // Stop sound...
    delay(50);        // ...for 1sec
    tone(Pityogo, 1000); // Send 1KHz sound signal...
    delay(50);
    noTone(Pityogo);     // Stop sound...
}







//*********( THE END )******
