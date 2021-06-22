/****************************
*	Bluetooth remote car	    *
*	NTUmaker				          *
*	Teacher :				          *
*		阿湯				              *
*	Platform :				        *
*		Arduino nano		        *
****************************/

/****************************
*		    Header files	     	*
****************************/
//#include <SoftwareSerial.h>

/****************************
*		    Pin definitions	  	*
****************************/
#define RxD 5 //connected to Bluetooth module TxD port
#define TxD 6 //connected to Bluetooth module RxD port
//SoftwareSerial BT(RxD,TxD); // create a software serial port for Bluetooth module (recieve(RxD), transmit(TxD))
#define LEFTCONTROL1 8
#define LEFTCONTROL2 9
#define RIGHTCONTROL1 10
#define RIGHTCONTROL2 11
#define speedPWM_R 3 //L293D enable pin
#define speedPWM_L 6 //L293D enable pin

/****************************
*		   Global variables	  	*
****************************/
int byteDataL = 120;
int byteDataR = 100;

/****************************
*		    Setup block	    		*
****************************/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  BT.begin(9600);  
//  Serial.println("BT is ready!");
  pinMode(LEFTCONTROL1, OUTPUT);
  pinMode(LEFTCONTROL2, OUTPUT);
  pinMode(RIGHTCONTROL1, OUTPUT);
  pinMode(RIGHTCONTROL2, OUTPUT);
//  pinMode(speedPWM, OUTPUT);
}

/****************************
*		    Functions block	   	*
****************************/
void leftForward() {
     digitalWrite(LEFTCONTROL1, 1);
     digitalWrite(LEFTCONTROL2, 0);
}
void leftBackward() {
     digitalWrite(LEFTCONTROL1, 0);
     digitalWrite(LEFTCONTROL2, 1);
}
void rightForward() {
     digitalWrite(RIGHTCONTROL1, 1);
     digitalWrite(RIGHTCONTROL2, 0);
}
void rightBackward() {
     digitalWrite(RIGHTCONTROL1, 0);
     digitalWrite(RIGHTCONTROL2, 1);
}

void leftStop() {
     digitalWrite(LEFTCONTROL1, 0);
     digitalWrite(LEFTCONTROL2, 0);
}

void rightStop() {
     digitalWrite(RIGHTCONTROL1, 0);
     digitalWrite(RIGHTCONTROL2, 0);
}

void motorOn() {
  analogWrite(speedPWM_R, byteDataR);
  analogWrite(speedPWM_L, byteDataL);
}

void motorOnTurn() {
  analogWrite(speedPWM_R, 90);
  analogWrite(speedPWM_L, 90);
}

void motorOff() {
  analogWrite(speedPWM_R, 0);
  analogWrite(speedPWM_L, 0);
}

void delayAndStop() {
  delay(100);
  motorOff();
}

/****************************
*		    Loop block	    		*
****************************/
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){ //Something be transmitted from Bluetooth module
    char BTRead = Serial.read();
    Serial.print(BTRead);
  
    switch(BTRead) {
      case '0':
        motorOff(); //disable motor      
      break;
      case '1' : //↑
//        digitalWrite(speedPWM, 1); //Enable motor   
        motorOn();
        leftForward();  //left wheel spins forward
        rightForward(); //right wheel spins forward
        delayAndStop();
      break;
      case '2' : //↓
//        digitalWrite(speedPWM, 1); //Enable motor  
        motorOn(); 
        leftBackward();  //left wheel spins backward
        rightBackward(); //right wheel spins backward
        delayAndStop();
      break;
      case '3' : //→
//        digitalWrite(speedPWM, 1); //Enable motor   
        motorOnTurn();  
        leftForward();   //left wheel spins forward
        // rightBackward(); //right wheel spins backward
        rightStop();
        delayAndStop();
      break;
      case '4' : //←
//        digitalWrite(speedPWM, 1);
        motorOnTurn();  
        //leftBackward(); //left wheel spins backward
        leftStop();
        rightForward(); //right wheel spins forward
        delayAndStop();
      break;
      default:
      //nothing
      break;
    }
  }
//  if (Serial.available()) { //BT command
//    BT.write(Serial.read());
//  }
}
