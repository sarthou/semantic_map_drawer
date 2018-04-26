#ifndef MAPREADER_H
#define MAPREADER_H

#include <string>
#include <vector>
#include <map>

#include "ros/ros.h"
#include "route_drawer/OntologyManipulator.h"

struct corridor_t
{
  std::string name_;
  std::vector<std::string> at_right_;
  std::vector<std::string> at_left_;
  std::vector<std::string> at_begin_edge_;
  std::vector<std::string> at_end_edge_;
  std::map<std::string, std::string> in_front_of_;
};

class MapReader
{
public:
  MapReader(ros::NodeHandle* n) : onto_(n) { n_ = n; }
  ~MapReader() {}

  void getMap();

  std::vector<corridor_t> corridors() {return corridors_; }

private:
  ros::NodeHandle* n_;
  OntologyManipulator onto_;

  std::vector<corridor_t> corridors_;

  void getCorridors();
  void getInFrontOf(corridor_t& corridor);
  void getSides(corridor_t& corridor);
  std::vector<std::string> getSide(std::string corridor, std::string property);
  std::vector<std::string> orderPlaces(std::vector<std::string> base, bool inverse);

  void displayCorridor(corridor_t corridor);
  void displaySide(std::vector<std::string> side, std::string name);
};

#endif
