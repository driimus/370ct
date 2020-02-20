#pragma once
#include "particleStore.h"


void addToParticleSet (particleStore *pSet, particle p){
  if (pSet == NULL) { 
    std::cout << "> addToParticleSet called with non allocated particleStore - exiting " << std::endl;
    exit(0);
  }
  int size = pSet->size;

  if (size==0) {
			// we need to create the first array element and initialise it from the one that was
			// passed
    pSet->particleSet =  new particle[1];
    pSet->particleSet[0] = p;
    pSet->size = 1;
  } else {
    // If we got here, then the array has been created, so we can safely extend it
    pSet->size++;
    particle * pArr = new particle[pSet->size];

    for (int x(0);x<pSet->size-1;x++) {
	    pArr[x] = pSet->particleSet[x];
    }
    pArr[pSet->size-1] = p;
    delete [] pSet->particleSet;
    pSet->particleSet= pArr;
    pArr = NULL;
  }
}


void deleteFromParticleSet (particleStore *pSet, int index){
  if (pSet ==NULL) {
    std::cerr  << "> Attempt to delete a member of the particle set before the set exists. Invalid operation prevented - exiting" << std::endl;
    exit(0);
  }
  if (pSet->size!=0) {
    if ((index<0)||(index>pSet->size-1)) {
      std::cerr  << "> Particle set index supplied to deleteFromParticleSet function is out of bounds. Invalid operation prevented - exiting" << std::endl;
      exit(0);
    }
  }
  int x;
  particle * pArr = new particle[pSet->size-1];
  // fill new array, skipping perticle to be deleted
  int i(0);                  
  for (x=0;x<pSet->size;x++) {
    if (x!=index) {
      pArr[i] = pSet->particleSet[x];
      i++;
    }
  }
  delete [] pSet->particleSet;
  pSet->particleSet= pArr;
  pSet->size = pSet->size-1;
  pArr = NULL;
}

