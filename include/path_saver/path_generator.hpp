#ifndef PATH_SAVER__PATH_GENERATOR_HPP_
#define PATH_SAVER__PATH_GENERATOR_HPP_

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/path.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

#include <fstream>

class Path_Generator : public rclcpp::Node
{
public:
  Path_Generator();
private:
  // rclcpp::Subscription<> subscriber_;
};
#endif  // PATH_SAVER__PATH_GENERATOR_HPP_
