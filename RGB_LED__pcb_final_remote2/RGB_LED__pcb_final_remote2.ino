
#include <IRremote.h>

int Switch1Pin = 4;
int Switch2Pin = 7;
int Switch3Pin = 8;
int redPin = 9;  
int grnPin = 6;
int bluPin = 5;
int whitePin = 3;
int ColorPotPin = A2;
int SpeedPotPin = A3;
int color[3];                    //Colors from SingleKnobColorSelect Function
int currentColor[4];             //Current LED PWM Values

IRrecv irrecv(12);               //Pin the IR Receiver is Attached to
decode_results results;
unsigned int rawCodes[RAWBUF];   // The durations if raw
int wait = 1;


int on[4] = {255, 255, 255, 255};
int black[4]  = {0, 0, 0, 0};
int white[4]  = {0, 0, 0, 255};
int red[4]    = {255, 0, 0, 0};
int green[4]  = {0, 255, 0, 0};
int blue[4]   = {0, 0, 255, 0};
int color1[4] = {255, 25, 0, 0};
int color2[4] = {255, 100, 0, 0};
int color3[4] = {255, 150, 0, 0};
int color4[4] = {255, 255, 0, 0};
int color5[4] = {0, 255, 25, 0};
int color6[4] = {0, 255, 100, 0};
int color7[4] = {0, 255, 150, 0};
int color8[4] = {0, 255, 255, 0};
int color9[4] = {25, 0, 255, 0};
int color10[4] = {100, 0, 255, 0};
int color11[4] = {150, 0, 255, 0};
int color12[4] = {255, 0, 255, 0};
int color13[4] = {0, 0, 0, 0};
int strobeDelay[] = {1, 5, 10, 20, 40, 80, 120, 240, 500, 1000, 5000};

int redVal = black[0];
int grnVal = black[1]; 
int bluVal = black[2];
int whiteVal = black [3];
int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;
int prevW = whiteVal;





void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(redPin, OUTPUT);   
  pinMode(grnPin, OUTPUT);   
  pinMode(bluPin, OUTPUT);  
  pinMode(whitePin, OUTPUT);  
  pinMode (Switch1Pin, INPUT);
  pinMode (Switch2Pin, INPUT);
  pinMode (Switch3Pin, INPUT);
  
//  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);  //Changing PWM settings for all 4 leds to be able to fade,
//  TCCR2B = _BV(CS22);                                              //this disables the IR Recievers functionality 
//  OCR2A = 180;
//  OCR2B = 50;  
}





void loop() {

//1
if (digitalRead(Switch1Pin) == HIGH && digitalRead(Switch2Pin) == HIGH && digitalRead(Switch3Pin)==HIGH) {
    
}
//2
if (digitalRead(Switch1Pin) == HIGH && digitalRead(Switch2Pin) == HIGH && digitalRead(Switch3Pin)==LOW) {
wait = 1;
    if (irrecv.decode(&results)) {
      Serial.println(results.value);
      if (results.value==4294967295){
        delay(5);
      }
      else if (results.value==16195807 || results.value==16748655){fastCrossFade(red);}      //Individual Color Buttons, multiple remote styles
      else if (results.value==16228447 || results.value==16716015){fastCrossFade(green);}
      else if (results.value==16212127 || results.value==16732335){fastCrossFade(blue);}
      else if (results.value==16191727 || results.value==16756815){fastCrossFade(color1);}
      else if (results.value==16199887 || results.value==16754775){fastCrossFade(color2);}
      else if (results.value==16189687 || results.value==16750695){fastCrossFade(color3);}
      else if (results.value==16197847 || results.value==16746615){fastCrossFade(color4);}
      else if (results.value==16224367 || results.value==16724175){fastCrossFade(color5);}
      else if (results.value==16232527 || results.value==16722135){fastCrossFade(color6);}
      else if (results.value==16222327 || results.value==16718055){fastCrossFade(color7);}
      else if (results.value==16230487 || results.value==16713975){fastCrossFade(color8);}
      else if (results.value==16208047 || results.value==16740495){fastCrossFade(color9);}
      else if (results.value==16216207 || results.value==16738455){fastCrossFade(color10);}
      else if (results.value==16206007 || results.value==16734375){fastCrossFade(color11);}
      else if (results.value==16214167 || results.value==16730295){fastCrossFade(color12);}
      else if (results.value==16203967 || results.value==16736415){fastCrossFade(color13);}
      else if (results.value==16244767 || results.value==16764975){fastCrossFade(white);}
      else if (results.value==16769055 || results.value==16236607){fastCrossFade(on);}     
     
      else if (results.value==581859882 || results.value==581859881){                      //Nikon Remote Codes
        singleKnobColorSelect(analogRead(ColorPotPin));
        delay(125);                                                                       //Shutter Opening Delay
        analogWrite(redPin, color[0]); 
        analogWrite(grnPin, color[1]); 
        analogWrite(bluPin, color[2]); 
        analogWrite(whitePin, color[3]); 
        delay(200);                                                                      //Flash Duration
        analogWrite(redPin, 0);     
        analogWrite(grnPin, 0);      
        analogWrite(bluPin, 0);   
        analogWrite(whitePin, 0); 
      }  

      else if (results.value==16240687|| results.value==16773135){                      //Flash Button
        analogWrite(redPin, 255);   
        analogWrite(grnPin, 255);      
        analogWrite(bluPin, 255); 
        analogWrite(whitePin, 255); 
        delay(150);
        analogWrite(redPin, 0);   
        analogWrite(grnPin, 0);      
        analogWrite(bluPin, 0);   
        analogWrite(whitePin, 0); 
      }      

      else if (results.value==16248847 || results.value==16771095){                    //Strobe Button
        do{
          irrecv.resume(); 
          delay(random(25, 100));    
          analogWrite(whitePin, 255); 
          delay(random(50, 150));
          analogWrite(redPin, 0);  
          analogWrite(grnPin, 0);      
          analogWrite(bluPin, 0); 
          analogWrite(whitePin, 0); 
          irrecv.decode(&results);
          Serial.println(results.value);
        } 
        while (results.value!=16203967 && results.value!= 16736415);
      } 

      else if (results.value==16238647 || results.value==16767015){                       //Fade Button
        do{ 
          irrecv.resume(); // Receive the next value 
          wait = 10;
          fastCrossFade(red);
          fastCrossFade(green);  
          fastCrossFade(blue);
          irrecv.decode(&results);
        } 
        while (results.value!=16203967 && results.value!=16736415);
      }  

      else if (results.value==16246807 || results.value==16762935){        //Smooth
        wait = 1000;
        do{ 
          irrecv.resume(); 
          fastCrossFade(red);
          fastCrossFade(green);  
          fastCrossFade(blue);
          irrecv.decode(&results);
        }
        while (results.value!=16203967 && results.value!=16736415);     

      }

      else if (results.value==16220287 || results.value==16720095){      //Dimmer
        if(redVal>2)
        redVal /= 2;
        if(grnVal>2)
        grnVal /= 2; 
        if(bluVal>2)
        bluVal /= 2;
        if(whiteVal>2)
        whiteVal /= 2;
        
        analogWrite(redPin, redVal);   
        analogWrite(grnPin, grnVal);      
        analogWrite(bluPin, bluVal);  
        analogWrite(whitePin, whiteVal);  

      }  

      else if (results.value==16187647 || results.value==16752735){                //Brighter
        if(redVal<120)
        redVal *= 2;
        if(grnVal<120)
        grnVal *= 2; 
        if(bluVal<120)
        bluVal *= 2;
        if(whiteVal<120)
        whiteVal *= 2;

        analogWrite(redPin, redVal);  
        analogWrite(grnPin, grnVal);      
        analogWrite(bluPin, bluVal);   
        analogWrite(whitePin, whiteVal);   
  
      }
      irrecv.resume(); // Receive the next value
    }     
}
//3
if (digitalRead(Switch1Pin) == HIGH && digitalRead(Switch2Pin) == LOW && digitalRead(Switch3Pin)==HIGH) {

}
//4
if (digitalRead(Switch1Pin) == HIGH && digitalRead(Switch2Pin) == LOW && digitalRead(Switch3Pin)==LOW) {

    int strobeMultiplierRead = analogRead(SpeedPotPin); 
    int strobeMultiplierArraySpot = map(strobeMultiplierRead, 0, 1023, 10, 0);
      wait = (strobeDelay[strobeMultiplierArraySpot]);
        singleKnobColorSelect(analogRead(ColorPotPin));
      if(color[0]>0){
        currentColor[0] = color[0];
        currentColor[1] = 0;
        currentColor[2] = 0;
        currentColor[3] = 0;
        fastCrossFade(currentColor);
        }
      if(color[1]>0){
        currentColor[0] = 0;
        currentColor[1] = color[1];
        currentColor[2] = 0;
        currentColor[3] = 0;
        fastCrossFade(currentColor);
      }  
        if(color[2]>0){
        currentColor[0] = 0;
        currentColor[1] = 0;
        currentColor[2] = color[2];
        currentColor[3] = 0;
        fastCrossFade(currentColor);
      }
       if(color[3]>0){
        currentColor[0] = 0;
        currentColor[1] = 0;
        currentColor[2] = 0;
        currentColor[3] = color[3];
        fastCrossFade(currentColor);
      } 
}
//5
if (digitalRead(Switch1Pin) == LOW && digitalRead(Switch2Pin) == HIGH && digitalRead(Switch3Pin)==HIGH) {
    singleKnobColorSelect(analogRead(ColorPotPin));
    int strobeMultiplierRead = analogRead(SpeedPotPin); 
    fastCrossFade(color);
    int delaySpeed = analogRead(SpeedPotPin); 
    int actualDelay = map(strobeMultiplierRead, 0, 1023, 10000, 50);
    delay(actualDelay);
    fastCrossFade(white);
    delay(actualDelay);
}
//6
if (digitalRead(Switch1Pin) == LOW && digitalRead(Switch2Pin) == HIGH && digitalRead(Switch3Pin)==LOW) {
    int strobeMultiplierRead = analogRead(SpeedPotPin); 
    int strobeMultiplierArraySpot = map(strobeMultiplierRead, 0, 1023, 10, 0);
      wait = (strobeDelay[strobeMultiplierArraySpot]);
        singleKnobColorSelect(analogRead(ColorPotPin));
      if(color[0]>0){
        currentColor[0] = color[0];
        currentColor[1] = 0;
        currentColor[2] = 0;
        currentColor[3] = 0;
        fastCrossFade(currentColor);
        fastCrossFade(black);
        }
      if(color[1]>0){
        currentColor[0] = 0;
        currentColor[1] = color[1];
        currentColor[2] = 0;
        currentColor[3] = 0;
        fastCrossFade(currentColor);
        fastCrossFade(black);
      }  
        if(color[2]>0){
        currentColor[0] = 0;
        currentColor[1] = 0;
        currentColor[2] = color[2];
        currentColor[3] = 0;
        fastCrossFade(currentColor);
        fastCrossFade(black);
      }
       if(color[3]>0){
        currentColor[0] = 0;
        currentColor[1] = 0;
        currentColor[2] = 0;
        currentColor[3] = color[3];
        fastCrossFade(currentColor);
        fastCrossFade(black);
      }  
  }
//7
if (digitalRead(Switch1Pin) == LOW && digitalRead(Switch2Pin) == LOW && digitalRead(Switch3Pin)==HIGH) {
    singleKnobColorSelect(analogRead(ColorPotPin));
    int strobeMultiplierRead = analogRead(SpeedPotPin); 
    fastCrossFade(color);
    int delaySpeed = analogRead(SpeedPotPin); 
    int actualDelay = map(strobeMultiplierRead, 0, 1023, 10000, 50);
    delay(actualDelay);
    fastCrossFade(black);
    delay(actualDelay);
}
//8
if (digitalRead(Switch1Pin) == LOW && digitalRead(Switch2Pin) == LOW && digitalRead(Switch3Pin)==LOW) {
    singleKnobColorSelect(analogRead(ColorPotPin));
    analogWrite(redPin, color[0]);
    analogWrite(grnPin, color[1]);
    analogWrite(bluPin, color[2]);
    analogWrite(whitePin, color[3]);
    delay(5);
}

}





//Functions==============================================================================================

int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}


int calculateVal(int step, int val, int i) {
  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}


void fastCrossFade(int color[4]) {
  int stepR = calculateStep(prevR, color[0]);
  int stepG = calculateStep(prevG, color[1]); 
  int stepB = calculateStep(prevB, color[2]);
  int stepW = calculateStep(prevW, color[3]);

  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);
    whiteVal = calculateVal(stepW, whiteVal, i);

    analogWrite(redPin, redVal);   // Write current values to LED pins
    delayMicroseconds(wait); // Pause for 'wait' milliseconds before resuming the loop
    analogWrite(grnPin, grnVal);      
    delayMicroseconds(wait); // Pause for 'wait' milliseconds before resuming the loop
    analogWrite(bluPin, bluVal); 
    delayMicroseconds(wait); // Pause for 'wait' milliseconds before resuming the loop
    analogWrite(whitePin, whiteVal);
    delayMicroseconds(wait); // Pause for 'wait' milliseconds before resuming the loop
  }
  // Update current values for next loop
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
  prevW = whiteVal;
  
}



void slowCrossFade(int color[3]) {
  int stepR = calculateStep(prevR, color[0]);
  int stepG = calculateStep(prevG, color[1]); 
  int stepB = calculateStep(prevB, color[2]);
  int stepW = calculateStep(prevW, color[3]);

  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);
    whiteVal = calculateVal(stepW, whiteVal, i);
    
    analogWrite(redPin, redVal);   // Write current values to LED pins
    delayMicroseconds(wait); // Pause for 'wait' milliseconds before resuming the loop
    analogWrite(grnPin, grnVal);      
    delayMicroseconds(wait); // Pause for 'wait' milliseconds before resuming the loop
    analogWrite(bluPin, bluVal); 
    delayMicroseconds(wait); // Pause for 'wait' milliseconds before resuming the loop
    analogWrite(whitePin, whiteVal);
    delay(wait); // Pause for 'wait' milliseconds before resuming the loop

  }
  // Update current values for next loop
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
  prevW = whiteVal;
}



void singleKnobColorSelect(int potVal){
  if (potVal < 68)
  {color[0] = 255; color[1] = 0; color[2] = 0; color[3] = 0;}
  else if (potVal < 136) 
  {color[0] = 255; color[1] = 128; color[2] = 0; color[3] = 0;}
  else if (potVal < 204) 
  {color[0] = 255; color[1] = 255;  color[2] = 0; color[3] = 0;}
  else if (potVal < 272)
  {color[0] = 128; color[1] = 255; color[2] = 0; color[3] = 0;}
  else if (potVal < 341)
  {color[0] = 0; color[1] = 255; color[2] = 0; color[3] = 0;}
  else if (potVal < 409)
  {color[0] = 0; color[1] = 255; color[2] = 128; color[3] = 0;}
  else if (potVal < 477)
  {color[0] = 0; color[1] = 255; color[2] = 255; color[3] = 0;}
  else if (potVal < 545)
  {color[0] = 0; color[1] = 128; color[2] = 255; color[3] = 0;}
  else if (potVal < 613)
  {color[0] = 0; color[1] = 0; color[2] = 255; color[3] = 0;}
  else if (potVal < 682)
  {color[0] = 128; color[1] = 0; color[2] = 255; color[3] = 0;}
  else if (potVal < 750)
  {color[0] = 255; color[1] = 0; color[2] = 255; color[3] = 0;}
  else if (potVal < 818)
  {color[0] = 255; color[1] = 0; color[2] = 128; color[3] = 0;}
  else if (potVal < 886) 
  {color[0] = 255; color[1] = 255; color[2] = 255; color[3] = 0;}
    else if (potVal < 954) 
  {color[0] = 255; color[1] = 255; color[2] = 255; color[3] = 255;}
  else 
  {color[0] = 0; color[1] = 0; color[2] = 0; color[3] = 0;}
}


