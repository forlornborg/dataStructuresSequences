#include"foxsays.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

struct _foxStructure{
  seq si;
  token next;
  token current;
  int seqCounter;
  token word1;
  token word2;
};

typedef struct _foxStructure foxSeq;

void foxGotoNext(seq* sthis){
  foxSeq* f = (foxSeq*) sthis;
  f -> current = f -> next;
  if(f -> seqCounter %7 == 0){
    f -> next = f -> word2;
  }else{
    f -> next = f -> word1;
  }
  f -> seqCounter++;
}

token foxGetCurrent(seq* sthis){
  foxSeq* this = (foxSeq*) sthis;
  token t;
  //translate integer to string and package in token
  //snprintf(t.text, sizeof(token)-1, "%s",this->current);
  t = this -> current;
  return t; //not a pointer, safe to return;
}

void foxDestroy(seq* sthis){
  free(sthis); //That's it. Just one list here
}


seq * newFoxSaysSeq(token A, token B){
  foxSeq* f = (foxSeq*)malloc(sizeof(foxSeq));
  //develop Interface
  f -> si.getCurrent = foxGetCurrent;
  f -> si.gotoNext = foxGotoNext;
  f -> si.destroy = foxDestroy;

  //initialize my local variables
  f -> word1 = A;
  f -> word2 = B;
  f -> next = A;
  f -> current = A;
  f -> seqCounter = 3;
}
