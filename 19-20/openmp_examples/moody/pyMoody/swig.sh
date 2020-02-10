echo "Running swig command to add python support to Moody"
swig -c++ -python  -o moody_interface.cpp pyMoodyInterface.i
echo "swig command executed, if no errors were reported you can now compile moody with 'make pyMoody'"

