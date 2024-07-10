#ifndef PATH_SAVER__PATH_GENERATOR_HPP_
#define PATH_SAVER__PATH_GENERATOR_HPP_

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/path.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2/buffer_core.h"

#include <fstream>

class Path_Generator : public rclcpp::Node
{
public:
  Path_Generator();

private:
  void timer_cb();

  rclcpp::TimerBase::SharedPtr timer_;
  tf2_ros::Buffer buffer_;
  tf2_ros::TransformListener listener_;
  std::ofstream file_;
};
#endif  // PATH_SAVER__PATH_GENERATOR_HPP_
