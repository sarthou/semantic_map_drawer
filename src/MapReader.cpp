#include "route_drawer/MapReader.h"

#include <iostream>
#include <algorithm>

void MapReader::getMap()
{
  getCorridors();

  for(size_t i = 0; i < corridors_.size(); i++)
  {
    getSides(corridors_[i]);
    getInFrontOf(corridors_[i]);
    //displayCorridor(corridors_[i]);
  }
}

void MapReader::getCorridors()
{
  std::vector<std::string> corridors = onto_.getType("corridor");
  for(size_t i = 0; i < corridors.size(); i++)
  {
    corridor_t tmp;
    tmp.name_ = corridors[i];
    corridors_.push_back(tmp);
  }
}

void MapReader::getInFrontOf(corridor_t& corridor)
{
  for(size_t place_i = 0; place_i < corridor.at_right_.size(); place_i++)
  {
    std::vector<std::string> front = onto_.getOn(corridor.at_right_[place_i], "hasInFront");
    for(size_t i = 0; i < front.size(); i++)
    {
      std::vector<std::string>::iterator it = std::find(corridor.at_left_.begin(), corridor.at_left_.end(), front[i]);
      if(it != corridor.at_left_.end())
      {
        corridor.in_front_of_[front[i]] = corridor.at_right_[place_i];
        corridor.in_front_of_[corridor.at_right_[place_i]] = front[i];
      }
    }
  }
}

void MapReader::getSides(corridor_t& corridor)
{
  corridor.at_right_ = getSide(corridor.name_, "isAtRightOfPath");
  corridor.at_left_ = getSide(corridor.name_, "isAtLeftOfPath");
  corridor.at_begin_edge_ = getSide(corridor.name_, "isAtBeginEdgeOfPath");
  corridor.at_end_edge_ = getSide(corridor.name_, "isAtEndEdgeOfPath");
}

std::vector<std::string> MapReader::getSide(std::string corridor, std::string property)
{
  std::vector<std::string> places = onto_.getFrom(property, corridor);

  if((property == "isAtLeftOfPath") || (property == "isAtEndEdgeOfPath"))
    return orderPlaces(places, true);
  else
    return orderPlaces(places, false);
}

std::vector<std::string> MapReader::orderPlaces(std::vector<std::string> base, bool inverse)
{
  std::vector<std::string> ordered;
  size_t max_time = base.size();
  for(size_t timeout = 0; (timeout < max_time) && (base.size() != 0); timeout++)
    for(size_t i = 0; i < base.size();)
    {
      std::vector<std::string> atLeft = onto_.getOn(base[i], "isAtRightOf");
      if(atLeft.size() == 0)
      {
        ordered.insert(ordered.begin(), base[i]);
        base.erase(base.begin() + i);
      }
      else
      {
        std::vector<std::string>::iterator it = std::find(ordered.begin(), ordered.end(), atLeft[0]);
        if(it != ordered.end())
        {
          ordered.insert(it + 1, base[i]);
          base.erase(base.begin() + i);
        }
        else
          i++;
      }
    }

  if(inverse)
    std::reverse(ordered.begin(),ordered.end());

  return ordered;
}

void MapReader::displayCorridor(corridor_t corridor)
{
  std::cout << "**** " << corridor.name_ << " ****" << std::endl;
  displaySide(corridor.at_right_, "RIGHT");
  displaySide(corridor.at_left_, "LEFT");
  displaySide(corridor.at_begin_edge_, "BEGIN");
  displaySide(corridor.at_end_edge_, "END");
}

void MapReader::displaySide(std::vector<std::string> side, std::string name)
{
  std::cout << name << " : ";
  for(size_t i = 0; i < side.size(); i++)
    std::cout << side[i] << " <=> ";
  std::cout << std::endl;
}
