#define DELAY 5       //change this if u want to increase or decrease the delay(in min)
#define VALVE_PIN 2   //change this if you want to change the valve pin
#define MOTOR_PIN 3   // change this is u want to change the motor pin
                      //both motor pin and valve should be turned low for the circuit to complete in relay module 
#define PINA 4  // these 2 are for completing the circuit, at completing, valve will turn off and motor will turn on.
#define PINB 5  //both these pins will check alternatively, to prevent corrosion
​
bool alternated_flag = true, water_filled = false;

void alternate(){ //keeps changing the polarity of the circuit(to avoid corrosion)
  if (alternated_flag){  //when true, PINB is the input
    pinMode(PINA,OUTPUT);
    pinMode(PINB,INPUT);
    digitalWrite(PINA,HIGH);
  }
  else{
    pinMode(PINB,OUTPUT);   // when false PINA is the input
    pinMode(PINA,INPUT);
    digitalWrite(PINB,HIGH);
​
  }
  alternated_flag = not alternated_flag;
}
​
bool check(){ //returns the state of the circuit; true if its complete, false if its incomplete
 
  if (alternated_flag) return digitalRead(PINB);
  return digitalRead(PINA);
}
​
void setup() {
  pinMode(VALVE_PIN,OUTPUT);  digitalWrite(VALVE_PIN,HIGH);
  pinMode(MOTOR_PIN,OUTPUT);  digitalWrite(MOTOR_PIN,HIGH);
}
​
void loop() {
  
  if (check() ) {  // if the circuit is complete, turn off the valve and turn on the motor
    digitalWrite(VALVE_PIN,HIGH);
    digitalWrite(MOTOR_PIN,LOW);
    water_filled = true;
  }
​
  if (water_filled){  
    delay( DELAY * 60000);     // 60 000 millis is one min
    water_filled = false;
  }
  else if ( !check() && !water_filled ){
    digitalWrite(VALVE_PIN,LOW);
    digitalWrite(MOTOR_PIN,HIGH);     
  }
​
  alternate();     
}
