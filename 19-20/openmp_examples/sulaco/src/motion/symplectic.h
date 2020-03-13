#pragma once
#include "../particle_handling/particleStore.h"

//double sqr(double);
void kick (particleStore, particle *,int, int, double);
void kick_noforceCalc(particle *, int);
void drift (particle *, int);


//double sqr(double x) {
//  return ((x)*(x));
//}


void accountForInertia(particle *single) {
  if (single->type!=0) { //if neither collective or collapsor, neither of which can move
    single->xf = single->xf/single->mass;
    single->yf = single->yf/single->mass;
    single->zf = single->zf/single->mass;
  }
}

/**
 * Symplectic kick method
 */

void kick (particleStore *in, particle *single,int subject, int stepsize, double G)  {
  if (single->type!=0) {//collective or collapsor, neither of which can move
    single->xf=0;
    single->yf=0;
    single->zf=0;
    int i;
    for (i=0;i<in->size;i++) {
      if (i!=subject) {// no self interaction
	double xdist(single->x - in->particleSet[i].x);
	double ydist(single->y - in->particleSet[i].y);
	double zdist(single->z - in->particleSet[i].z);
	double xt(sqr(xdist));
	double yt(sqr(ydist));
	double zt(sqr(zdist));
	double distancesqr(xt+yt+zt);
	double distance(sqrt(distancesqr));
	double f(G * (single->mass * in->particleSet[i].mass) / distancesqr);
	if ((sqr((single->x + (xdist/2)) - in->particleSet[i].x)) < xt) {
	  single->xf+=f*xdist/distance;
	} else {
	  single->xf-=f*xdist/distance;
	}
	if ((sqr((single->y + (ydist/2)) - in->particleSet[i].y)) < yt) {
	  single->yf+=f*ydist/distance;
	} else {
	  single->yf-=f*ydist/distance;
	}
	if ((sqr((single->z + (zdist/2)) - in->particleSet[i].z)) < zt) {
	  single->zf+=f*zdist/distance;
	} else {
	  single->zf-=f*zdist/distance;
	}
      }
    }
    accountForInertia(single);
    single->xv += single->xf*stepsize;
    single->yv += single->yf*stepsize;
    single->zv += single->zf*stepsize;
  }
}

/**
 * kick this particles velocity using the existing force (use on first step)
 */
void kickNoforceCalc(particle *single, int stepsize) {
  if (single->type!=0) {
    single->xv += single->xf*stepsize;
    single->yv += single->yf*stepsize;
    single->zv += single->zf*stepsize;
  }
}

/**
 * drift this particle across some prtion of a step
 */
void drift (particle *single, int stepsize) {
  if (single->type!=0) {
    single->x +=(stepsize*single->xv);
    single->y +=(stepsize*single->yv);
    single->z +=(stepsize*single->zv);
  }
}
