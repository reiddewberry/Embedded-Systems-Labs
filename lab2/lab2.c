//Chandler Reid Dewberry
//11404018
//ECE486 Lab 2
//2/16/17

//This is initializing certain variables to a set integer
#define d 2
#define e 3
#define f 4
#define g 5
#define c 7
#define b 8
#define a 9
#define dp 6
#define breadLED 10
#define SWState 12


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as outputs and one input.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(breadLED, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
  pinMode(SWState, INPUT);
  Serial.begin(9600);
  Serial.println("If there is a dot lit then the display is a letter.");
  Serial.println("Count = (decimal) 0 (hex) 0");
}

// the loop function runs over and over again forever
void loop() {
  /*prevState will hold the last State the switch was in
  and count will hold how many time the switch has been changed*/
  int prevState = digitalRead(SWState);
  int count = 0;
  while(1){
    /*curState will hold the current state of the switch*/
    int curState = digitalRead(SWState);

    /*if the switch is changed then the statement is ran.
    It adds 1 to the count and prints the count in Decimal and Hex.*/
    if(curState != prevState){
      count += 1;
      if(count == 16){
        count = 0;
      }
      prevState = curState;
      Serial.print("count = (decimal) ");
      Serial.print(count);
      Serial.print(" (hex) ");
      Serial.print(count, HEX);
      Serial.println();
    }

    /*if the switch is "on" this blinks the on-board
    and off-board LED on in inverse synchronous*/
    if(curState == 1){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the on-board LED on
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the on-board LED off
      digitalWrite(breadLED, HIGH);      // turn the off-board LED on
      delay(1000);                       // wait for a second
      digitalWrite(breadLED, LOW);       // turn the off-board LED off
    }

    /*These if statements turn on the corresponding parts of the
    7 segment display to display the correct count*/
    if(count != 1 && count != 4){
      digitalWrite(a, HIGH);
    }
    else{
      digitalWrite(a, LOW);
    }

    if(count != 5 && count != 6 && count != 12 && count != 14 && count != 15){
      digitalWrite(b, HIGH);
    }
    else{
      digitalWrite(b, LOW);
    }

    if(count != 2 && count != 12 && count != 14 && count != 15){
      digitalWrite(c, HIGH);
    }
    else{
      digitalWrite(c, LOW);
    }

    if(count != 1 && count != 4 && count != 7 && count != 9 && count != 10 && count != 15){
      digitalWrite(d, HIGH);
    }
    else{
      digitalWrite(d, LOW);
    }

    if(count != 1 && count != 3 && count != 4 && count != 5 && count != 7 && count != 9){
      digitalWrite(e, HIGH);
    }
    else{
      digitalWrite(e, LOW);
    }

    if(count != 0 && count != 1 && count != 7 && count != 12 && count != 13){
      digitalWrite(f, HIGH);
    }
    else{
      digitalWrite(f, LOW);
    }

    if(count != 1 && count != 2 && count != 3 && count != 7){
      digitalWrite(g, HIGH);
    }
    else{
      digitalWrite(g, LOW);
    }

    if(count == 10 || count == 11 || count == 12 || count == 13 || count == 14 || count == 15){
      digitalWrite(dp, HIGH);
    }
    else{
      digitalWrite(dp, LOW);
    }
  }
}
