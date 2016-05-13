const int buttonPin = 2;     // the number of the pushbutton pin
const int motorPin = 9;  // define the pin the motor is connected to
                         // (if you use pin 9,10,11 or 3you can also control speed)
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
 
 void setup()
 {
  // initialize the motor pin:
  pinMode(motorPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
 }
 
 
void loop()                     // run over and over again
 {
 motorOnThenOff();
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

