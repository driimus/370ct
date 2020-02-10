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
#ifndef SINGLETRAIL_H
#define SINGLETRAIL_H
#include "../moody/capsule/capsuleBase/mopfile/MopItem.h"
#include "trailElement.h"
class SingleTrail
{
private:
        TrailElement * trail;
	int currentIndex;
	int currentSize;
	bool trailExists;
public:
	SingleTrail() {
		this->currentIndex = 0;
		this->currentSize = 0;
		this->trailExists = false;
	}

	~SingleTrail() {
		if (this->trailExists) {
			delete [] this->trail;
		}

	}

	void createTrail(int trailSize) {
                this->trail = new TrailElement[trailSize];
		this->currentSize = trailSize;
		this->currentIndex = 0;
		this->trailExists = true;
	}

	void resizeTrail(int trailSize) {
		if (this->trailExists) {
                        this->trailExists = false;
			delete [] this->trail;
                        this->trail = new TrailElement[trailSize];
			this->currentSize = trailSize;
			this->currentIndex = 0;
                        this->trailExists = true;
		}
        }

	void blankTrail() {
                if (this->trailExists) {
			this->currentIndex = 0;
                }
                for (int x(0);x<this->currentSize;x++) {
                        this->trail[x].x= 0;
                        this->trail[x].y= 0;
                        this->trail[x].z= 0;
                        this->trail[x].identity = 0;
                        this->trail[x].r = 0;
                        this->trail[x].g = 0;
                        this->trail[x].b = 0;
                }
	}

        TrailElement * getTrail() {
		if (this->trailExists) {
			return this->trail;
		}
	}

        void addNewEntry(MopItem item ) {
                if (this->trailExists) {
                    if (this->currentIndex!=0) {
                        int k=this->currentIndex-1;
                        for (int i(0);i<this->currentIndex;i++) {
                                this->trail[k] = this->trail[k-1];
                                k--;
                        }
                        this->trail[0].identity = item.identity;
                        this->trail[0].x = item.x;
                        this->trail[0].y = item.y;
                        this->trail[0].z = item.z;
                        this->trail[0].r = item.red;
                        this->trail[0].g = item.green;
                        this->trail[0].b = item.blue;
                        if (this->currentIndex<this->currentSize) {
                                this->currentIndex++;
                        }
                    } else {
                        this->trail[0].identity = item.identity;
                        this->trail[0].x = item.x;
                        this->trail[0].y = item.y;
                        this->trail[0].z = item.z;
                        this->trail[0].r = item.red;
                        this->trail[0].g = item.green;
                        this->trail[0].b = item.blue;
                        this->currentIndex++;
                    }
                }
	}

	int getCurrentSize() {
		if (this->trailExists) {
			return this->currentSize;
		}
		return 0;
	}
	int getCurrentdisplayIndex() {
		if (this->trailExists) {
			return this->currentIndex;
		}
		return 0;
	}

        TrailElement & getTrailIndex(int index) {
                if ((index>=0)&&(index<this->currentSize)) {
			return this->trail[index];
		}
		// default return index 0;
		return this->trail[0];
	}

        void fillTrailIndex (TrailElement & info, int index ) {
		if (this->trailExists) {
                        if ((index>=0)&&(index<this->currentSize)) {
				this->trail[index].identity = info.identity;
				this->trail[index].x = info.x;
				this->trail[index].y = info.y;
				this->trail[index].y = info.z;
				this->trail[index].r = info.r;
				this->trail[index].g = info.g;
				this->trail[index].b = info.b;
			}
		}
	}

};

#endif // SINGLETRAIL_H
