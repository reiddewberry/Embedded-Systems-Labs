//Chandler Reid Dewberry
//11404018
//ECE486 Lab 5
//3/9/17

/*Includes the wdt into this program*/
#include <avr/wdt.h>

// the setup function runs once when you press reset or power the board
void setup() {
  //Starts Serial and disables the WDT
  Serial.begin(9600);
  wdt_disable();
  //Enables the ADC
  ADCSRA |= _BV(ADEN);
  //Prints the Board was reset
  Serial.println("Board was reset");
  Serial.println();
}

// the loop function runs over and over again forever
void loop() {
  //Used to store what is inputted by the user
  String userInput;
  //Used to compare how much time has past since last input
  static long prevTime = millis();
  //Used to store the analog value read
  int analogVal;
  /*tells the user to input
   an 'a' to run lab #4
   and 'b' to run lab #5*/
  Serial.print("Select a type of conversion to perform ('a' for ");
  Serial.println("lab #4, 'b' for lab #5)");

  //While loop runs forever
  while(1){
    //check if there is an input from the user
    if(Serial.available() > 0){
      userInput = Serial.readString();

      /*Checks if a was inputted and runs lab #5 is so*/
      if(userInput == "a"){
        //value to store the total average time to run the ADC
        long avgTime = 0;
        Serial.println("Starting a set of conversions using AnalogRead:");
        //Runs the analogRead() conversion 30 times from lab #5
        for(int x=0; x<30; x++){
          //sets the convTime to current time
          long convTime = micros();
          //runs analogRead() and store the value
          analogVal = analogRead(0);
          //convTime is set again to how long the conversion took
          convTime = (micros()-convTime);
          //Delays the program 250ms to have time to change the value
          delay(250);
          /*These next few lines print what the
          digital value of the analog input was
          and in the amount of time it takes E.g.:
          #1  digital value = 3FF   Time = 118ms*/
          Serial.print("#");
          Serial.print(x+1);
          if(x<9){
            Serial.print(":   digital value = ");
          }
          else{
            Serial.print(":  digital value = ");
          }
          //Adds leading Zeros if needed
          if(analogVal < 256){
            Serial.print(0);
            if(analogVal < 16){
              Serial.print(0);
            }
            //Prints the value in HEX
            Serial.print(analogVal, HEX);
          }
          else{
            Serial.print(analogVal, HEX);
          }
          //prints the conversion time in miscroseconds
          Serial.print("  Time = ");
          Serial.print(convTime);
          Serial.println("usecs");

          avgTime += convTime;
          /*Averages the times and prints
          when it reaches the last of the 30 values*/
          if(x==29){
            Serial.println();
            Serial.print("avg conversion time = ");
            Serial.print(avgTime/30);
            Serial.println("usecs");
            Serial.println();
            /*Sets the time comparator
            to the current time*/
            prevTime = millis();
            //Flushes the serial buffer
            Serial.readString();
            //Runs the loop again
            loop();
          }
        }
      }

      if(userInput == "b"){
        //value to store the total average time to run the ADC
        long avgTime = 0;
        /*Notifies the user that the conversion is
        beginning using polling and port manipulation*/
        Serial.print("Starting a set of conversions using ");
        Serial.println("polling and port manipulation:");
        ADMUX = B01000000; //Sets the ref voltage to 5V
        ADCSRA |= B00000111; //Sets the prescaler to default 128
        for(int x=0; x<30; x++){
          ADCSRA |= _BV(ADSC);
          long convTime = micros();
          while(bit_is_set(ADCSRA,ADSC)){
            /*This loop constantly polls to see
            if the conversion is finished*/
          }
          convTime = (micros()-convTime);
          //Stores the ADC Low in variable Low
          int low  = ADCL;
          //Stores the ADC High in variable High
          int high = ADCH;
          /*Shifts the high value 8 bits left
          and ORs it with low to find
          the actual analog value*/
          analogVal = (high << 8) | low;
          //Delays the program 250ms to have time to change the value
          delay(250);
          /*These next few lines print what the
          digital value of the analog input was
          and in the amount of time it takes E.g.:
          #1  digital value = 3FF   Time = 108ms*/
          Serial.print("#");
          Serial.print(x+1);
          if(x<9){
            Serial.print(":   digital value = ");
          }
          else{
            Serial.print(":  digital value = ");
          }
          //Adds leading Zeros if needed
          if(analogVal < 256){
            Serial.print(0);
            if(analogVal < 16){
              Serial.print(0);
            }
            //Prints the analog value stored in HEX
            Serial.print(analogVal, HEX);
          }
          else{
            Serial.print(analogVal, HEX);
          }
          //prints the conversion time in miscroseconds
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
            /*Sets the time comparator
            to the current time*/
            prevTime = millis();
            //Flushes the serial buffer
            Serial.readString();
            //Runs the loop again
            loop();
          }
        }
      }

      /*if a user inputs an invalid value
      it tells the user and resets the timer*/
      else{
        /*Sets the time comparator
        to the current time*/
        prevTime = millis();
        /*Prints that there was an error
        and restates the only valid inputs*/
        Serial.print("ERROR: An invalid user input - ");
        Serial.println("the only valid user input is 'a' or 'b'");
      }
    }

    /*this runs a 4 second timer before reseting
    the board*/
    if((millis() - prevTime) >= 4000){
      Serial.println();
      //enables the WDT to run for 120ms
      wdt_enable(WDTO_120MS);
      while(1){}
     }
  }
}
