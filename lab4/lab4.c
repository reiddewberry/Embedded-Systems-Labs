//Chandler Reid Dewberry
//11404018
//ECE486 Lab 4
//3/2/17

/*Includes the wdt into this program*/
#include <avr/wdt.h>

// the setup function runs once when you press reset or power the board
void setup() {
  //Starts Serial and disables the WDT
  Serial.begin(9600);
  wdt_disable();
}

// the loop function runs over and over again forever
void loop() {
  /*initializes the user input from the serial buffer,
  the timer value prevTime, the value for analog input,
  and tells the user to input a 'c'*/
  String userInput;
  static long prevTime = millis();
  int analogVal;
  Serial.println("Enter 'c' to start a set of conversions.");

  while(1){
    int notifyTimeout = 0;

    //check if there is an input from the user
    if(Serial.available() > 0){
      userInput = Serial.readString();

      /*Checks if c was inputted and runs a loop 30 times
      and prints out the values of the pot and the
      amount of time to read the value*/
      if(userInput == "c"){
        long avgTime = 0;
        for(int x=0; x<30; x++){
          long convTime = micros();
          analogVal = analogRead(0);
          convTime = (micros()-convTime);
          delay(250);
          Serial.print("#");
          Serial.print(x+1);
          if(x<9){
            Serial.print(":   digital value = ");
          }
          else{
            Serial.print(":  digital value = ");
          }
          if(analogVal < 256){
            Serial.print(0);
            if(analogVal < 16){
              Serial.print(0);
            }
            Serial.print(analogVal, HEX);
          }
          else{
            Serial.print(analogVal, HEX);
          }
          Serial.print("  Time = ");
          Serial.print(convTime);
          Serial.println("usecs");

          avgTime += convTime;
          /*Averages the times and prints
          it then runs the loop again*/
          if(x==29){
            Serial.println();
            Serial.print("avg conversion time = ");
            Serial.print(avgTime/30);
            Serial.println("usecs");
            Serial.println();
            prevTime = millis();
            Serial.readString();
            loop();
          }
        }
      }

      /*if a user inputs an invalid value
      it tells the user and resets the timer*/
      else{
        prevTime = millis();
        Serial.println("ERROR: An invalid user input - the only valid user input is 'c'");
        Serial.println("Enter 'c' to start a set of conversions.");
      }
    }

    /*this runs a 4 second timer before reseting
    the board*/
    if((millis() - prevTime) >= 4000){
      Serial.println("Board was reset");
      wdt_enable(WDTO_120MS);
      while(1){}
     }
  }
}
