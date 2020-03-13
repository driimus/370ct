#pragma once
#include "symplectic.h"
#include <omp.h>

void setExternals(particleStore *);
void symplecticStep(int,particleStore *,double, bool *);


/**
 * Symplectic Integrator that makes use of OpenMP
 */
void symplecticStepOMP(int stepsize,particleStore *in,double G, bool *firstKick) {
  int i;
  setExternals(in); // calls omp inside the function, since it gets called over the entire set, it needs no wrapping
  if (firstKick) {
    #pragma omp parallel for
    for (i=0;i<in->size;i++) {// run over entire set, iterating one particle in each loop
      kick (in,&(in->particleSet[i]),i,stepsize/4,G);
    }
    *firstKick=false;
  } else {
    #pragma omp parallel for
    for (i=0;i<in->size;i++) {// run over entire set, iterating one particle in each loop
      kickNoforceCalc(&(in->particleSet[i]),stepsize/4);
    }
  }
  //drift half the step
  #pragma omp parallel for
  for (i=0;i<in->size;i++) {// run over entire set, iterating one particle in each loop
    drift (&(in->particleSet[i]),stepsize/2);
  }
  //kick for half a step
  #pragma omp parallel for
  for (i=0;i<in->size;i++) { // run over entire set, iterating one particle in each loop
    kick (in,&(in->particleSet[i]),i,stepsize/2,G);
  }
  //drift for half a step
  #pragma omp parallel for
  for (i=0;i<in->size;i++) { // run over entire set, iterating one particle in each loop
    drift (&(in->particleSet[i]),stepsize/2);
  }
  //kick for the last 1/4 step
  #pragma omp parallel for
  for (i=0;i<in->size;i++) { // run over entire set, iterating one particle in each loop
    kick (in,&(in->particleSet[i]),i,stepsize/4,G);
  } 
}

/**
 * setting the external references for the particles that enable lock free integration
 * in a parallel for
 */
void setExternals(particleStore *in) {
  int i;
  #pragma omp parallel for
  for (i=0;i<in->size;i++) {
    in->particleSet[i].x_ext=in->particleSet[i].x;
    in->particleSet[i].y_ext=in->particleSet[i].y;
    in->particleSet[i].z_ext=in->particleSet[i].z;
  }
}
