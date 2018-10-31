int ledPin = 13;                // IR LED connected to digital pin 13
int rpmcount;
unsigned int rpm;
unsigned long timeold;

// include the library code:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//i2c pins
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //;


void setup()
{
  lcd.begin(16, 2);  // intialise the LCD
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
  //Triggers on FALLING (change from HIGH to LOW)

  attachInterrupt(digitalPinToInterrupt(2), rpm_fun, FALLING);
  //Turn on IR LED


  rpmcount = 0;
  rpm = 0;
  timeold = 0;
}
void rpm_fun()
{
  //Update count

  if (digitalRead(2) == LOW)
  { rpmcount++;
    Serial.println(rpmcount);
  }
  while (digitalRead(2) == LOW) {
    //Serial.print("aa");
  }
  // Serial.println("kk");
  // Serial.println(digitalRead(2));


  //attachInterrupt(digitalPinToInterrupt(2), rpm_fun, FALLING);



}

void loop()
{ if (millis() - timeold >= 1000) {
    /*Uptade every one second, this will be equal to reading frecuency (Hz).*/
    //Don’t process interrupts during calculations
    detachInterrupt(0);
    //Note that this would be 60*1000/(millis() – timeold)*pulses if the interrupt
    //happened once per revolution
    Serial.print("RPMcount:");    Serial.println(rpmcount);
    rpm = 60 * rpmcount;
    // rpm= (60*1000*rpmcount)/(millis()-timeold);
    timeold = millis();
    rpmcount = 0;
    //Write it out to serial port
    lcd.clear();
    lcd.print("RPM = ");
    lcd.print(rpm);
    Serial.println(rpm);
    //Restart the interrupt processing
    attachInterrupt(digitalPinToInterrupt(2), rpm_fun, FALLING);
  }
}
