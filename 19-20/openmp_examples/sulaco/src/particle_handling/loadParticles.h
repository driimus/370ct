#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <fstream>
#include <memory>
#include "../rapidxml/rapidxml.hpp"
#include "particleArrayHandling.h"


/**
 * load in the settings for the project into an instance of the settings type.
 */
particleStore  * loadParticles(path in){
  particleStore * tmp = new particleStore;
  tmp->size = 0;

  using namespace rapidxml;
  particle p;
xml_document<> doc;
 xml_node<> *pNode;
 xml_node<> *pRoot;
std::ifstream file(in.projectParticlesPath);
std::stringstream buffer;
buffer << file.rdbuf();
file.close();
std::string content(buffer.str());
doc.parse<0>(&content[0]);
//get the root node
 pRoot = doc.first_node();
// Interate over the particles
 xml_node<> *particle_node;
  for(particle_node = pRoot->first_node("particle"); particle_node; particle_node = particle_node->next_sibling())  {
    pNode = particle_node->first_node("type");
    p.name = atoi(pNode->value());
    pNode = particle_node->first_node("name");
    p.name = pNode->value();
    pNode = particle_node->first_node("id");
    p.id = atoi(pNode->value());
    pNode = particle_node->first_node("mass");
    p.mass = atof(pNode->value());
    pNode = particle_node->first_node("type");
    p.type = atoi(pNode->value());
    pNode = particle_node->first_node("radius");
    p.radius = atof(pNode->value());
    pNode = particle_node->first_node("rgb")->first_node("red");
    p.r = atoi(pNode->value());
    pNode = particle_node->first_node("rgb")->first_node("green");
    p.g = atoi(pNode->value());
    pNode = particle_node->first_node("rgb")->first_node("blue");
    p.b = atoi(pNode->value());
    pNode = particle_node->first_node("vector")->first_node("X");
    p.x = atof(pNode->value());
    pNode = particle_node->first_node("vector")->first_node("Y");
    p.y = atof(pNode->value());
    pNode = particle_node->first_node("vector")->first_node("Z");
    p.z = atof(pNode->value());
    pNode = particle_node->first_node("vector")->first_node("XV");
    p.xv = atof(pNode->value());
    pNode = particle_node->first_node("vector")->first_node("YV");
    p.yv = atof(pNode->value());
    pNode = particle_node->first_node("vector")->first_node("ZV");
    p.zv = atof(pNode->value());
    addToParticleSet (tmp,p);
   }
return  tmp;

}
