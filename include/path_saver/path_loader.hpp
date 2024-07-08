#ifndef PATH_LOADER_NODE__PATH_LOADER_HPP_
#define PATH_LOADER_NODE__PATH_LOADER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/path.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#include <fstream>

class Path_Loader : public rclcpp::Node
{
public:
  Path_Loader();
private:
  void timer_callback();
  nav_msgs::msg::Path load_path(const std::string& file_path);
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  nav_msgs::msg::Path path_;
};

#endif // PATH_LOADER_NODE__PATH_LOADER_HPP__