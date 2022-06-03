#include "AD5593R.h"

AD5593R AD5593R(23);
bool my_DACs[8] = {1,1,1,1,1,1,1,1}; //Choose which channels need to be configured as Digital Analog Convertors

#define FL_VOLTAGEPIN A0

float feedbackFL = 0;
float oldSpeedSignal;
float newSpeedSignal;
float x = 0;

void setup()
{
  Serial.begin(9600);
  AD5593R.enable_internal_Vref();    //Enable the internal voltage supply
  AD5593R.set_DAC_max_2x_Vref();     //Set the max channel voltage to 2 times the internal votlage
  AD5593R.configure_DACs(my_DACs);   //Configure chosen channels to Digitial Analog Convertors
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  AD5593R.write_DAC(0,2.5);
  AD5593R.write_DAC(1,2.5);
  Serial.println("--------------------------------------------------------------");
}

void loop()
{
  delay(500);
  if (x>=100)
  {
    float randomValue0 = random(500, 4500);      // Generate random value for random voltage (X-axis)
    Serial.print("Random X: ");
    Serial.println(randomValue0);
    float voltageXtemp = randomValue0 /1000;
    float voltageX = voltageXtemp + 0.04;

    float randomValue1 = random(500, 4500);      // Generate random value for random voltage (X-axis)
    Serial.print("Random Z: ");
    Serial.println(randomValue1);
    float voltageZtemp = randomValue1 / 1000;
    float voltageZ = voltageZtemp + 0.04;

    Serial.print("Target channel 0 (X): ");
    Serial.println(voltageXtemp);
    Serial.print("Targer channel 1 (Z): ");
    Serial.println(voltageZtemp);
    AD5593R.write_DAC(0,voltageX);              //Analog Input on the PLC for X wire
    AD5593R.write_DAC(1,voltageZ);              //Analog Input on the PLC for Z wire
    Serial.println("---------------------------------------------------------------");
    x = 0;
  }
  x+=1;
  Serial.print("X: ");
  Serial.println(x);

  
  oldSpeedSignal = newSpeedSignal;
  newSpeedSignal = analogRead(FL_VOLTAGEPIN);
  Serial.print("InputVoltage is: ");
  Serial.println(newSpeedSignal/200);
  
  if (newSpeedSignal > oldSpeedSignal)
  {
    if (newSpeedSignal <= 200 && feedbackFL < 4.9)
    {
      feedbackFL += 0.1;
    }
    else if (200 < newSpeedSignal && newSpeedSignal <= 400 && feedbackFL < 4.8)
    {
      feedbackFL += 0.2;
    }
    else if (400 < newSpeedSignal && newSpeedSignal <= 600 && feedbackFL < 4.7)
    {
      feedbackFL += 0.3;
    }
    else if (600 < newSpeedSignal && newSpeedSignal <= 800 && feedbackFL < 4.6)
    {
      feedbackFL += 0.4;
    }
    else if (800 < newSpeedSignal && feedbackFL < 4.5)
    {
      feedbackFL += 0.5;
    }
  }
  else if (newSpeedSignal < oldSpeedSignal)
  {
    if (newSpeedSignal <= 200 && feedbackFL > 0.1)
    {
      feedbackFL -= 0.1;
    }
    else if (200 < newSpeedSignal && newSpeedSignal <= 400 && feedbackFL > 0.2)
    {
      feedbackFL -= 0.2;
    }
    else if (400 < newSpeedSignal && newSpeedSignal <= 600 && feedbackFL > 0.3)
    {
      feedbackFL -= 0.3;
    }
    else if (600 < newSpeedSignal && newSpeedSignal <= 800 && feedbackFL > 0.4)
    {
      feedbackFL -= 0.4;
    }
    else if (800 < newSpeedSignal && feedbackFL > 0.5)
    {
      feedbackFL -= 0.5;
    }
  }
  Serial.print("Feedback is: ");
  Serial.println(feedbackFL);
  AD5593R.write_DAC(2,feedbackFL);
}
