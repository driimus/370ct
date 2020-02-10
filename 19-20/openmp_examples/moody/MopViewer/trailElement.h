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
#ifndef TRAIL_H
#define TRAIL_H
class TrailElement
{
public:
    TrailElement() {
    }
    ~TrailElement () {}
    TrailElement(const TrailElement& te) {
            this->identity = te.identity;
            this->x = te.x;
            this->y = te.y;
            this->z = te.z;
            this->r = te.r;
            this->g = te.g;
            this->b = te.b;
    }
	int identity;
	double x;
	double y;
	double z;
	int r;
	int g;
	int b;
};
#endif // TRAIL_H
