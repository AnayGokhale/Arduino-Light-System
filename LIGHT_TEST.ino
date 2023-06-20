#include <LiquidCrystal.h>
const int pin = A0;
int rawValue = 0;
int timer = 0;
int minutes = 0;
int hours = 0;
int seconds = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int state = 0;
bool buttonPressed = false;
bool done = false;
int loopms=50;
int count = 1000/loopms;
int oneTimeDelay = 3000;
int batterySaver = 5;
void setup() { 
  // put your setup code here, to run once:
pinMode(6, INPUT);
lcd.begin(16, 2);
lcd.
lcd.setCursor(0, 0);
lcd.print("STARTED");
lcd.setCursor(0, 1);
lcd.print("PRESS BUTTON");
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(6) ==  HIGH){
  buttonPressed = true;
}
else{
  buttonPressed = false;
}
switch(state){
  case 0:
    original();
    break;
  case 1:
    highdetected();
    break;
  case 2:
    buttonPress();
    break;
  case 3:
  if(buttonPressed){
    state = 1;
    done = true;
  }
  else{
    count--;
    if (count == 0)
    {
      reader();
      count = 1000/loopms;
    }
  } 
  break;
  case 4:
    if(oneTimeDelay != 0){
    stopRead();
    delay(oneTimeDelay);
    oneTimeDelay = 0;
    }
    if(buttonPressed){
      state = 1;
      done = false;
      oneTimeDelay = 3000;
      timer = 0;
      batterySaver = 5;
    }
    break;
}
delay(loopms);
}
void original(){
if(buttonPressed){
  state = 1;
}
else{
  state = 0;
}
}
void highdetected(){
if(buttonPressed){
  state = 1;
}
else{
  state = 2;
}
}
void buttonPress(){
  if(done){
    state = 4;
  }
  else if(buttonPressed){
    state = 1;
  }
  else if(!buttonPressed){
    state = 3;
  }
}
void reader(){
  //run code
  if(batterySaver == 0){
    lcd.noDisplay();
  }
  else{
    batterySaver--;
    lcd.display();
  }
  rawValue = analogRead(pin);
  delay(5);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reading: ");
  lcd.print(rawValue);
  lcd.setCursor(0, 1);
  lcd.print("SunTime: ");
  lcd.print(timer);
  if(rawValue >= 1010){
    timer += 1.0;
 }         
  //end reader code
}
void stopRead(){
  //print final results
  seconds = timer;
  minutes = seconds / 60;
  hours = minutes / 60;
  seconds = timer - (minutes * 60);
  minutes = minutes - (hours * 60);
  lcd.display();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Final Sun Time: ");
  lcd.setCursor(0, 1);
  lcd.print(hours);
  lcd.print("hrs ");
  lcd.print(minutes);
  lcd.print("mins ");
  lcd.print(seconds);
  lcd.print("s");

}
