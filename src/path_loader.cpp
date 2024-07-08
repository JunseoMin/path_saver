#include "path_saver/path_loader.hpp"

Path_Loader::Path_Loader(): Node("Path_Loader")
{
  publisher_ = this->create_publisher<nav_msgs::msg::Path>("/global_path",10);
  timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&Path_Loader::timer_callback, this));
  path_ = load_path("global_path.csv");
}

void Path_Loader::timer_callback()
{
  if (!path_.poses.empty())
  {
    publisher_->publish(path_);
    RCLCPP_INFO(this->get_logger(), "Path published");
  }
}

nav_msgs::msg::Path Path_Loader::load_path(const std::string& file_path)
{
  nav_msgs::msg::Path path_msg;
  path_msg.header.frame_id = "map";
  std::ifstream file(file_path);
  std::string line;
  std::getline(file, line);
  while (std::getline(file, line))
  {
    std::istringstream s(line);
    std::string field;
    geometry_msgs::msg::PoseStamped pose;
    std::getline(s, field, ',');
    pose.pose.position.x = std::stod(field);
    std::getline(s, field, ',');
    pose.pose.position.y = std::stod(field);
    std::getline(s, field, ',');
    pose.pose.position.z = std::stod(field);
    path_msg.poses.push_back(pose);
  }
  return path_msg;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Path_Loader>());
  rclcpp::shutdown();
  return 0;
}