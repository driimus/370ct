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
#ifndef TRAILSET_H
#define TRAILSET_H
#include <cstdlib>
#include "singletrail.h"
//#include <QDebug>
class TrailSet
{
private:
	SingleTrail *trailHistorySet;
	int numTrails;
	int trailSize;
public:

	TrailSet(int numTrails, int trailSize) {
                trailHistorySet = new SingleTrail[numTrails];
		for (int x(0);x<numTrails;x++) {
                        trailHistorySet[x].createTrail(trailSize);
		}
		this->numTrails = numTrails;
                this->trailSize = trailSize;

	}

	~TrailSet(){
                delete [] trailHistorySet;
                this->numTrails = 0;
                this->trailSize = 0;
	}

	SingleTrail *getTrail(int index) {
		if ((index>=0)&&(index<this->numTrails)){
			return (trailHistorySet+index);
		}
		return NULL;
	}

	void blankTrails() {
		for (int x(0);x<numTrails;x++) {
			trailHistorySet[x].blankTrail();;
		}
	}

};

#endif // TRAILSET_H
