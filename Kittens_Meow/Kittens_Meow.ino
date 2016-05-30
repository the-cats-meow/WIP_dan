
#include "pitches.h"

const int buttonPin = 2;  // the number of the pushbutton pin (2 and 3 are interupt pins)
const int motorPin = 9;   // define the pin the motor is connected to
                          // (if you use pin 9,10,11 or 3you can also control speed)

// test melody, had to add tiny rests between notes to make them definitive and different.
int testMelody[] = {
  REST, NOTE_C4, REST, NOTE_G3, REST, NOTE_G3, REST, NOTE_A3, REST, NOTE_G3, REST, REST, REST, NOTE_B3, REST, NOTE_C4, END
};
int testNoteDurations[] = {
  1, 4, 64, 8, 64, 8, 64, 4, 64, 4, 64, 4, 64, 4, 64, 4,
};
                          
class Motor
{
  // Class Member Variables
  // These are initialized at startup
  int MotorPin;      // the number of the motor pin

  // These maintain the current state
  int oldState;                   // variable for reading the pushbutton status
  unsigned long previousMillis;   // will store last time LED was updated
  int pattern;                    // variable for choosing patterns
  int counter = 0;                // for patterns that incriment something. is currently for testing only

  // Constructor - creates a motor 
  // and initializes the member variables and state
  public:
  Motor(int pin)
  {
  MotorPin = pin;
  pinMode(motorPin, OUTPUT);     
  
  previousMillis = 0; // Unused at the time
  pattern = 0;
  oldState = digitalRead(buttonPin);        
  }

  void Update(){
    ButtonCycle();
    switch(pattern){
      case 0: Blink(); 
      break;
      case 1: PlayNotes(testMelody,testNoteDurations,2000); 
      break;
      case 2: analogWrite(MotorPin,0);
      break;            
      case 3: ; 
      break;
      case 4: ;
      break;
      case 5: ;
      break;
    }
  };
  
  private:
  void Blink2() {
  analogWrite(MotorPin,255);
  delay(500);
  analogWrite(MotorPin,0);
  delay(250);
  };
  
  void Blink()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if(currentMillis % 500 > 250) //250ms on/off time
    {
      //previousMillis = currentMillis;  // Remember the time
      analogWrite(MotorPin,255);  // Update the actual LED
    }
    else if (currentMillis % 500 <= 250)
    {
      //previousMillis = currentMillis;   // Remember the time
      analogWrite(MotorPin,0);   // Update the actual LED
    }
  };

  void Fade() {
    unsigned long currentMillis = millis(); 
    if (currentMillis - previousMillis > 50) {
      previousMillis = currentMillis;  // Remember the time
      long strength = (currentMillis % 510) - 255; //produce a number between -255 and +255
      analogWrite(MotorPin,abs(strength));  // Update the actual LED, uses abs to get absolute value
    }
  };

  //Fade2 is an attempt at a smoother fade. Goes all the way to Zero (off) which is feels like it is less desireable then I wanted, might make a little snippet of code to constain the vibe between two pusling patterns
  void Fade2() {
    unsigned long currentMillis = millis(); 
    if (currentMillis - previousMillis > 5) {  // the "Magic number" is the ms between incrimenting the counter
      previousMillis = currentMillis;  // Remember the time
      counter += 1;
      long strength = (counter % (510)) - 255; //produce a number between -255 and +255
      analogWrite(MotorPin,abs(strength));  // Update the actual LED, uses abs to get absolute value
    }
  };

  //  PlayNotes is used to translate a pair of arrays (notes and durations) into a song
  //  Melody is an array of notes, using their , and 2) their associated Duration (measured by note value, not ms length)
  //  Suggestion to make the starting note a rest (remeber to add a time value with it), code currently skips first note on the first loop.
  //  Finish melody with an END note, tells the machine to loop
  void PlayNotes(int melody[], int noteDurations[], int measureLength)  {
    
    // to calculate the note duration, take measureLength divided by the note type.
    // e.g. quarter note = measure / 4, eighth note = 1000/8, etc.
    // Note: only works for 4/4 time (or anything where top and bottom match) look at ways to fix this in future
    int noteDuration = measureLength / noteDurations[counter];
    unsigned long currentMillis = millis(); 
    if (currentMillis - previousMillis >= noteDuration) {
      counter += 1;
      if (melody[counter] == 1){
        counter = 0;
      }
      if (melody[counter] == 0){
        analogWrite(MotorPin,0);
      }
      else{
        int strength = map(melody[counter], 130, 550, 50, 255);
        analogWrite(MotorPin,strength);
      }
      previousMillis = currentMillis; 
          
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:\
    //int pauseBetweenNotes = noteDuration * 1.30;
    //delay(pauseBetweenNotes);
    }
  };
  
  void ButtonCycle() {
   // Get current button state.
   // Current logic is for pushbutton and not toggle button       
   bool newState = digitalRead(buttonPin);
   // Check if state changed from high to low or vice versa(button press).  
   if ((newState != oldState) && (oldState == HIGH)) {
    // Short delay to debounce button. 
    delay(20);
    // Check if button is still different after debounce.   
    newState = digitalRead(buttonPin); 
    if (newState != oldState) {    
      pattern++;    
      counter = 0;
      if (pattern > 2){
         pattern=0;
      }
     //Set the lastest button state to the old state.
        oldState = newState; 
    }
    }
  else {
    oldState = newState;
    }
  };
};

void setup() {
  
  // initialize the motor pin:
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  }
Motor motor1(motorPin);
 
void loop()                     // run over and over again
 {
 motor1.Update();
 //ButtonCycle();
 //motorOnThenOff();
 //motorOnThenOffWithSpeed();
 //motorAcceleration();
 }
 
/*
 * motorOnThenOff() – turns motor on then off
 * (notice this code is identical to the code we used for
 * the blinking LED)
 */
 void motorOnThenOff(){
   int onTime = 2500;  //the number of milliseconds for the motor to turn on for
   int offTime = 1000; //the number of milliseconds for the motor to turn off for
   
   digitalWrite(motorPin, HIGH); // turns the motor On
   delay(onTime);                // waits for onTime milliseconds
   digitalWrite(motorPin, LOW);  // turns the motor Off
   delay(offTime);               // waits for offTime milliseconds
 }
 
/*
 * motorOnThenOffWithSpeed() – turns motor on then off but uses speed values as well
 * (notice this code is identical to the code we used for
 * the blinking LED)
 */
 void motorOnThenOffWithSpeed(){
   
   int onSpeed = 200;  // a number between 0 (stopped) and 255 (full speed)
   int onTime = 2500;  //the number of milliseconds for the motor to turn on for
   
   int offSpeed = 50;  // a number between 0 (stopped) and 255 (full speed)
   int offTime = 1000; //the number of milliseconds for the motor to turn off for
   
   analogWrite(motorPin, onSpeed);   // turns the motor On
   delay(onTime);                    // waits for onTime milliseconds
   analogWrite(motorPin, offSpeed);  // turns the motor Off
   delay(offTime);                   // waits for offTime milliseconds
 }
 
/*
 * motorAcceleration() – accelerates the motor to full speed then
 * back down to zero
 */
 void motorAcceleration(){
   int delayTime = 50; //milliseconds between each speed step
   
   //Accelerates the motor
   for(int i = 0; i < 256; i++){ //goes through each speed from 0 to 255
     analogWrite(motorPin, i);   //sets the new speed
     delay(delayTime);           // waits for delayTime milliseconds
   }
   
   //Decelerates the motor
   for(int i = 255; i >= 0; i--){ //goes through each speed from 255 to 0
     analogWrite(motorPin, i);   //sets the new speed
     delay(delayTime);           // waits for delayTime milliseconds
   }
 }

