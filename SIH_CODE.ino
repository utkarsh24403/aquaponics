#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


float Celsius = 0;
float Fahrenheit = 0;

int pinDHT11 = A3;
SimpleDHT11 dht11(pinDHT11);

LiquidCrystal_I2C lcd(0x38,20,4); // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd1(0x3F,20,4);

float calibration_value = 21.34;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
void setup() 
{
  sensors.begin();
 Serial.begin(9600);
   Serial.println("Temperature and Humidity Sensor");
  

  
  lcd.begin(20, 4);
  lcd1.begin(20, 4);
  lcd.setCursor(2, 0);
  lcd.print("  PRESENTED BY      ");
  lcd.setCursor(2, 1);
  lcd.print("TEAM KRISHI-TECH    ");
  lcd1.setCursor(0,0);
  lcd1.print("System Status");
  lcd1.setCursor(0,1);
  lcd1.print("Hi PV");
  delay(1000);
  lcd.clear();
 
}
void loop() {

sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);
   

 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value;
 lcd.setCursor(2, 0);
 lcd.print("pH Val:");
 lcd.setCursor(10, 0);
 lcd.print(ph_act);
 byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }

if(Celsius == -127)
  {
    //
    lcd.setCursor(2, 3);
 lcd.print("WTemp:");
 lcd.setCursor(8, 3);
 lcd.print("Calculate......");
 //lcd.print(" C");
  }
  if(Celsius> -127){
  Serial.print(Celsius);
  Serial.print(" C  ");
  Serial.print(Fahrenheit);
  Serial.println(" F");

 lcd.setCursor(2, 3);
 lcd.print("WTemp:");
 lcd.setCursor(10, 3);
 lcd.print(Celsius);
 lcd.print(" C");
  //delay(1000);
}
 
  
  lcd.setCursor(2, 1);
 lcd.print("Temp:");
 lcd.setCursor(8, 1);
 lcd.print(temperature);
 lcd.print(" *C");
  
 
 lcd.setCursor(2, 2);
 lcd.print("RH:");
 lcd.setCursor(7, 2);
 lcd.print(humidity);
 lcd.print(" %");

 

  delay(500);
  lcd.clear();
  

}
