#include <iostream>
#include "ros/ros.h"

#include <vector>
#include <string>

#include "route_drawer/MapReader.h"
#include "route_drawer/MapDrawer.h"

ros::NodeHandle* n_;


int main(int argc, char** argv)
{
  ros::init(argc, argv, "semantic_route_drawer");

  ros::NodeHandle n;
  n_ = &n;

  ros::service::waitForService("ontoloGenius/arguer", -1);

  ROS_DEBUG("semantic_route_drawer ready");

  MapReader reader(&n);
  reader.getMap();
  MapDrawer drawer(&n);
  drawer.draw(reader.corridors());
  drawer.draw(reader.openspaces());

  ROS_DEBUG("KILL semantic_route_drawer");

  return 0;
}
