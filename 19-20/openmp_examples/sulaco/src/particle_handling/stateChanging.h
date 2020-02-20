#pragma once

#include "particle.h"
#include "particleStore.h"

    /**
     * alter the rgb value
     */
void changeRGB(particle *in, int red, int green, int blue) {
  in->r = red;
  in->g = green;
  in->b = blue;
}
    
