#ifndef ONTOLOGYMANIPULATOR_H
#define ONTOLOGYMANIPULATOR_H

#include "ros/ros.h"

#include <vector>
#include <string>

class OntologyManipulator
{
public:
  OntologyManipulator(ros::NodeHandle* n) {n_ = n; cpt = 0;}
  ~OntologyManipulator() {}

  std::vector<std::string> string2vector(const std::string& value);

  std::string getOn(const std::string& name, const std::string& property);
  std::string getFrom(const std::string& property, const std::string& name, const std::string& selector = "");
  std::string getWith(const std::string& indiv_1, const std::string& indiv_2, const std::string& selector = "");
  std::string getUp(std::string& name, const std::string& selector = "");
  bool isA(std::string& name, const std::string& base_class);
  std::string getDown(std::string& name);
  std::string getRelatedFrom(const std::string& name);
  std::string getType(const std::string& name);

  size_t nb() {return cpt;}
  void reset() {cpt = 0;}

  bool close();

private:
  ros::NodeHandle* n_;
  size_t cpt;
};

#endif
