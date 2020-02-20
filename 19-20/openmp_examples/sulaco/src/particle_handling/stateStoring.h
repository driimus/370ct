#pragma once

#include "particle.h"
#include "particleStore.h"

    /**
     * copy the positional elements of the state vector 
     * to variabes that will be read by other particles during integration
     */
    void updateExternals(particle *in) {
        in->x_ext = in->x;
        in->y_ext = in->y;
        in->z_ext = in->z;
    }
    

    /**
     * Record the starting position of this particle, to be used for later resets
     */
    void storeCurrentPosition(particle *in) {
        in->stored_x = in->x;
        in->stored_y = in->y;
        in->stored_z = in->z;
    }
    
    /**
     * Record the starting velocity of in particle, to be used for later resets
     */
    void storeCurrentVelocity(particle *in) {
        in->stored_xv = in->xv;
        in->stored_yv = in->yv;
        in->stored_zv = in->zv;
    }
    
    /**
     * Record the starting velocity of in particle, to be used for later resets
     */
    void storeCurrentStateVector(particle *in) {
        storeCurrentPosition(in);
        storeCurrentVelocity(in);
    }
    /**
     * Reset in particles position using previously stored values
     */
    void resetToStoredPosition(particle *in) {
        in->x = in->stored_x;
        in->y = in->stored_y;
        in->z = in->stored_z;
    }
    
    /**
     * Reset in particles velocity using previously stored values
     */
    void resetToStoredVelocity(particle *in) {
        in->xv = in->stored_xv;
        in->yv = in->stored_yv;
        in->zv = in->stored_zv;
    }
    /**
     * Reset in particles positon and velocity using previously stored values
     */
    void resetToStoredStateVector(particle *in) {
        resetToStoredPosition(in);
        resetToStoredVelocity(in);
    }
    
    
