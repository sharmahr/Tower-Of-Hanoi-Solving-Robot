# Tower-Of-Hanoi-Solving-Robot

Tower Of Hanoi :

The Tower of Hanoi is a mathematical game or puzzle. It consists of three rods and a number of disks of different sizes, which can slide onto any rod. The puzzle starts with the disks in a neat stack in ascending order of size on one rod, the smallest at the top, thus making a conical shape.

The objective of the puzzle is to move the entire stack to another rod, obeying the following simple rules:

    1) Only one disk can be moved at a time.
    2) Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack or on an empty rod.
    3) No larger disk may be placed on top of a smaller disk.

With 3 disks, the puzzle can be solved in 7 moves. The minimal number of moves required to solve a Tower of Hanoi puzzle is 2n − 1, where n is the number of disks. In my case there are 4 disk therefore the number of moves required are 15.

Code snippet :

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

This recursive fnction gives the steps to be performed by the robotic arm to solve The Tower Of Hanoi problem. Each move is a structure which contains the following attributes:

   1) current disk 
   2) source location 
   3) destination location
   
   code snippet:
   
   struct move{
     int disk;
     int source;
     int destination;
  };
   
 These moves re stored in an array so that the can be mapped by the robotic arm.  The robotic arm maps these moves by using the following functions:
 
void sourcePeg(int source)                // To move to the source peg
void destinationPeg(int destination)      // To move to the destination peg
void pickDisk(int source)                 // To pick the disk from the peg
void placeDisk(int destination)           // To place the disk in the peg
void openGrip()                           // To open the the gripper of the robotic arm 
void closeGrip()                          // To close the grip of the robotic arm
void endMotion()                          // Ending the motion of the robotic arm
