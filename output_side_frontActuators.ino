// Analog input pins for the PLC signal
#define FL_VOLTAGEPIN A0 //Connect PLC voltage signal for the position of the Front Left Linear Actuator to this pin
#define FR_VOLTAGEPIN A1 //Connect PLC voltage signal for the position of the Front Right Linear Actuator to this pin

// Ditital output pins with PWM for the MC signal
#define FL_PWMR 10 //RPWM pin on MotorController Front Left Linear Actuator
#define FL_PWML 9  //RPWM pin on MotorController Front Left Linear Actuator
#define FR_PWMR 6  //RPWM pin on MotorController Front Right Linear Actuator
#define FR_PWML 5  //LPWM pin on MotorController Front Right Linear Actuator

// Variables to store the old and new target speed in
int NewTargetSpeedFL;
int NewTargetSpeedFR;
int OldTargetSpeedFL;
int OldTargetSpeedFR;
// Variables to store the PWM signal value in
float pwmValueFLL;
float pwmValueFLR;
float pwmValueFRL;
float pwmValueFRR;

void setup()
{
  Serial.begin(9600);
  pinMode(FL_VOLTAGEPIN, INPUT);
  pinMode(FR_VOLTAGEPIN, INPUT);
  pinMode(FL_PWMR, OUTPUT);
  pinMode(FL_PWML, OUTPUT);
  pinMode(FR_PWMR, OUTPUT);
  pinMode(FR_PWML, OUTPUT);
}


void loop()
{
  // Check to see in which direction the LA needs to move. 
  OldTargetSpeedFL = NewTargetSpeedFL;
  NewTargetSpeedFL = analogRead(FL_VOLTAGEPIN);
  
  OldTargetSpeedFR = NewTargetSpeedFR;
  NewTargetSpeedFR = analogRead(FR_VOLTAGEPIN);

  Serial.print("Signal from A0: ");
  Serial.println(NewTargetSpeedFL);

  // Write speed signal to either Right or Left PWM pin for Front Left Linear Actuator
  if (OldTargetSpeedFL > NewTargetSpeedFL)
  {
    pwmValueFLR = NewTargetSpeedFL/4;
    analogWrite(FL_PWMR, pwmValueFLR);
    analogWrite(FL_PWML, 0);
    Serial.print("FL extending, PWM value: ");
    Serial.println(pwmValueFLR);
    Serial.println("--------------------------------------------------------------");
  }
  else if (OldTargetSpeedFL <= NewTargetSpeedFL)
  {
    pwmValueFLL = NewTargetSpeedFL/4;
    analogWrite(FL_PWML, pwmValueFLL);
    analogWrite(FL_PWMR, 0);
    Serial.print("FL retracting, PWM value: ");
    Serial.println(pwmValueFLL);
    Serial.println("--------------------------------------------------------------");
  }

  // Write speed signal to either Right or Left PWM pin for Front Right Linear Actuator
  if (OldTargetSpeedFR > NewTargetSpeedFR)
  {
    pwmValueFRR = NewTargetSpeedFR/4;
    analogWrite(FR_PWMR, pwmValueFRR);
    analogWrite(FR_PWML, 0);
    Serial.print("FR extending, PWM value: ");
    Serial.println(pwmValueFRR);
    Serial.println("--------------------------------------------------------------");
  }
  else if (OldTargetSpeedFR <= NewTargetSpeedFR)
  {
    pwmValueFRL = NewTargetSpeedFR/4;
    analogWrite(FR_PWML, pwmValueFRL);
    analogWrite(FR_PWMR, 0);
    Serial.print("FR extending, PWM value: ");
    Serial.println(pwmValueFRR);
    Serial.println("--------------------------------------------------------------");
  }
}
