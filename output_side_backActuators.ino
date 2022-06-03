// Analog input pins for the PLC signal
#define BL_VOLTAGEPIN A0 //Connect PLC voltage signal for the position of the Back Left Linear Actuator to this pin
#define BR_VOLTAGEPIN A1 //Connect PLC voltage signal for the position of the Back Right Linear Actuator to this pin

// Ditital output pins with PWM for the MC signal
#define FL_PWMR 10 //RPWM pin on MotorController Back Left Linear Actuator
#define FL_PWML 9  //RPWM pin on MotorController Back Left Linear Actuator
#define FR_PWMR 6  //RPWM pin on MotorController Back Right Linear Actuator
#define FR_PWML 5  //LPWM pin on MotorController Back Right Linear Actuator

// Variables to store the old and new target speed in
int NewTargetSpeedBL;
int NewTargetSpeedBR;
int OldTargetSpeedBL;
int OldTargetSpeedBR;
float pwmValueBLL;
float pwmValueBLR;
float pwmValueBRL;
float pwmValueBRR;

void setup()
{
  Serial.begin(9600);
  pinMode(BL_VOLTAGEPIN, INPUT);
  pinMode(BR_VOLTAGEPIN, INPUT);
  pinMode(BL_PWMR, OUTPUT);
  pinMode(BL_PWML, OUTPUT);
  pinMode(BR_PWMR, OUTPUT);
  pinMode(BR_PWML, OUTPUT);
}


void loop()
{
  // Check to see in which direction the LA needs to move. 
  OldTargetSpeedBL = NewTargetSpeedBL;
  NewTargetSpeedBL = analogRead(BL_VOLTAGEPIN);
  
  OldTargetSpeedBR = NewTargetSpeedBR;
  NewTargetSpeedBR = analogRead(BL_VOLTAGEPIN);

  // Write speed signal to either Right or Left PWM pin for FL
  if (OldTargetSpeedBL > NewTargetSpeedBL)
  {
    pwmValueBLR = NewTargetSpeedBL/4;
    analogWrite(BL_PWMR, pwmValueBLR);
    analogWrite(BL_PWML, 0);
    Serial.print("FL extending, PWM value: ");
    Serial.println(pwmValueBLR);
  }
  else if (OldTargetSpeedBL <= NewTargetSpeedBL)
  {
    pwmValueBLL = NewTargetSpeedBL/4;
    analogWrite(BL_PWML, pwmValueBLL);
    analogWrite(BL_PWMR, 0);
    Serial.print("FL retracting, PWM value: ");
    Serial.println(pwmValueFLL);
  }

  // Write speed signal to either Right or Left PWM pin for FR
  if (OldTargetSpeedBR > NewTargetSpeedBR)
  {
    pwmValueBRR = NewTargetSpeedBR/4;
    analogWrite(BR_PWMR, pwmValueBRR);
    analogWrite(BR_PWML, 0);
    Serial.print("FR extending, PWM value: ");
    Serial.println(pwmValueBRR);
  }
  else if (OldTargetSpeedBR <= NewTargetSpeedBR)
  {
    pwmValueBRL = NewTargetSpeedBR/4;
    analogWrite(BR_PWML, pwmValueBRL);
    analogWrite(BR_PWMR, 0);
    Serial.print("FR extending, PWM value: ");
    Serial.println(pwmValueBRR);
  }
  
}
