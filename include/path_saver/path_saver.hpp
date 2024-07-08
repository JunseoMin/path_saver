#ifndef path_saver__PathSaver_HPP_
#define path_saver__PathSaver_HPP_

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/path.hpp"
#include <fstream>

class PathSaver : public rclcpp::Node
{
public:
  PathSaver();
  
private:
  void path_callback(const nav_msgs::msg::Path::SharedPtr msg);
  void path_to_csv(const nav_msgs::msg::Path::SharedPtr path);

  rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr subs_;
};

#endif  // path_saver__PathSaver_HPP_