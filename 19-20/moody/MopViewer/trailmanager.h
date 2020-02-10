/**
* Author      : Dr Carey Pridgeon
* Copyright   : Dr Carey Pridgeon 2009
* Licence     : Licensed under the Apache License, Version 2.0 (the "License");
*             : you may not use this file except in compliance with the License.
*             : You may obtain a copy of the License at
*             : http://www.apache.org/licenses/LICENSE-2.0
*             :
*             : Unless required by applicable law or agreed to in writing,
*             : software distributed under the License is distributed on
*             : an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
*             : either express or implied. See the License for the specific
*             : language governing permissions and limitations under the License.
*/
#ifndef TRAILMANAGER_H
#define TRAILMANAGER_H

#include "trailset.h"
#include "mophandling.h"
#include "../moody/capsule/capsuleBase/etc/Advisor.h"
class TrailManager
{
private:

	TrailSet *trails;
	int trailSize;
	int numTrails;
        bool trailsExist;
public:

        TrailManager() {
            this->trailsExist = false;
        }


	~TrailManager() {
		if (this->trailsExist) {
                        delete this->trails;
		}
	}

        void createTrails (MopHandling *mop, int trailSize) {
                int count(0);
                for (int x=0;x<mop->getNumParticles();x++) {
                        if (mop->getLoadedState()->getMopItem(x).identity !=Advisor::nonInteractive) {
                            count++;
                        }
                }

                this->trails = new TrailSet(count,trailSize);
                this->trailSize = trailSize;
                this->numTrails = count;
                for (int x=0;x<this->numTrails;x++) {
                        this->trails->getTrail(x)->blankTrail();
                }
                this->trailsExist = true;
        }

        void deleteTrails() {
                if (this->trailsExist) {
                        delete this->trails;
                        this->numTrails = 0;
                        this->trailSize = 0;
                        this->trailsExist = false;
                }
        }

        void deleteTrailAtIndex(int index) {
                if (this->trailsExist) {
                        if ((index>-1)&&(index<this->numTrails)) {
                                TrailSet * tmp = new TrailSet(this->numTrails-1,this->trailSize);
                                // copy over existing trail content, excluding the trail to be deleted
                                for (int x(0);x<this->numTrails;x++) {
                                        if (x!=index) {
                                                for (int y(0); y<this->trailSize;y++) {
                                                        tmp->getTrail(x)->fillTrailIndex(this->trails->getTrail(x)->getTrailIndex(y),y);
                                                }
                                        }
                                }
                                this->numTrails+=1;
                                delete this->trails;
                                this->trails = tmp;
                                tmp = NULL;
                                this->numTrails-=1;
                        }
                }
        }

	void updateTrails(MopHandling *mop) {
		if (this->trailsExist) {
			for (int x=0;x<mop->getNumParticles();x++) {
                                if (mop->getLoadedState()->getMopItem(x).identity !=Advisor::nonInteractive) {
                                        this->trails->getTrail(x)->addNewEntry(mop->getDisplayState()->getMopItem(x));
				}
			}
		}
	}

	void clearTrails() {
		if (this->trailsExist) {
                        for (int x=0;x<this->numTrails;x++) {
				this->trails->getTrail(x)->blankTrail();
			}
		}
	}

	void resizeTrails(int trailSize){
                if (this->trailsExist) {
			for (int x(0);x<this->numTrails;x++) {
                            this->trails->getTrail(x)->resizeTrail(trailSize);
			}
                        this->trailSize = trailSize;
                }
	}

	void addTrail() {
		if (this->trailsExist) {
			TrailSet * tmp = new TrailSet(this->numTrails+1,this->trailSize);
			// copy over existing trail content first
			for (int x(0);x<this->numTrails;x++) {
				for (int y(0); y<this->trailSize;y++) {
					tmp->getTrail(x)->fillTrailIndex(this->trails->getTrail(x)->getTrailIndex(y),y);
				}
			}
                        delete this->trails;
			this->trails = tmp;
			tmp = NULL;
			this->numTrails+=1;
		}
	}

        void displayTrails(int focusParticle, bool showTrailsForSelectedParticlesOnly, bool selectedParticleOneActive, bool selectedParticleTwoActive, int selectedParticleOne, int selectedParticleTwo, int xRot, int yRot, int zRot){
                if (this->trailsExist) {
			glPushMatrix();
			glLoadIdentity();
			glRotated(xRot, 1.0, 0.0, 0.0);
			glRotated(yRot, 0.0, 1.0, 0.0);
			glRotated(zRot, 0.0, 0.0, 1.0);
                        glDisable(GL_LIGHTING);
                        if (showTrailsForSelectedParticlesOnly) {
                            if (selectedParticleOneActive) {

                                 for (int i(0);i<this->trails->getTrail(selectedParticleOne)->getCurrentdisplayIndex();i++) {
                                     glColor3ub (this->trails->getTrail(selectedParticleOne)->getTrailIndex(i).r,this->trails->getTrail(selectedParticleOne)->getTrailIndex(i).g,this->trails->getTrail(selectedParticleOne)->getTrailIndex(i).b);
                                     glBegin(GL_POINTS);
                                        glVertex3f(this->trails->getTrail(selectedParticleOne)->getTrailIndex(i).x-this->trails->getTrail(focusParticle)->getTrailIndex(i).x,this->trails->getTrail(selectedParticleOne)->getTrailIndex(i).y-this->trails->getTrail(focusParticle)->getTrailIndex(i).y,this->trails->getTrail(selectedParticleOne)->getTrailIndex(i).z-this->trails->getTrail(focusParticle)->getTrailIndex(i).z);
                                     glEnd();
                                 }

                            }
                            if (selectedParticleTwoActive) {

                                     for (int i(0);i<this->trails->getTrail(selectedParticleTwo)->getCurrentdisplayIndex();i++) {
                                         glColor3ub (this->trails->getTrail(selectedParticleTwo)->getTrailIndex(i).r,this->trails->getTrail(selectedParticleTwo)->getTrailIndex(i).g,this->trails->getTrail(selectedParticleTwo)->getTrailIndex(i).b);
                                         glBegin(GL_POINTS);
                                             glVertex3f(this->trails->getTrail(selectedParticleTwo)->getTrailIndex(i).x-this->trails->getTrail(focusParticle)->getTrailIndex(i).x,this->trails->getTrail(selectedParticleTwo)->getTrailIndex(i).y-this->trails->getTrail(focusParticle)->getTrailIndex(i).y,this->trails->getTrail(selectedParticleTwo)->getTrailIndex(i).z-this->trails->getTrail(focusParticle)->getTrailIndex(i).z);
                                         glEnd();
                                     }

                             }
                                glEnd();
                        } else {
                                for (int x(0);x<this->numTrails;x++) {
                                        for (int y(0);y<this->trails->getTrail(x)->getCurrentdisplayIndex();y++) {
                                             glBegin(GL_POINTS);
                                                glColor3ub (this->trails->getTrail(x)->getTrailIndex(y).r,this->trails->getTrail(x)->getTrailIndex(y).g,this->trails->getTrail(x)->getTrailIndex(y).b);
                                                glVertex3f(this->trails->getTrail(x)->getTrailIndex(y).x-this->trails->getTrail(focusParticle)->getTrailIndex(y).x,this->trails->getTrail(x)->getTrailIndex(y).y-this->trails->getTrail(focusParticle)->getTrailIndex(y).y,this->trails->getTrail(x)->getTrailIndex(y).z-this->trails->getTrail(focusParticle)->getTrailIndex(y).z);
                                             glEnd();
                                        }

                                }

                        }
                        glPopMatrix();
                        glEnable(GL_LIGHTING);
                }
	}

	int getTrailSize() {
		return this->trailSize;
	}

	int getNumTrails() {
		return this->numTrails;
	}



	bool getDoTrailsExist() {
		return this->trailsExist;
	}
};

#endif // TRAILMANAGER_H
