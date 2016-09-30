#include"rot.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

/*
Pattern of rot
A, A+B, B, 0, -A, -A-B, -B, 0, ...
*/

struct _rotStructure{
  seq si; //an instance of the itnerface
  int next;
  int current;
  int ABArray[4];
  int seqCounter;
  int posNegCounter;
};

typedef struct _rotStructure rot;


/*
rotGetCurrent PsuedoCode

*/
token rotGetCurrent(seq* sthis){
  //from fib
  rot* this = (rot*) sthis;
  token t;
  //translate integer to string and package in token
  snprintf(t.text, sizeof(token)-1, "%d",this->current);
  return t; //not a pointer, safe to return;
}

/*
rotGotoNext PsuedoCode
seqCounter
posnegCounter. neg if 0
create a for loop which will run through ABArray
set current to ABArray[seqCounter]
if(posNegCounter is true) then multiply current by -1
if seqCounter reaches 4, flip posNegCounter. seqCounter goes to 0

*/
void rotGotoNext(seq* sthis){
  //abCounter: 0 = A. 1 = B+A. 2 = B. 3 = 0;
  rot * this = (rot*)sthis;
  this -> current = this -> next;
  if(this -> posNegCounter){ //if positive
    this -> next = (this ->ABArray[this -> seqCounter]);

  }else{ //make negative
    this -> next = -1*(this ->ABArray[this -> seqCounter]);
  }
  this -> seqCounter++;
  //if mod 4 then we need to loop
  //flip the posNegCounter

  if(this -> seqCounter == 4){
    this -> seqCounter = 0;
    if(this -> posNegCounter == 1){
      this -> posNegCounter = 0;
    }else{
      this -> posNegCounter = 1;
    }
  }


}

void rotDestroy(seq* sthis){
  free(sthis); //All that is necessary
}

//rot Constructor
seq* newRotSeq(int A, int B){
  rot * r = (rot*)malloc(sizeof(rot)); //allocating space for sequence
  //inhereting si functions
  r -> si.getCurrent = rotGetCurrent;
  r -> si.gotoNext = rotGotoNext;
  r -> si.destroy = rotDestroy;
  //private variables of this specific instance
  r -> ABArray[0] = A;
  r -> ABArray[1] = A+B;
  r -> ABArray[2] = B;
  r -> ABArray[3] = 0;
  r -> current = A;
  r -> next = A + B;
  int i = 0;
  r -> posNegCounter = 1;
  r -> seqCounter = 2;

  return (seq*) r; //return pointer to instance
}
