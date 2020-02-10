%module pyMoody
%include "std_string.i"
%feature("autodoc", "1");

%{
  #include "../moody/moody.h"
 %}

#include ../moody/moody.h

	/**
	* This is the core class for Moody
	*/
	class Capsule {

	public:
	Capsule(void);
	~Capsule(void);

	/**
	* copy constructor
	*/
	Capsule(const Capsule& cb);

	/**
	* simple runtime timing class. Has unpredicatable behaviour on parallel systems. Basically it's pants and needs redesigning
	*/
	Timing timer;

	/**
	* class that handles reading/writing of mo files (the output files for moody)
	*/
	MopFile *mop;
	
	/**
	* method that will replace the current content of this capsule with that of another
	*/
	void fillFromExistingCapsule (const Capsule & other);
	
	/**
	* parallell Symplectic second order Integration
	*/
	void iterateSym();

	 /**
	* parallel MidPoint second order Integration
	*/
	void iterateMidPoint();
	
	/**
	* parallell RK4 fourth order Integration
	*/
	void iterateRK4();

	/**
	* Mathematical functions and operations. Here it's public, whereas other Moody classes use it privatelly.
	*/
	Numerics maths;
	
	/**
	* prepare the annealer for use in Stochastic Hill Climbing.
	* it only needs to be allocated once, all other calls to this method will just reset it.
 the annealer uses such a tiny amount of memory and gets deleted when the capsule is
	* itself deleted, there is no explicit delete method.
	*/
	virtual void prepareAnnealer( int runningTime,  double haltingPct = 0);

	/**
	* How many particles are currently in the model? (includes non interactive particles)
	*/
	int getEnvironmentSetSize();

	/**
	* How many particles are there in the environment set which haven't been put there in order to make room for fitness testing chromosomes
	*/
	int getOriginalEnvironmentSetSize();
	
	/**
	* How many particles are currently in the experimentation population?
	*/
	int getPopulationSetSize();

	/**
	* How many particles are currently in the intermediate set?
	*/
	int getIntermediateSetSize();
	
	/**
	* tells you the current mop file name in use
	*/
	std::string getMopName();
	
	/**
	* Returns a specified member of the environment set. Causes an exit if the array index is out of bounds.
	*/
	Particle &getEnvironmentSetMember( int index);

	/**
	* Returns a specified member of the population set. Causes an exit if the array index is out of bounds.
	*/
	Particle &getPopulationSetMember( int index);

	/**
	* Returns a specified member of the intermediate set. Causes an exit if the array index is out of bounds.
	*/
	Particle &getIntermediateSetMember( int index);
	/**
	* This method is used when adding a particle to the set stored in this Capsule.
	* Either appends to the end of the array, or creates the array if it doesn't exist yet.
	* Updates record of particle array length
	*/
	void addToEnvironmentSet (Particle &p);

	/**
	* This method is used when adding a particle to the environment set using a ParticleStruct
	* Either appends to the end of the array, or creates the array if it doesn't exist yet.
	* Updates record of particle array length
	*  - used internally by Moody, you don't need to call this directly.
	*/
	void addToEnvironmentSet (ParticleStruct & ps);

	/**
	* This method is used when removing a paticle from the set stored in this Capsule.
	* Updates record of particle array length
	*  - used internally by Moody, you don't need to call this directly.
	*/
	void deleteFromEnvironmentSet ( int index);

	/**
	* This method is used to add extra array entries to the environment set. These entries are then available for use
	* by chromosomes moved (copied) over from the intermediate set.
	* These extra entries should be filled with proper particles before the environment set is actually used
	*/
	void extendEnvironmentSetWithBlanks (int size);

	/**
	* This method is used to record how many particles there are in the environment set before we
	* add blank entries for use during EA experiments
	*/
	void recordOriginalEnvironmentSize ();

	/**
	* This method is used when adding a particle to the experimentation set stored in this Capsule.
	* Either appends to the end of the array, or creates the array if it doesn't exist yet.
	* Updates record of particle array length
	*/
	void addToPopulationSet (Particle & p);

	/**
	* This method is used when adding a particle to the experimentation set using a particle struct
	* Either appends to the end of the array, or creates the array if it doesn't exist yet.
	* Updates record of particle array length
	*/
	void addToPopulationSet (ParticleStruct & ps);

	/**
	* This method is used when removing a paticle from the experimentation set stored in this Capsule.
	* Updates record of particle array length
	*/
	void deleteFromPopulationSet ( int index);

	/**
	* This method is used when adding a particle to the intermediate set stored in this Capsule.
	* Either appends to the end of the array, or creates the array if it doesn't exist yet.
	* Updates record of particle array length
	*/
	void addToIntermediateSet (Particle & p);

	/**
	* This method is used when adding a particle to the intermediate set from a ParticleStruct
	* Either appends to the end of the array, or creates the array if it doesn't exist yet.
	* Updates record of particle array length
	*/
	void addToIntermediateSet (ParticleStruct & ps);

	/**
	* This method is used when removing a paticle from the intermediate set stored in this Capsule.
	* Updates record of particle array length
	*/
	void deleteFromIntermediateSet ( int index);

	/**
	* Returns the number of states currently set
	*/
	int getNumStates();

	/**
	* Returns the number of steps that occur in each state
	*/
	int getNumSteps();
	
	/**
	* Returns the size of a single step
	*/
	int getStepSize();

	/**
	* Returns the currently set value for G
	*/
	double getGravitationalConstant();

	/**
	* returns the absolute path to the result folder
	*/
	std::string getResultFolder();

	/**
	* possibly obvious what this method does...
	* returns pointless int to stop python wrapping getting confused, blessit...
	*/
	int setRandomSeed(int seed);

	/**
	* This takes the setting from another capsule, replacing those currently present
	*/
	void TakeSettingsFromAnotherCapsule( CapsuleBase &other);

	/**
	* This takes the particles from another capsule, replacing those currently present
	*/
	void TakeParticlesFromAnotherCapsule( CapsuleBase &other);
	
	/**
	* Load a project from the specified folder. Also prepares and records the absolute paths
	* for the particle, cfg and result folders
	*/
	virtual void loadProject(std::string projectFolder);

	/**
	* Export the particle set currently held by this Capsule into a particles.xml file.
	*/
	void exportParticlesToXMLFile(std::string fn);

	/**
	*  Tournament Selection, works for lowest or highest value
	*/
	virtual int tournamentSelection (int num, int direction);

	/**
	*  find least fit member of the population by stored score, works for lowest or highest score.
	*/
	virtual int findLeastFit (int direction);

	/**
	*  Fitness as a measure of proximity to target, to be used while model is iterating
	*/
	virtual double fitnessProximitySingleTarget (int subject, int target);
	
	/**
	* Fitness as a measure of proximity to target, to  be used after model has finished a run.
	* requires that history be recorded for subject and target.
	*/
	virtual double fitnessProximitySingleTargetUsingHistory (int subject,int target);
	
	/**
	* Fitness as a measure of time in relative proximity to target, to  be used after model has finished a run.
	* requires that history be recorded for subject and target.
	* A duration of one will make this perform exactly like 'fitnessProximitySingleTargetUsingHistory'
	*/
	virtual double fitnessProximityAndDurationSingleTargetUsingHistory (int subject,int target , int duration);

	/**
	* Allocates the block of memory required by each particle. How many
	* memory entries are created is specified by the parameter memorySize
	*/
	void createParticleMemory(int memorySize);

	/**
	* Unlike the population of environment sets, the intermediate set is of fixed size
	* particles are moved in and out of currently existing positions.
	* therefore the intermediate set must be created first and
	* filled with 'blank' particles. Placemarkers are used initially.
	*/
	void createIntermediateSet (int size);

	/**
	*  move a particle from the population set to the intermediate set - copies content only, no particle deleted.
	* particle history and memory content are not copied if present
	*/
	void moveParticleFromPopulationToIntermediateSet (int subject, int target);

	/**
	*  move a particle from the intermediate set to the population set
	* particle history and memory content are not copied if present
	*/
	void moveParticleFromIntermediateToPopulationSet (int subject, int target);
	
	/**
	*  move a particle from the intermediate set to the environment - copies content only, no particle deleted.
	* particle history and memory are not copied if present
	*/
	void moveParticleFromIntermediateToEnvironmentSet (int subject, int target);

	/**
	*  mop  file writer wrapper, using this means you don't need to supply the method parameters normally required.
	*/
	void writeCurrentStateToMopFile();
	/**
	*  Traverse the environment particle set and check for then apply any burns due at the state/step passed as parameters
	*/
	void processSpacecraft(int state, int step);

	/**
	* Record the state vectors of all particles in the environment population.
	* this can then be recalled to restore iterated particles to their initial starting velocity and position
	*/
	void recordCurrentStateVectorsForEnvironmentSet();

	/**
	* Revert  all particles in the environment population to previously stored state vectors.
	*/
	void ResetToRecordedStateVectorsForEnvironmentSet();

	/**
	* create a particle history for each particle in the environment set.
	*
	*/
	void createHistoryStorage(int frequency);

	/**
	* Record a history entry for each particle in the environment if it is time to do so.
	* For this to work it must be called once per step during the course of an experiment.
	* Also, it has to have been set up correctly, lest you over-run the array.
	*/
	void doHistory();
	/**
	* Reset the history for every particle in the environment set
	*/
	void resetHistory();

	/**
	* Delete the history for every particle in the environment set
	*/
	void deleteHistory();

	/**
	*  get the amount of the history array which is currently filled
	* Note: This will ONLY work if two conditions have been met
	* 1: That CabsuleBases doHistory is being used to record history for all particles
	* 2: That all particle histories have been set up with a call to CapsuleBases createHistoryStorage method
	*/
	const int getStoredHistoryCount();

	/**
	* Delete the history for every particle in the environment set
	*/
	void createMopFile(std::string location,std::string fn);			
};


/**
* This class represents a particle in Moody.
* Particles are responsible for their own movement, so contain internal integration methods.
* Particles can also be used as spacecraft and/or subjects of evolutionary computation experiments.
*/
class Particle {

public:
	Particle();
	~Particle();
	
	/**
	* turn this particle into a placemarker with no values
	*/
	void turnIntoPlacemarker ();

	/**
	* Make a placemark particle with the specified location (x,y,z) and colour (red,green,blue)
	*/
	void turnIntoPlacemarker(double x, double y, double z, int red, int green, int blue);

	/**
	* make a placemark particle with the same location and colour as an existing particle.
	*/
	void turnIntoPlacemarker(Particle &other);
	
	/**
	* copy the content of another particle into this one. Note that particle memory and history are never copied
	*/
	void fillFromExistingParticle (Particle & other);
	
	/**
	* equality check
	*/
	bool operator == ( const Particle & other);

	/**
	* inequality check
	*/
	bool operator  != ( const Particle & other);

	/**
	*  export as xml for use as part of a new particles.xml file.
	*  this differs from overloaded '<<', as it doesn't include the burn sequence managers content.
	*/
	std::string exportAsXMLForParticlesFile();

	/**
	*  reset so the particle begins at memory entry 0 again.
	* There is no need to actually empty the memory blocks
	*/
	void resetMemory();

	/**
	* get the name of this particle (a std::string)
	*/
	std::string getName();
	
	/**
	* get the mass of this particle
	*/
	double getMass();

	/**
	* get the BurnSequenceManager.
	* causes Moody to exit if you try to access a burn sequence manager for a particle
	* that is not set up as a spacecraft
	*/
	BurnSequenceManager & getBurnSequenceManager();

	/**
	* initialise the burn sequence manager
	*/
	void initialiseBurnSequenceManager(int num,int  maxBurns, int maxSequenceSize, int states, int numberOfStepsPerState);

	/**
	* rebuild the burn sequence timing tables for this particles burn sequence manager
	*/
	void rebuildBurnSequenceTimingTables(int steps);

	/**
	* make stored copies of spacecraft related members that will change when used and need to be reset
	*/
	void storeSpacecraftRelatedMembers();

	/**
	* restore spacecraft related members that have changed when used and need to be reset
	*/
	void restoreSpacecraftRelatedMembers();

	/**
	* set/update the score currently allocated to this particle
	*/
	void setScore(double score);
	
	/**
	* get the score currently allocated to this particle
	*/
	double getScore();

	/**
	* get whether or not this particle has been set up as a spacecraft
	*/
	bool getIsSpacecraft();

	/**
	*  fill all the private members of this particle using a particle structs content.
	* this option exists so a particles internal state can be extracted, changed and re-inserted.
	* It's not currently used, but may be useful for EA experiments
	*/
	void fillFromExistingParticleStruct(ParticleStruct & p);

	/**
	* create the block of memory this particle is going to use.
	* This needs to be done in advance, because creating memory storage
	* as needed is far too costly
	*/
	void createMemory( int size);
	
	/**
	*  get the number of vectors currently stored in memory
	*/
	int tellMeMemorySize();

	/**
	* set this particles position and/or velocity to be the first one stored in this particles memory
	*/
	void revertToFirstStoredVector( int option);

	/**
	* set this particles position and/or velocity to the indicated one stored in this particles memory
	*/
	void revertToVector( int index, int option);

	/**
	* set this particles position and/or velocity to the one most recently stored in this particles memory
	*/
	void revertToLastStoredVector( int option);

	/**
	* Euler method interaction between this particle and another
	*/
	void interactWithSpecified(Particle & that,  double G);

	/**
	* Euler method interaction between this particle and all others
	*/
	void interactWithAll(Particle * allParticles,  int numParticles,  double G,  int myIndex);

	/**
	* place the current private state of this particle into a particleStruct
	*/
	ParticleStruct exportContentAsParticleStruct();


	/**
	* place the current private state of this particle into a MopItem, ready to be recorded in a mop file
	* If all you want is a quick readout of a particles position and velocity, this is the best method to call.
	*/
	MopItem exportAsMopItem();

	/**
	*  find the distance between this particle and another
	*/
	double findDistance(Particle &that);

	/**
	*  store the current vector in memory.
	*  the particles block of memory must already have been assigned
	*/
	int addCurrentVectorToMemory();

	/**
	* Record the starting position of this particle, to be used for later resets
	*/
	void storeCurrentPosition();

	/**
	* Record the starting velocity of this particle, to be used for later resets
	*/
	void storeCurrentVelocity();

	/**
	* Record the starting velocity of this particle, to be used for later resets
	*/
	void storeCurrentStateVector();
	
	/**
	* Reset this particles position using previously stored values
	*/
	void resetToStoredPosition();
	
	/**
	* Reset this particles velocity using previously stored values
	*/
	void resetToStoredVelocity();
	
	/**
	* Reset this particles positon and velocity using previously stored values
	*/
	void resetToStoredStateVector();
	
	/**
	* inertia calculation
	*/
	void accountForInertia();

	/**
	* reset force accumulators. Not needed in integration, this exists for non integration based uses of Moody, such as gravitational mapping.
	*/
	void resetForceAccumulators();

	/**
	* Move a distance specified by using Eulers method.
	* The assumption here is that this will be used as part of a more complex integrator, not on its own.
	*/
	void moveParticle( int travelTime);

	/**
	* Performs the last stage of RK4 integration, producing the final position of the particle
	*/
	void finaliseStep( int travelTime);

	/**
	* During integration, the x/y/z values of a particle change. However, since the
	* state of a particle at the start of a first order move, at least in terms of position,
	* needs to be known by other particles that also want to move relative to it,
	* we need to make a copy of the starting position that the other particles can read.
	*/
	void setExternalReferenceVector();

	/**
	* kick this particles velocity using the existing force
	*/
	void kick_noforceCalc(int stepsize);

	/**
	* Symplectic method - drifts this particle across a step
	*/
	void drift (int stepsize);

	/**
	* Convert available fuel to thrust using this particles specific impulse value
	* This method impements Konstantin Tsiolkovsky's rocket equation
	* The result is correct for field free space.
	* FuelMass is the mass that will be removed as a result of this burn.
	* that mass is not removed by this method.
	*/
	double convertFuelToThrust (double fuelMass);

	/**
	*  set up this particle as a spacecraft, fuel structure and paylod must equal unity
	*/
	void makeSpacecraft (SpacecraftInitialiser sci);

	/**
	* Apply a burn event
	* If there was no burn event due can be found by the burn sequence manager but this was called, the BurnEventFire object used will be zero filled and do nothing.
	*/
	void ExecuteBurn (int sequence, int state, int step);

	/**
	* Place this particle in a random orbital location around another particle
	*/
	void generateOrbitalPosition(Particle * allParticles, int numParticles, int focusParticle, double altitude, bool equaliseVelocities,bool addEscapeVelocity, double escapeVelocity);

	/**
	* This does the same as generateOrbitalPosition, but does not touch velocity
	*/
	void placeParticleRandomlyOnSphere(Particle * allParticles, int numParticles, int focusParticle, double altitude);

	/**
	*  mutation operator - assuming this particle has been placed on the surface of a sphere, alter the angles by some small random amount and recalculate position. Does not alter velocity/direction of travel. Must already have been placed on a sphere
	* parameters:
	* the central point of the sphere as x,y,z
	* radius of the sphere
	*/	

	void  mutatePositionOnSphere(double radius);

	/**
	*  mutation operator (second version) - assuming this particle has been placed on the surface of a sphere, alter the angles by some small random amount and recalculate position. Does not alter velocity/direction of travel. Must already have been placed on a sphere
	* parameters:
	* the environment Set
	* the index of the particle this is to be centred on
	* radius of the sphere
	*/	
	void mutatePositionOnSphere(Particle *allParticles,int focusParticle,double radius);

	/**
	*  mutation operator - assuming this particle has been placed on the surface of a sphere, such as is done in 
	* the method generateOrbitalPosition, alter the angles by some small random amount, recalculate position and direction of travel.
	* parameters:
	* the central point of the sphere as x,y,z
	* radius of the sphere
	* true will cause the direction of travel to be altered as well, false will just move the particle
	* if velocity is to be altered,  baseXd and such are used to provide an initial velocity to which the angled changes will be appended
	*/	
	void mutatePositionAndVelocityOnSphere(double x, double y, double z, double radius, double velocity, double baseXd, double baseYd, double baseZd);

	/**
	*  mutation operator - mutate location for this particle
	*/
	void mutateLocation() ;

	/**
	*  mutation operator - mutate velocity for this particle
	*/
	void mutateVelocity();

	/**
	*  mutation operator - mutate mass for this particle. Note that this mutation is
	* only really effective when a particle is set up as a spacecraft, whereby mass effects the rocketry aspect
	*/
	void mutateMass();

	/**
	*  mutation operator - mutate fuel percentage for this particle
	* has no effect if this particle isn't set up as a spacecraft
	* changes to fuel mass are taken from or given to payload
	*/
	void mutateFuelPercentage();

	/**
	*  mutation operator - mutate payload for this particle
	* has no effect if this particle isn't set up as a spacecraft
	* changes to payload mass are taken from or given to fuel
	*/
	void mutatePayloadPercentage();

	/**
	*  mutation operator - mutate structural mass (what's left after payload and fuel mass)  for this particle
	* has no effect if this particle isn't set up as a spacecraft.
	* changes are taken from or given to fuel and payload mass equally
	*/
	void mutateStructurePercentage();

	/**
	* reset this particle history array ready for reuse. Does not resize history
	*/
	void resetHistory();

	/**
	* delete this particle's history array completelly. Use this if you want to de-allocate the history array,  and use resetHistory if you just want to clear it.
	*/
	void deleteHistory();
	
	/**
	* store the current state vector in this particles history. All storage attempts once the history is filled are ignored
	*/
	void AddCurrentStateVectorToHistory();

	/**
	* store the current state vector in this particles history. All storage attempts once the history is filled are ignored
	* parameters are the number of states, the number of states per step, and the number of times per state you want to 
	* record a history entry.
	* Unless you are planning to record the histories of a select few particles, 
	* call createHistoryStorage() in Capsule, which will build history storage for
	* all particles in the environment set
	*/
	void createHistory(int states, int steps, int frequency);

	/**
	* record a history entry if it's time to do so. For this to work it has to be called once for every step of an iterating model
	* unless you are specifically recording the history of a select set of particles, you should use the doHistory() implemented in
	* Capsule (well, CapSuleBase), which calls this for all particles in the environment set.
	*/
	void doHistory();

	/**
	*  get one entry of this particles history
	*/
	ParticleHistory & getHistoryEntry(int index);

	/**
	*  get the overall size of history array
	*/
	const int getHistoryStorageArraySize();

	/**
	*  get the amount of the history array which is currently filled
	*/
	const int getStoredHistoryCount();

	/**
	*  This is the kick operation used in symplectic integration
	*/
	void kick(Particle * allParticles,const int numParticles, const double G, const int myIndex, int stepsize);

};


/**
* This struct is used when manipulating/initialising the contents of a particle
*/
struct ParticleStruct {
  
	/**
	* this particles mass
	*/
	double mass;

	/**
	* stored copy of this particles mass
	*/
	double stored_mass;

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
	double xd;

	/**
	* The velocity of this particle along the Y axis
	*/
	double yd;

	/**
	* The velocity of this particle along the Z axis
	*/
	double zd;

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
	double stored_xd;

	/**
	* The stored initial velocity of this particle along the Y axis
	*/
	double stored_yd;

	/**
	* The stored initial velocity of this particle along the Z axis
	*/
	double stored_zd;

	/**
	* the red portion of this particles colour
	*/
	int red;

	/**
	* the green portion of this particles colour
	*/
	int green;

	/**
	* the blue portion of this particles colour
	*/
	int blue;

	/**
	* the std::string name of this particle
	*/
	std::string name;

	/**
	*  What types of particle this particle is allowed to interact with.
	*/
	int interactionPermission;

	/**
	* what type this particle is - (collapsor/normal particle/placemark/spacecraft)
	*/
	int identity;

	/**
	*  what size this particle will have when displayed in a visualisation
	*/
	int visualRepresentation;

	/**
	* the current score of this particle (when an EA is being performed)
	*/
	double score;

	/**
	* determines whether this particle is set up to be a spacecraft or not
	*/
	bool isSpacecraft;

	/**
	* tells us whether the spacecraft burn sequence manager has been allocated
	*/
	bool burnsManagerActive;

	/**
	* the percentage of this particles total mass that is structural content
	*/
	double structurePercentage;

	/**
	* the percentage of this particles total mass that is payload content
	*/
	double payloadPercentage;

	/**
	* the percentage of this particles total mass that is fuel content
	*/
	double fuelPercentage;

	/**
	* the specific impulse value in use
	*/
	double specificImpulse;

	/**
	* the percentage of this particles total mass that is structural content
	*/
	double stored_structurePercentage;

	/**
	* the percentage of this particles total mass that is payload content
	*/
	double stored_payloadPercentage;

	/**
	* the percentage of this particles total mass that is fuel content
	*/
	double stored_fuelPercentage;

	/**
	* the specific impulse value in use
	*/
	double stored_specificImpulse;

	/**
	* rotation variable storage (used when placing/moving particles on the surface of a sphere)
	*/
	double curlyThing;

	/**
	* other rotation variable storage (used when placing/moving particles on the surface of a sphere)
	*/
	double theta;	
};


/**
* This struct is used when a particle is being turned into a spacecraft
*/
struct SpacecraftInitialiser {
	/**
	* the name for this spacecraft
	*/
	std::string name;

	/**
	* this spacecrafts mass
	*/
	double mass;

	/**
	* the percentage of this particles total mass that will be structural content
	*/
	double structurePercentage;

	/**
	* the percentage of this particles total mass that will be payload content
	*/
	double payloadPercentage;

	/**
	* the percentage of this particles total mass that will be fuel content
	*/
	double fuelPercentage;

	/**
	* the specific impulse to be used by this spacecraft
	*/
	double specificImpulse;

	/**
	* the radius for this spacecraft
	*/
	double radius;

	/**
	* the red portion of this spacecrafts colour
	*/
	int red;

	/**
	* the greem portion of this spacecrafts colour
	*/
	int green;

	/**
	* the blue portion of this spacecrafts colour
	*/
	int blue;

	/**
	*  What types of particle this particle is allowed to interact with.
	*/
	int interactionPermission;

	/**
	* what type this particle is - most likely 'spacecraft'
	*/
	int identity;

	/**
	*  what size this particle will have when displayed in a visualisation
	*/
	int visualRepresentation;
};

/**
* This class is used to hold the result of a call to BurnSequenceManager::findSequenceNeighbors
*/
class SequenceSearch
{
public:
	int subjectStartingState;
	int subjectEndingState;
	int subjectStartingStep;
	int subjectEndingStep;
	int preceedingStartingState;
	int preceedingEndingState;
	int preceedingStartingStep;
	int preceedingEndingStep;
	int preceedingDistance;
	int followingStartingState;
	int followingEndingState;
	int followingStartingStep;
	int followingEndingStep;
	int followingDistance;
	int subjectIndex;
	int preceedingIndex;
	int followingIndex;
	int stepsBefore;
	int stepsAfter;
	SequenceSearch(void);
	~SequenceSearch(void);
};


/**
* This class represents a single burn for a spacecraft particle
*/
class BurnEventFire {
public:
	BurnEventFire(void);

	/**
	*  the amount of fuel to be used in this burn, expressed as a percentage of the fuel available to the parent sequence
	*/
	double fuelPct;

	/**
	* positive thrust percentage for the X axis
	*/
	double xPlus;

	/**
	* negative thrust percentage for the X axis
	*/
	double xMinus;

	/**
	* positive thrust percentage for the Y axis
	*/
	double yPlus;

	/**
	* negative thrust percentage for the Y axis
	*/
	double yMinus;

	/**
	* positive thrust percentage for the Z axis
	*/
	double zPlus;

	/**
	* negative thrust percentage for the Z axis
	*/
	double zMinus;
};

#pragma once
#include "../../etc/Numerics.h"
/**
* This represents a single burn for a spacecraft particle
* This class only has public members, since member values are all accessed and changed
* externally, but has methods to perform mutations
*/
class BurnEvent {
public:
	BurnEvent(void);
	
	/**
	* copy constructor
	*/
	BurnEvent(const BurnEvent& bs);

	/**
	* replace the contents of this BurnEvent with that of another
	*/
	void fillFromExistingBurnEvent (const BurnEvent & other);
	
	/**
	* equality operator
	*/
	bool operator == (const BurnEvent & other);
	
	/**
	* inequality operator
	*/
	bool operator  != (const BurnEvent & other);

	/**
	* when in the time span occupied by the parent sequence will this burn event occur.
	*  The burn point is expressed as a percentage of the time span occupied by the parent sequence
	*/
	double positionPct;

	/**
	*  the state in which this burn is to be used (calculated dynamically, do not set directly)
	*/
	int stateUsed;

	/**
	*  the step on which this burn is to be used (calculated dynamically, do not set directly)
	*/
	int stepUsed;

	/**
	*  the amount of fuel to be used in this burn, expressed as a percentage of the fuel available to the parent sequence
	*/
	double fuelPct;

	/**
	* positive thrust percentage for the X axis
	*/
	double xPlus;

	/**
	* negative thrust percentage for the X axis
	*/
	double xMinus;

	/**
	* positive thrust percentage for the Y axis
	*/
	double yPlus;

	/**
	* negative thrust percentage for the Y axis
	*/
	double yMinus;

	/**
	* positive thrust percentage for the Z axis
	*/
	double zPlus;

	/**
	* negative thrust percentage for the Z axis
	*/
	double zMinus;

	/**
	* Mathematical functions and operations
	*/
	Numerics maths;

	/**
	* mutate burn fuel allocation percentages by swapping allocations around.
	* the number of swaps to perform is set in the parameter 'swaps'
	*/
	void mutateFuelAllocationsBySwapping(int swaps);

	/**
	* mutate burn event fuel allocation
	*/
	void mutateBurnEventFuelAxisAllocation();
};

/**
* This class is used to form the lookup table which is consulted to see whether the
* BurnSequence to which this lookup table belongs needs to fire a burn event at the current state/step
*/
class BurnLookup {
public:
	BurnLookup(void);

	/**
	* copy constructor
	*/
	BurnLookup(const BurnLookup& bl);

	/**
	* replace the contents of this BurnLookup with that of another
	*/
	void fillFromExistingBurnLookup (const BurnLookup & other);

	/**
	* equality operator
	*/
	bool operator == (const BurnLookup & other);

	/**
	* inequality operator
	*/	
	bool operator  != (const BurnLookup & other);

	/**
	*export the contents of this BurnLookup to an xml string
	*/
	std::string exportAsXML ();

	/**
	* In which state is this burn set to occur
	*/
	int state;

	/**
	* On which step is this burn set to occur
	*/
	int step;
};


/**
* This class manages a sequence of BurnEvents
*/
class BurnSequence
{

public:

	BurnSequence(void);

	~BurnSequence(void);

	/**
	* copy constructor
	*/
	BurnSequence( const BurnSequence& bs);

	/**
	* replace the contents of this BurnSequence with that of another
	*/
	void fillFromExistingBurnSequence ( const BurnSequence & other);

	/**
	* get the number of burns in this sequence
	*/
	int getBurnCount();
	
	/**
	* get a pointer to a given burn in the burn sequence
	*/
	BurnEvent & getBurn(int index);

	/**
	* set the active period of this sequence
	* note that this should not be called unless you have already verified that the timing
	* provided will not overlap with another.
	*/
	void prepareSequenceActivePeriod(int numberOfStepsPerState, int startState, int endState, int startStep, int endStep);

	/**
	* get the total time in simple steps of this sequence
	*/
	int getActivePeriodAsSteps();

	/**
	* get the state on which this burn sequence starts
	*/
	int getStartState();

	/**
	*  get the state in which this burn sequence ends
	*/
	int getEndState();

	/**
	* get the step on which this burn sequence starts
	*/
	int getStartStep();

	/**
	* get the step on which this burn sequence ends
	*/
	int getEndStep();

	/**
	* get the percentage of the available fuel which this burn sequences uses
	*/
	double getFuelPct();

	/**
	* set the percentage of the available fuel which this burn sequences uses
	*/
	void setFuelPct( double fuelPct);
	
	/**
	* set the state in which this burn sequence starts
	*/
	void setStartState( int startState);

	/**
	* set the state in which this burn sequence ends
	*/
	void setEndState( int endState) ;

	/**
	* set the step on which this burn sequence starts
	*/
	void setStartStep( int startStep);

	/**
	* set the step on which this burn sequence ends
	*/
	void setEndStep( int endStep);

	/**
	* add a new burn event to this burn sequence using a prepared BurnEvent
	*/
	void addBurnEvent (BurnEvent &b);

	/**
	* remove a burn event
	*/
	void deleteBurnEvent ( int index);

	/**
	* add a burn event to the fast access burn lookup table
	*/
	void addToBurnLookupTable (int state, int step);

	/**
	* burn lookup table sort. Uses insertion sort because the list will usually be mostly sorted.
	* Sorts first by state, then again by steps within each state
	* (unfinished method, do not use)
	*/
	void sortBurnLookupTable ();

	/**
	* remove a burn event from the lookup table
	*/
	void deleteFromBurnLookupTable ( int index);

	/**
	* remove the last burn event from the lookup table
	*/
	void deleteTopFromBurnLookupTable ();

	/**
	* rebuild the burn lookup table after a change to the burn sequence timing
	*/
	void rebuildBurnLookupTable ();

	/**
	* calculate burn sequence span and apply exact timings to owned burn sequences based on their positionPct values.
	*/
	void calculateBurnSequenceTiming(int numberOfStepsPerState);
	/**
	* quick check to see whether a burn from this sequence needs to be applied on this state/step
	*/
	int checkBurnTable(int state, int step);

	/**
	* make a random burn event (does not calculate this burns fuel percentage allocation)
	*/
	BurnEvent createRandomBurnEvent();

	/**
	*  set up the fuel percentages for the individual burns
	*/
	void allocateFuelToBurns();

	/**
	* Retreive a single burn event from those stored so it can be used.
	*/
	BurnEventFire fetchBurnEvent(int index);

	/**
	* build a new random burn sequence of size, um, size...
	* we don't set it's fuel percentage, active period or burn timing here, although we do set the
	* fuel percentages for its individual burns, since those are all relative to the
	* values the burn sequence will be given later by the BurnSequenceManager
	*/
	void createBurnSequence(int size);

	/**
	* mutate burn event position in the burn sequence (time of firing)
	* burn sequence timing is recalculated, so this is an expensive mutation
	*/
	void mutateBurnEventPosition(int index, int numberOfStepsPerState);
	/**
	* mutate burn fuel allocation percentages for this sequence by taking from one and giving to another.
	*/
	void mutateFuelAllocations();

	/**
	* mutate a single BurnEvents thrust allocation
	*/
	void mutateRandomBurnEventThrust();

	/**
	* mutate a single BurnEvents fuel allocation percentages by swapping allocations around.
	* the number of swaps to perform is set in the parameter 'swaps'
	*/
	void mutateFuelAllocationsBySwapping(int swaps);
};

/**
* this class manages the burn sequences stored for a particle
*/
class BurnSequenceManager
{
public:

	BurnSequenceManager(void);

	~BurnSequenceManager(void);
	
	/**
	* copy constructor
	*/
	BurnSequenceManager( const BurnSequenceManager& bsm);
	
	/**
	* replace the contents of this BurnSequenceManager with that of another
	*/
	void fillFromExistingBurnSequenceManager (BurnSequenceManager & other);

	/**
	* get the burn sequence specified by index
	*/
	BurnSequence &getBurnSequence(int index);

	/**
	* empty this burn sequence manager, deleting the array of stored burn sequences
	*/
	void clear();

	/**
	* get the number of burn sequences stored by this manager
	*/
	int getSequenceCount();

	/**
	* add a new BurnSequence to this burn sequenceSet
	*/
	void addBurnSequence (BurnSequence &b);

	/**
	* remove a burn sequence
	*/
	void deleteBurnSequence ( int index);

	/**
	*  create all burn sequences, assigning timing and fuel allocation.
	* The maximum initial size of a burn sequence is specified in terms of steps.
	* These can be <> the size of one or more states.
	* We also need to provide the number of states used for the entire experiment run, and the steps in a state for timing to be worked out.
	* For the sequence timings to be valid they must not overlap. If this is too restrictive, reduce state length.
	*/
	void buildBurnSequences(int num,int  maxBurns, int maxSequenceSize, int states, int numberOfStepsPerState);

	/**
	*  rebuild all burn sequence timing tables
	*/
	void rebuildBurnSequenceTimingTables(int steps);

	/**
	* Check to see whether one of the burn sequences needs to fire a burn at this point (state/step)
	* return -1 if no burn is due or the index of the burn sequence that contains the
	* burn to fire
	*/
	int scanBurnTables(int state, int step);

	/**
	* Fetch a burn event from the sequence indicated by index that the timing tables indicate is now due
	* Not this will only work if there actually is a burn event due at the current state and step.
	* establish whether there is with a call to scanBurnTables first, which will return the correct sequence index.
	* Note that once retreived by this method a burn event is considered to have been used/fired, and will no longer be available.
	* If all you want to do is read/alter a burn event, use the BurnSequence::getBurn() method
	*/
	BurnEventFire getCurrentBurnEvent(int sequence, int state, int step);

	/**
	* mutate burn event position for a randomly selected sequence burn sequence (time of firing)
	* burn sequence timing is recalculated, so this is an expensive mutation
	* this is a wrapper for a mutation operator that belongs to the sequence being mutated
	*/
	void mutateSingleBurnEventPosition(int steps);
	
	/**
	* mutate burn event thrust allocation for a single burn of a randomly selected sequence.
	* this is a wrapper for a mutation operator that belongs to the sequence being mutated
	*/
	void mutateSingleBurnEventThrust();

	/**
	* mutate burn fuel allocation percentages for burns in a randomly selected sequence by taking from one and giving to another.
	* this is a wrapper for a mutation operator that belongs to the sequence being mutated
	*/
	void mutateFuelAllocationForBurnsInSingleSequence();
	
	/**
	* mutate burn fuel allocation percentages for a randomly selected sequence by swapping allocations between burns.
	* the number of swaps to perform is set in the parameter 'swaps'.
	* this is a wrapper for a mutation operator that belongs to the sequence being mutated
	*/
	void mutateRandomBurnFuelAllocationsBySwapping(int swaps);

	/**
	* swap the fuel allocations of two sequences
	*/
	void mutateSwapSequenceFuelAllocations();

	/**
	* mutate the fuel allocations of two sequences, taking from one and giving to another
	*/
	void mutateSequenceFuelAllocations();
	
	/**
	* swap the positioning of two sequences, how many times to do this is determined by the parameter 'swaps'
	* This is done by the burn sequence manager, not the burn sequences involved, because it requires
	* knowledge of the set of sequences that a single sequence couldn't have
	* the burn timings of each sequence are recalculated after the swap is complete
	*/
	void mutateSequencesBySwappingPosition(int swaps, int numberOfStepsPerState);

	/**
	* mutate the positioning of a randomly selected sequence (you cannot control which sequence this is).
	* limits: The sequence can only either shrink or grow or move in a manner which does not stray 
	* into the period occupied by another existing sequence.
	* parameter is the number of steps there are in a state.
	* This is done by the burn sequence manager, not the burn sequences involved, because it requires
	* knowledge of the set of sequences that a single sequence couldn't have.
	* the burn timings of the subject sequence is recalculated after the resize or move is complete
	*/
	void mutateSequenceByChangingTiming( int numberOfStates, int numberOfStepsPerState);
};


/**
* A memory entry for a particle
*/
class MemoryEntry
{
public:
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
	double xd;

	/**
	* The velocity of this particle along the Y axis
	*/
	double yd;

	/**
	* The velocity of this particle along the Z axis
	*/
	double zd;

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
	*  is the content of this memory block valid? (memory resets do not actually empty memory blocks, that's a waste of time)
	*/
	bool exists;
	
	MemoryEntry(void);

	~MemoryEntry(void);
};

/**
* This struct is used to hold the entire memory content of a particle when it is extracted
*/
struct MemoryContent {
	/**
	* the current size of memory
	*/
	int memorySize;
	/**
	* the memory block itself
	*/
	MemoryEntry *content;
};



/**
* This class holds a single entry in a particles history
* history means the positions and velocities recorded for a particle during a given run
*/
class ParticleHistory {
public:
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
	double xd;

	/**
	* The velocity of this particle along the Y axis
	*/
	double yd;

	/**
	* The velocity of this particle along the Z axis
	*/
	double zd;

	/**
	* clear this memory entry's content
	*/
	void blank();
};


/**
* This class is used to store a single state, containing many MopItems, for writing to, or when read from, a MOP file.
*/
class MopState {

public:
	MopState();
	~MopState();
	
	/**
	* copy constructor
	*/
	MopState(const MopState& bs);
	
	/**
	* returns the entire array of MopItems stored
	*/
	MopItem *getContent() const;

	/**
	* returns the specified MopItem
	*/
	MopItem getMopItem(int x) const;

	/**
	* returns the number of MopItems stored
	*/	
	int getItemCount() const;
	
	/**
	* add a new MopItem
	*/
	void addMopItem(MopItem current);
};

/**
* This class is used to store a single MOP file entry, which represents the state of a particle
*/
class MopItem
{
public:
	MopItem();
	~MopItem();
	
	/**
	* copy constructor
	*/	
	MopItem(const MopItem& mi);
	
	/**
	* replace the contents of this MopItem with that of another
	*/
	void fillFromExistingMopItem(const MopItem & other);

	double mass;
	double radius;
	double x;
	double y;
	double z;
	double xd;
	double yd;
	double zd;
	int red;
	int green;
	int blue;
	char name[50];   
    std::string nameToStdString();
	int interactionPermission;
	int identity;  
	int visualRepresentation; 
};

/*
*This class manages the MOP files used by Moody to store time series data
*/
class MopFile {


public:
	MopFile();
	~MopFile();
	/**
	* retrieve the filename
	*/
	std::string getFilename() ;

	/**
	* set the filename to be used, with path specified seperatelly
	*/
	void setFilename(std::string path,std::string fn);

	/**
	* set the filename to be used including path
	*/
	void setFilename (std::string fn);

	/**
	* write the current state to the mop file
	*/
	void writeState(Particle * localSet, int environmentSetSize);


	/**
	* open the mop file for reading
	*/
	void openMopfileReader();

	/**
	* reset the mop file
	*/
	void resetFile();

	/**
	* read a single state from the mop file
	*/
	MopState * readState();
    /**
	* read a single state from the mop file, clycling back to the start of the file 
    * if the end is reached
	*/
	MopState * readCyclingState();
};


/**
* Simple timing class. Doesn't work properly on true SMP machines
*/
class Timing
{
public:

	Timing(void);

	~Timing(void);
	
	/**
	* start the clock
	*/
	void start();
	
	/**
	* stop the clock and send time taken to std::out
	*/
	void stop();
};


/**
* This class contains numeric methods and defines
*/
class Numerics
{
public:

	#define PI 3.141592653589793

	#define AU 1.49598E+11
	
	/**
	* rounding method
	*/
	int round(double x);

	/**
	* sqr method
	*/
	double sqr(double x);
	
	/**
	* Measure the distance between two bodies in 3d space.
	*/
	double calculateDistance(const double & m1x, const double & m1y, const double & m1z, const double & m2x, const double & m2y, const double & m2z);
	
	/**
	* generate a random number within the given range (double)
	*/
	double randomRange(const double low, const double high);

	/**
	* generate a random number within the given range (int)
	*/
	int randomRangeInt( const int low,  const int high);
	
	/**
	*  generate a gaussian random number
	*/
	double generateGaussian (void);

	/**
	*  unipolar sigmoid function
	*/
	double sigmoid(float x);

	/**
	* check to see whether a provided value is within a specified range - integer version
	*/
	bool isValueWithinRange( const int value, const int lower, const int upper);
	
	/**
	* check to see whether a provided value is within a specified range - doubles version
	*/
	bool isValueWithinRange( const double value, const double lower, const double upper);

	/**
	* Converts a double value to a string
	*/
	std::string doubleToString( const double val);

	/**
	* Converts an integer value to a string
	*/
	std::string intToString(int val);
};

/**
* Very simple annealer for use in Stochastic Hill Climbing. Provides a simple linear rate of cooling.
* To use, initialise before beginning the iterations of the hill climber, then make one call to reduce()
* once for every subsequent iteration. If an annealing jump is produced reduce() will return true, if not, it
* will return false;
*/
class Annealer
{


public:

	Annealer(void);

	virtual ~Annealer(void);
		
	/**
	* initialise the annealer.
	* totalTime is the runtime of your experiment, haltingPct allows you to set a point other than the end of the
	* total runtime at which the annealer should terminate
	*/
	void initialise(int totalTime, double haltingPct = 0 );

	/**
	* call this method on each iteration of your experiment. It returns true if an annealing jump is allowed
	* or false otherwise
	*/
	bool reduce();
};


/**
* This class contains static const members that are used to control behaviours in Moody
*/
class Advisor {
public:

	/**
	* Particle interaction setting - Setting for all normal particles (planets and such) - interact with all particles, including special ones, except for placemarks
	*/
	static const int interactALL = 1;

	/**
	* Particle interaction setting - Only interact with ordinary particles and collapsors (would be used for spacecraft)
	*/
	static const int interactEnvironmentOnly = 2;

	/**
	* Particle interaction setting - Setting to be used if the particle is not to interact with any other particles (acting as a fixed placemark)
	*/
	static const int interactNONE = 3;

	/**
	* Particle interaction setting - Setting to be used if the particle is not to interact with other particles of the same type (asteroids, spacecraft, things like that)
	*/
	static const int interactDifferentOnly = 4;

	/**
	* Particle interaction setting - This particle is acting as a collapsor
	*/
	static const int collapsor = 103;

	/**
	* Particle interaction setting - This particle is acting as a collapsor, and isn't being allowed to move
	*/
	static const int collapsorFixed = 104;

	/**
	* Particle interaction setting -  A placemark particle, not to be subject to movement at all
	*/
	static const int nonInteractive = 105;

	/**
	* Particle identity setting -  A Particle that needs no special treatment
	*/
	static const int ordinary = 106;

	/**
	* Particle identity setting -  this particle is a very small body, so small that it needn't be made to interact with others of the same type.
	*/
	static const int planetesimal = 108;
	/**
	* Particle identity setting -  this particle is an EA experiment chromosome
	*/
	static const int chromosome = 109;

	/**
	* Particle memory handling constants - retreive all stored data
	*/
	static const int ALL = 400;

	/**
	* Particle memory handling constants - retreive all stored data except for forces
	*/
	static const int OMIT_FORCES = 401;

	/**
	* Particle memory handling constants - retreive all stored data except for position
	*/
	static const int OMIT_VECTOR = 402;

	/**
	* tournament selection - lowest score required
	*/
	static const int LOWEST = 701;
	/**
	* tournament selection - highest score required
	*/
	static const int HIGHEST = 702;

	/**
	* sequence selected is first sequence (used during sequence mutation bounds checking)
	*/
	static const int Before_First_Sequence = -801;
	/**
	* sequence selected is last sequence (used during sequence mutation bounds checking)
	*/
	static const int After_Last_Sequence = -802;
};

