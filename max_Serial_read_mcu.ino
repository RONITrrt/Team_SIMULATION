#define BLYNK_TEMPLATE_ID           "TMPL3GbhxEtp0"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "sytHauxw1s1bZaxQzRGTG5rNQDRBMqKb"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Health";
char pass[] = "12345678";
void setup() 
{
Serial.begin(115200);
pinMode(LED_BUILTIN, OUTPUT);
Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
delay(1000);
while (!Serial) 
{
; 
}
}

String bpm;
String spo2;
char inData[20];
int inDataCount=0;
void loop() 
{ 

if (Serial.available())
{
  
 while (Serial.available())
 {     digitalWrite(LED_BUILTIN, HIGH);
       inData[inDataCount] = Serial.read();
      //Serial.print(inData[inDataCount]);
      //Serial.print("  ");
      //Serial.println(inDataCount);
      
      if(inData[inDataCount] == '!')
      {
        inData[inDataCount] = '\0';
        bpm = String(inData);
        inDataCount=0;
      }
      else if(inData[inDataCount] == '@')
      {
        inData[inDataCount] = '\0';
        spo2 = String(inData);
        inDataCount=0;
      }
      
      else if(inData[inDataCount] == '\n')
     {
        inDataCount=0;
        inData[inDataCount] = '\0';
      }
      else
      {
      inDataCount++;    
      }
 }
  Serial.println("--------------------------");

  Serial.print("BPM=");
  Serial.println(bpm);
  Serial.print("SPO2=");
  Serial.println(spo2);
  Serial.println("--------------------------");
Blynk.virtualWrite(V0,bpm.toFloat());  
Blynk.virtualWrite(V1,spo2.toFloat());    
digitalWrite(LED_BUILTIN, LOW); 
}

Blynk.run(); // Initiates Blynk

}
