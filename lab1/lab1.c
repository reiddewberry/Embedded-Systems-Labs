//Chandler Reid Dewberry
//11404018
//ECE4 Lab 1
//2/9/17

#define OFF_LED 8             //OFF_LED is created to toggle the off-board LED
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize LED_BUILTIN and OFF_LED as an output.
  //Also, tells the user how the program operates.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OFF_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Please enter 'g' to begin the LEDs and 's' to stop them.");
}

// the loop function runs over and over again forever
void loop() {
  //LEDstart is the string that we will pass in what is inputed from the Serial
  String LEDstart;
  if (Serial.available() > 0) {
    //This if statement sets LEDstart to the input and checks if it is a valid input
    LEDstart = Serial.readString();
    if(LEDstart != "g"){
      //This tells the user to enter the correct input to start the LEDs
      Serial.println("No, Please enter 'g' to start the LEDs.");
    }
  }

  //This prints to the user that the LEDs have started blinking
  if (LEDstart == "g"){Serial.println("The LEDs have been started.");}

  //This loop continuously keeps the LEDs flashing as long as 's' is not typed
  while (LEDstart == "g") {
    String LEDstop;
    digitalWrite(LED_BUILTIN, HIGH);               // turn the On-board LED on
    digitalWrite(OFF_LED, LOW);                    // turn the Off-board LED off
    delay(2000);                                   // wait for 2 seconds
    digitalWrite(LED_BUILTIN, LOW);                // turn the On-board LED off
    digitalWrite(OFF_LED, HIGH);                   // turn the Off-board LED on
    LEDstop = Serial.readString();
    if(LEDstop > "" && LEDstop != "s"){
      //This tells the user to enter the correct input to stop the LEDs
      Serial.println("No, Please enter 's' to stop the LEDs.");
    }
    else if(LEDstop == "s") {
       //This checks if the user has inputted 's' and stops the LEDs if so
      digitalWrite(OFF_LED, LOW);
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("The LEDs have been stopped.");
      break;
    }
  }
}

