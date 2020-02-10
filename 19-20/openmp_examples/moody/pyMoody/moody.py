#! /usr/bin/env python
import pyMoody
import sys
print "> pyMoody example - Dr Carey Pridgeon 2011"
argc = len(sys.argv)
if argc!=3:
    print "> Error: Incorrect number of parameters."
    print "> Usage: moody <integrator> <projectfolder>"
    print ">      : Where the integrator is either rk4 (Runge-kutta), mp (Midpoint), or sym (2nd order symplectic),"
    print ">      : and projectfolder is the location of the project folder itself,"
    print ">      : i.e python moody.py sym ../ReferenceProject"
    sys.exit()
experiment = pyMoody.Capsule()
experiment.loadProject(sys.argv[2])
integrator = sys.argv[1]
print "> Project contains "+repr(experiment.getEnvironmentSetSize())+" particles."
print "> Number of States Specified           : "+repr(experiment.getNumStates())
print "> Number of Steps per State            : "+repr(experiment.getNumSteps())
print "> Stepsize                             : "+repr(experiment.getStepSize())
print "> Gravitational Constant in use : "+repr(experiment.getGravitationalConstant())
experiment.createMopFile(experiment.getResultFolder(),experiment.getMopName())
print "> Starting.."   

if integrator=="rk4":
    print "> Integrator Selected: 4th Order Runge-Kutta."
    print "> Starting.."
    experiment.createParticleMemory(4)
    for i in range(0, experiment.getNumStates()):
        for j in range(0, experiment.getNumSteps()):
            experiment.iterateRK4()	
        print "> State "+repr(i)+" of "+repr(experiment.getNumStates())+" Completed"
        experiment.writeCurrentStateToMopFile()
elif integrator =="mp": 
    print "> Integrator Selected: 2nd Order Midpoint."
    print "> Starting.."
    for i in range(0, experiment.getNumStates()):
        for j in range(0, experiment.getNumSteps()):
            experiment.iterateMidPoint()	
        print "> State "+repr(i)+" of "+repr(experiment.getNumStates())+" Completed"
        experiment.writeCurrentStateToMopFile()
elif integrator=="sym":
    print "> Integrator Selected: 2nd Order Symplectic."
    print "> Starting.."
    for i in range(0, experiment.getNumStates()):
        for j in range(0, experiment.getNumSteps()):
            experiment.iterateSym()
        print "> State "+repr(i)+" of "+repr(experiment.getNumStates())+" Completed"
        experiment.writeCurrentStateToMopFile()
print "> Finished"
