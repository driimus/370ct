#pragma once
#include <string>
/**
* This struct is used when manipulating/initialising the contents of a particle
*/
struct particle {
	/**
	* whether this particle is a collective (representing another node in a distributed architecture)
	*/
  bool isCollective;
	/**
	* the std::string name of this particle
	*/
  std::string name;

	/**
	* the id of this particle
	*/
  int id;
	/**
	* this particles type (collapsor or normal)
	*/
  int type;

	/**
	* particles colour expressed as an rgb int
	*/
	int r;
  	int g;
  	int b;

	/**
	*  what size this particle will have when displayed in a visualisation
	*/
	int size;
	/**
	* this particles mass
	*/
  double mass;
	/**
	* the radius for this particle
	*/
  double radius;

	/**
	* The position of this particle along the X axis
	*/
  double x;

	/**
	* The position of this particle along the Y axis
	*/
  double y;

	/**
	* The position of this particle along the Z axis
	*/
  double z;

	/**
	* The velocity of this particle along the X axis
	*/
  double xv;

	/**
	* The velocity of this particle along the Y axis
	*/
  double yv;

	/**
	* The velocity of this particle along the Z axis
	*/
  double zv;

	/**
	* The force acting on this particle along the X axis
	*/
  double xf;

	/**
	* The force acting on this particle along the Y axis
	*/
  double yf;

	/**
	* The force acting on this particle along the Z axis
	*/
	double zf;

	/**
	* X Axis location member that is read by other particles during integration
	*/
	double x_ext;

	/**
	* Y Axis location member that is read by other particles during integration
	*/
	double y_ext;

	/**
	* Z Axis location member that is read by other particles during integration
	*/
	double z_ext;
	/**
	* The stored initial position of this particle along the X axis
	*/
	double stored_x;

	/**
	* The stored initial position of this particle along the Y axis
	*/
	double stored_y;

	/**
	* The stored initial position of this particle along the Z axis
	*/
	double stored_z;

	/**
	* The stored initial velocity of this particle along the X axis
	*/
	double stored_xv;

	/**
	* The stored initial velocity of this particle along the Y axis
	*/
	double stored_yv;

	/**
	* The stored initial velocity of this particle along the Z axis
	*/
	double stored_zv;
};
