#include <NewPing.h>


#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(A3, A2, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(A0, A1, MAX_DISTANCE), 
};

//TODO: Динамично свързване + в метода да се подава като аргумент "LOW" или "HIGH"
#define led1EchoPin A1 // Echo Pin
#define led1TrigPin A0 // Trigger Pin
#define led2EchoPin A2
#define led2TrigPin A3


int a[] = {2,9};  // Digit_1 "A" segment => Aduino pin 2
int b[] = {3,10};  // Digit_1 "B" segment => Aduino pin 3
int c[] = {4,11};  // Digit_1 "C" segment => Aduino pin 4
int d[] = {5,12};  // Digit_1 "D" segment => Aduino pin 5
int e[] = {6,13};  // Digit_1 "E" segment => Aduino pin 6
int f[] = {7,14};  // Digit_1 "F" segment => Aduino pin 7 
int g[] = {8,15};  // Digit_1 "G" segment => Aduino pin 8

//7 Segments digits flags pins
const int digit11= 17; 
const int digit12 = 18;
const int digit21 = 19;
const int digit22 = 20;


int distance,distance2, lastmeters = 0, currentmeters = 0; 
long duration, duration2;

//Flag pins array for first 7 segment display
int ledDisplay1FlagPins[] = {17,18};

//Flaf pins array for second 7 segment display
int ledDisplay2FlagPins[] = {19,20};


//Draw the distance from sensor to 7 segment displays
void DisplayDistance(int Distance, int digit, int displayNumber){
  
  clearDisplays();

  if(displayNumber == 0){ //first display
  
    for (int i = 0; i < 2; i++) //set which digit have to work
    {
      digitalWrite(ledDisplay1FlagPins[i], i == digit ? 1 : 0);
    }
  }else if(displayNumber == 1){ //second display
    for (int i = 0; i < 2; i++) //set which digit have to work
    {
      digitalWrite(ledDisplay2FlagPins[i], i == digit ? 1 : 0);
    }
  }
    
  //Shows a number on display
    switch(Distance){
      case 0 : DisplayZero(displayNumber); 
               break;
      case 1 : DisplayOne(displayNumber); 
               break;
      case 2 : DisplayTwo(displayNumber); 
               break;
      case 3 : DisplayThree(displayNumber); 
               break;
      case 4 : DisplayFour(displayNumber); 
               break;
      case 5 : DisplayFive(displayNumber); 
               break;
      case 6 : DisplaySix(displayNumber); 
               break;
      case 7 : DisplaySeven(displayNumber);
               break;
      case 8 : DisplayEight(displayNumber); 
               break;
      case 9 : DisplayNine(displayNumber);
               break;
    }

}

void DisplayZero(int displayNumber) {
  digitalWrite(a[displayNumber], HIGH);
  digitalWrite(b[displayNumber], HIGH);
  digitalWrite(c[displayNumber], HIGH);
  digitalWrite(d[displayNumber], HIGH);
  digitalWrite(e[displayNumber], HIGH);
  digitalWrite(f[displayNumber], HIGH);
}

void DisplayOne(int displayNumber){
  digitalWrite(b[displayNumber], HIGH);
  digitalWrite(c[displayNumber], HIGH);  
}
void DisplayTwo(int displayNumber) {
  digitalWrite(a[displayNumber], HIGH);
  digitalWrite(b[displayNumber], HIGH);
  digitalWrite(d[displayNumber], HIGH);
  digitalWrite(e[displayNumber], HIGH);
  digitalWrite(g[displayNumber], HIGH);
}
void DisplayThree(int displayNumber) {
  digitalWrite(a[displayNumber], HIGH);
  digitalWrite(b[displayNumber], HIGH);
  digitalWrite(c[displayNumber], HIGH);
  digitalWrite(d[displayNumber], HIGH);
  digitalWrite(g[displayNumber], HIGH);
}
void DisplayFour(int displayNumber) {
  digitalWrite(b[displayNumber], HIGH);
  digitalWrite(c[displayNumber], HIGH);
  digitalWrite(f[displayNumber], HIGH);
  digitalWrite(g[displayNumber], HIGH);
}
void DisplayFive(int displayNumber) {
  digitalWrite(a[displayNumber], HIGH);
  digitalWrite(c[displayNumber], HIGH);
  digitalWrite(d[displayNumber], HIGH);
  digitalWrite(f[displayNumber], HIGH);
  digitalWrite(g[displayNumber], HIGH);
}
void DisplaySix(int displayNumber) {
 digitalWrite(a[displayNumber], HIGH);
 digitalWrite(c[displayNumber], HIGH);
 digitalWrite(d[displayNumber], HIGH);
 digitalWrite(e[displayNumber], HIGH);
 digitalWrite(f[displayNumber], HIGH);
 digitalWrite(g[displayNumber], HIGH);
}
void DisplaySeven(int displayNumber) {
 digitalWrite(a[displayNumber], HIGH);
 digitalWrite(b[displayNumber], HIGH);
 digitalWrite(c[displayNumber], HIGH); 
}
void DisplayEight(int displayNumber) {
  digitalWrite(a[displayNumber], HIGH);
  digitalWrite(b[displayNumber], HIGH);
  digitalWrite(c[displayNumber], HIGH);
  digitalWrite(d[displayNumber], HIGH);
  digitalWrite(e[displayNumber], HIGH);  
  digitalWrite(f[displayNumber], HIGH);
  digitalWrite(g[displayNumber], HIGH);
}
void DisplayNine(int displayNumber) {
  digitalWrite(a[displayNumber], HIGH);
  digitalWrite(b[displayNumber], HIGH);
  digitalWrite(c[displayNumber], HIGH);
  digitalWrite(d[displayNumber], HIGH);
  digitalWrite(f[displayNumber], HIGH);  
  digitalWrite(g[displayNumber], HIGH);
}

//Set all pins(without flags) to LOW, because it will get display overlight
void clearDisplays(){
  for(int i = 2; i <= 20; i++){
    digitalWrite(i, LOW);
  }
}

//Calsulate distance
void Calculate(int Distance, int displayNumber){
  
  
  //Serial.println("Calculate...");
  //Because the distance is from 2 digits -> dm, for that reason it gets the second digit and show it on second place on the display
  DisplayDistance(Distance % 10, 1, displayNumber);
  delay(2);
  //Because the distance is from 2 digits -> dm, for that reason it gets the first digit and show it on first place on the display
  DisplayDistance(Distance / 10, 0, displayNumber);
  delay(2);
}

void setup() {
  Serial.begin(9600);
  for(int i = 2; i <= 16; i++){
    pinMode(i, OUTPUT); 
    digitalWrite(i, LOW);  
  }

  for(int i = digit11; i <= digit22; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i, LOW);  
  }
}

void loop() {

  Calculate(sonar[0].ping_cm() / 10, 0);

  Serial.println("SecondDistance is : ");
  Serial.print(sonar[1].ping_cm());
  Calculate(sonar[1].ping_cm() / 10, 1);
  
}


