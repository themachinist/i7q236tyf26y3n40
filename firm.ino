fvint dat = 2; //mic Data line goes to pin 2
int clk = 3; //mic Clock line goes to pin 3
int btn = 4; //mic data button to pin 4
int req = 5; //mic REQ line goes to pin 5 through q1 (arduino high pulls request line low)
int i = 0; int j = 0; int k = 0;
int buttonState;
// char u;
byte reading[14];

void setup()
{
  Serial.begin(9600);
  setupPins();
  digitalWrite(clk, HIGH); // enable internal pull ups
  digitalWrite(dat, HIGH); // enable internal pull ups
  digitalWrite(req,LOW);
}

void loop()
{ 
  // set request to low
  digitalWrite(req,LOW);
  
  // read the pushbutton input pin:
  buttonState = digitalRead(btn);

  // unless the data button is pressed
  if (buttonState == LOW) {
    digitalWrite(req, HIGH);
      // generate set request
    for( i = 0; i < 13; i++ ) {
      k = 0;
      for (j = 0; j < 4; j++) {
      while( digitalRead(clk) == LOW) { } // hold until clock is high
      while( digitalRead(clk) == HIGH) { } // hold until clock is low
        bitWrite(k, j, (digitalRead(dat) & 0x1)); // edit post, added a )
      }

      reading[i] = k;
    }

    // print the reading to the serial port
    for ( i = 4; i < 12; i++) {
      Serial.print(reading[i]);
    }
    Serial.println(reading[12]);
    
    digitalWrite(req,LOW);

    delay(100); 
  } 
}

void setupPins() {
  pinMode(req, OUTPUT);
  pinMode(clk, INPUT);
  pinMode(dat, INPUT);
  pinMode(btn, INPUT);
}
