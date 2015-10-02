// G.E. Barkhuff, Spring 2015
// Touchable Canvas
// Major Hardware: Velostat, Arduino Uno Microcontroller, LEDs
// Some code adapted from the Velostat Light-Up Sneaker Tutorial
// found at https://learn.adafruit.com/firewalker-led-sneakers/make-velostat-step-sensors

// INIT:
// pins for the five LEDs
int pinA = 0;
int pinB = 1;
int pinC = 2;
int pinD = 3;
int pinE = 4;

//array for pins
int pinArray[5] = {pinA, pinB, pinC, pinD, pinE};

//boolean array to hold if LED is on/off
boolean LEDOn[5] = {false, false, false, false, false};

// Analog input pins that the Velostat is attached to
const int analogZone0 = A0;  
const int analogZone1 = A1;
const int analogZone2 = A2;
const int analogZone3 = A3;
const int analogZone4 = A4;

// array to hold hold initial values read from the Velostat potentiometer
int initArray[5];

//array to hold current sensed value
int sensorArray[5];


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  
  loop to init all LED pins as output
  for (int i = 0; i< 5; i++){
  pinMode(pinArray[i], OUTPUT);
  }
  
  
  //setup the analog pins as pullup/ send power through them
  digitalWrite(analogZone0, HIGH);
  digitalWrite(analogZone1, HIGH);
  digitalWrite(analogZone2, HIGH);
  digitalWrite(analogZone3, HIGH);
  digitalWrite(analogZone4, HIGH);
  
  //get initial sensor values
  initRead();
  
  //print values
  Serial.print("i0: ");
  Serial.print(initArray[0]);
  Serial.print("; i1: ");
  Serial.print(initArray[1]);
  Serial.print("; i2: ");
  Serial.print(initArray[2]);
  Serial.print("; i3: ");
  Serial.print(initArray[3]);
  Serial.print("; i4: ");
  Serial.println(initArray[4]);
  
  //turn lights off to begin
  for (int i = 0; i<5; i++)
  {
   digitalWrite(pinArray[i], LOW); 
   
  }
  
}

void loop() {
  // read the analog in value:
  readSensors();
  
  // print the results to the serial monitor:
  printPressures();
  
  //check to see if pressure sensors activated
  sensorActivated();
  
  //turn on/off appropriate LEDs
  setOffLights();
  
  delay(500);
  
}


/**
*The readSensors() method reads the current value from the Velostat potentiometer
* on all 5 of the pressure zones.
**/
void readSensors()
{
  //for each of the five pressure sensors
  for (int i = 0; i<5; i++)
  {
   sensorArray[i] = 3 * analogRead(i);
  }
}

/**
*The initRead() method takes an initial average value for all
*five pressure zones, to be compared with later to tell if pressure
*has been applied.
**/
void initRead()
{ 
  //for each of the five sensors
  for (int j = 0; j<5; j++)
  {
    //get 100 readings, add together
    for (int i = 0; i<100; i++)
    {
    initArray[j] = initArray[j]+ analogRead(j);
    }
    //take average of the 100, 
    //then multiple by three to help detect sensitive pressure
    initArray[j] = (initArray[j]/100) * 3;
  }
}


/**
*The printPressures() method prints the pressure readings for all five zones
*to the serial monitor
**/
void printPressures()
{
  Serial.print("Zone 0 = ");
  Serial.print(sensorArray[0]);
  Serial.print("; 1 = ");
  Serial.print(sensorArray[1]);
  Serial.print("; 2 = ");
  Serial.print(sensorArray[2]);
  Serial.print("; 3 = ");
  Serial.print(sensorArray[3]);
  Serial.print("; 4 = ");
  Serial.println(sensorArray[4]);

}

/**
*sensorActivated() compares the init reading on the Velostat to the
*current reading to tell if pressure has been applied.
**/
void sensorActivated()
{
    //for all five pressure sensors
    for (int i = 0; i<5; i++)
    {
    //check if sensorArrayX is less than initArrayX
    if (sensorArray[i] - initArray[i] < -10){
      //turn boolean of array LEDOn to true
      LEDOn[i] = true; 
    }//close if
    else
    {
      //set boolean to false
      LEDOn[i] = false;
    }//close else
}
    
/**
*setOffLights() gets run during every loop iteration
*to turn on the lights corresponding to zones that have been activated.
**/
}

void setOffLights()
{
  //for all five LEDs
  for (int i = 0; i<5; i++)
  //if boolean is true, turn on
  if (LEDOn[i] == true)
  {
    digitalWrite(i, HIGH);
    
  }//end if
  //otherwise turn off/keep off
  else
  {
    digitalWrite(i, LOW);
  }
}
