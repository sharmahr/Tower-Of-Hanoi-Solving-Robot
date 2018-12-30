// Hardik Sharma
// number of moves for solving tower of hanoi with n disk = 2 power n -1


#include <Servo.h>
#include <Math.h>
#define buzzer A0

Servo rotation,arm,leftgrip,rightgrip;                               // create servo object to control a servo

const int diskwidth = 6;                                             // stroing the width of disk
int armangle = 0, rotangle = 0, gripangle = 60, armupangle = 20;     // variable to store the servo position
const int a = 32, b = 82, c = 133;                                   // the value of a b and c reffers to the rotation angle og the arm base
const int totaldisks = 4;
int currentdisk = 1;                                                 // gives the cuurent disk number
const int noofmoves = pow(2,totaldisks) - 1;
int readlength = 0;                                                  // counter variable to store the information of the move i the moves array
const int leaptime = 1000;                                           // delay between the two indivisual movements of the robotic arm
int pegalevel = 63, pegblevel = 87, pegclevel = 86;                  // storing the height of the pegs



struct move{
  int disk;
  int source;
  int destination;
  };

struct move moves[noofmoves];


  
void towerofhanoi(int n,int Sour, int Aux,int Des)
{ 
  if(n == 1)
  {
    Serial.print("Move Disk ");
    moves[readlength].disk = n;
    Serial.print(n);
    Serial.print(" from ");
    moves[readlength].source = Sour;
    Serial.print(moves[readlength].source);
    Serial.print(" to ");
    moves[readlength].destination = Des;
    Serial.print(moves[readlength].destination);
    Serial.println(" ");
    readlength += 1;
    return;
  }
  
  towerofhanoi(n-1,Sour,Des,Aux);
  Serial.print("Move Disk ");
  moves[readlength].disk = n;
  Serial.print(n);
  Serial.print(" from ");
  moves[readlength].source = Sour;
  Serial.print(moves[readlength].source);
  Serial.print(" to ");
  moves[readlength].destination = Des;
  Serial.print(moves[readlength].destination);
  Serial.println(" ");
  readlength += 1;
  towerofhanoi(n-1,Aux,Sour,Des);
}
 
void setup() {
  Serial.begin(9600);
  
  towerofhanoi(totaldisks,a,b,c); // calculating the moves to be performed
  pinMode(buzzer, OUTPUT);
  
  // attaches the servos to the servo objects
  rotation.attach(11);
  arm.attach(10);
  rightgrip.attach(9);
  leftgrip.attach(6);
  
  // sets the initial angle of the servos
  rotation.write(a);
  arm.write(25);
  leftgrip.write(gripangle);
  rightgrip.write(180-gripangle);
  
  delay(leaptime);
}



void sourcePeg(int source){    // To move to the source peg
  
  delay(leaptime);
  rotation.write(source);
  }


void destinationPeg(int destination){  // To move to the destination peg
  
  delay(leaptime);
  rotation.write(destination);
   }


void pickDisk(int source){         // To pick the disk from the peg
  
  delay(leaptime);
  switch(source){
    case a : pegalevel += diskwidth;
             arm.write(pegalevel);
             break;

    case b : pegblevel += diskwidth;
             arm.write(pegblevel);
             break;

    case c : pegclevel += diskwidth;
             arm.write(pegclevel);
             break;                 
     }
  
  closeGrip();
  delay(leaptime);
  arm.write(armupangle);
 }


void placeDisk(int destination){       // To place the disk in the peg
  delay(leaptime);
  switch(destination){
    case a : arm.write(pegalevel);
            pegalevel -= diskwidth;
            break;

    case b : arm.write(pegblevel);
            pegblevel -= diskwidth;
            break;

    case c : arm.write(pegclevel);
            pegclevel -= diskwidth;
            break;                 
     }
     
  openGrip();
  delay(leaptime);
  arm.write(armupangle);
 }


void openGrip(){           // To open the the gripper of the robotic arm 
  gripangle = 60;
  delay(leaptime);
  leftgrip.write(gripangle);
  rightgrip.write(180-gripangle); 
  }


void closeGrip(){          // To close the grip of the robotic arm
  switch(currentdisk){
    
    case 1: gripangle = 106;
    break;

    case 2: gripangle = 99;
    break;

    case 3: gripangle = 95;
    break;

    case 4: gripangle = 90;
    break;
    
    default: gripangle = 60;
    }
    
  delay(leaptime);
  leftgrip.write(gripangle);
  rightgrip.write(180-gripangle);
  }
  

void endMotion(){            // Ending the motion of the robotic arm
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(200);
  endMotion();
  } 

 
void loop() {
  
  for( int i=0; i<15; i++){
    currentdisk = moves[i].disk;
    sourcePeg(moves[i].source);
    pickDisk(moves[i].source);
    destinationPeg(moves[i].destination);
    placeDisk(moves[i].destination);
   }
   
  digitalWrite(buzzer, HIGH);
  arm.write(25);
  rotation.write(a);
  
  delay(leaptime);
  digitalWrite(buzzer, LOW);
  endMotion();
}



