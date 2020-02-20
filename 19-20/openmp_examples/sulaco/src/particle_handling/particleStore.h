#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <fstream>
#include <memory>
#include "particle.h"
/**
 * I've tried, but this type cannot be immutable without a *severe* performance impact.
 * for thread safety, whenever you change it (add/delete particles) be careful that only add OR delete are happening, and then only one instance of each.
 * particles cannot help but have pos and velocity updated, hence the impossibility of imutability. 
 * Thread safety for such things is handled up the chain of functions.
 */
typedef struct particleStore {
  particle *particleSet;
  int size;
} particleStore;

void allocateParticleStore(particleStore *store){
  store = new particleStore;
  store->size = 0;
}
