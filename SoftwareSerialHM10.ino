#include <SoftwareSerial.h>
#include <Timer.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

//made for making starting height 0
float zero=0;

//Vars for logging height during launch
Timer t;
int currTime=0;
int tickEvent;
int logs[240];

SoftwareSerial mySerial(7, 8); // RX, TX
void setup() {
  Serial.begin(57600);
  Serial.println("start transmission");

  pinMode(13,OUTPUT);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("s - start logging for 60s \n g - get logs \n c - get current height");

}
void logging()
{
  
  if(currTime>240)
  {
    t.stop(tickEvent);
    mySerial.print("Done logging");
    return;
  }
  logs[currTime]=baro.getAltitude()*100;

 /* Serial.print(currTime/4.0);
  Serial.print("s : ");
  Serial.println(logs[currTime]-zero);
  */
 // mySerial.write("s");
  currTime++;
}
 void startLog(){
    zero = baro.getAltitude();
    currTime=0;
    mySerial.write("began logging");
    //logs
    tickEvent = t.every(250, logging);
  }
void loop() { // run over and over
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
  if (mySerial.available()) {
    char in = mySerial.read();
    if(in=='C'|| in=='c')
    {
      /*
      float pascals = baro.getPressure();
      mySerial.print(pascals/3377); mySerial.print(" Inches (Hg)");
    */
      float altm = baro.getAltitude();
      mySerial.print(altm-zero); mySerial.print(" meters");
 /*   
      float tempC = baro.getTemperature();
      mySerial.print(tempC); mySerial.print("*C");
      */
    }
    if(in=='l'||in=='L')
    {
      zero = baro.getAltitude();
    }
    if(in=='s'||in=='S')
    {
      startLog();
    }
    if(in=='g'||in=='G')
    {
      for(int x=0;x<240;x++)
      {
        mySerial.print(x/4.0);
        mySerial.print("s : ");
        mySerial.print(logs[x]/100.0-zero);
        mySerial.println("m");
      }
    }
  }
  t.update();
}
  void testLights(char in)
  {
    if(in=='A'||in=='a')
    {
      digitalWrite(13, HIGH);
      mySerial.write("LIGHT ON");
    }
    if(in=='B'||in=='b')
    {
      digitalWrite(13, LOW);
      mySerial.write("LIGHT OFF");
    }
  }


