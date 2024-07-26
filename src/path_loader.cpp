#include "path_saver/path_loader.hpp"

Path_Loader::Path_Loader() : Node("Path_Loader")
{
  publisher_ = this->create_publisher<nav_msgs::msg::Path>("/path", 10);
  timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&Path_Loader::timer_callback, this));
  path_ = load_path("/root/path/globalpath__.csv");
  RCLCPP_INFO(this->get_logger(), "Path loaded");
}

void Path_Loader::timer_callback()
{
  if (!path_.poses.empty())
  {
    publisher_->publish(path_);
    // RCLCPP_INFO(this->get_logger(), "Path published");
  }
  else
  {
    RCLCPP_WARN(this->get_logger(), "Path empty");
  }
}

nav_msgs::msg::Path Path_Loader::load_path(const std::string &file_path)
{
  nav_msgs::msg::Path path_msg;
  path_msg.header.frame_id = "map";
  std::ifstream file(file_path);

  if (!file.is_open())
  {
    RCLCPP_ERROR(this->get_logger(), "Failed to open file: %s", file_path.c_str());
    return path_msg;
  }

  RCLCPP_INFO(this->get_logger(), "File opened: %s", file_path.c_str());
  std::string line;
  
  while (std::getline(file, line))
  {
    std::istringstream s(line);
    std::string field;
    geometry_msgs::msg::PoseStamped pose;
    
    try
    {
      if (!std::getline(s, field, ',')) continue;
      pose.pose.position.x = std::stod(field);
      
      if (!std::getline(s, field, ',')) continue;
      pose.pose.position.y = std::stod(field);
      
      if (!std::getline(s, field, ',')) continue;
      pose.pose.position.z = std::stod(field);
      
      if (!std::getline(s, field, ',')) continue;
      pose.pose.orientation.x = std::stod(field);
      
      if (!std::getline(s, field, ',')) continue;
      pose.pose.orientation.y = std::stod(field);
      
      if (!std::getline(s, field, ',')) continue;
      pose.pose.orientation.z = std::stod(field);
      
      if (!std::getline(s, field, ',')) continue;
      pose.pose.orientation.w = std::stod(field);
      
      path_msg.poses.push_back(pose);
      RCLCPP_INFO(this->get_logger(), "Path point added: (%f, %f, %f) (%f, %f, %f, %f)", pose.pose.position.x, pose.pose.position.y, pose.pose.position.z, pose.pose.orientation.x, pose.pose.orientation.y, pose.pose.orientation.z, pose.pose.orientation.w);
    }
    catch (const std::invalid_argument& e)
    {
      RCLCPP_ERROR(this->get_logger(), "Invalid data encountered in line: %s", line.c_str());
      continue;
    }
    catch (const std::out_of_range& e)
    {
      RCLCPP_ERROR(this->get_logger(), "Out of range data encountered in line: %s", line.c_str());
      continue;
    }
  }
  
  if (path_msg.poses.empty())
  {
    RCLCPP_WARN(this->get_logger(), "No valid path points found in the file: %s", file_path.c_str());
  }
  
  return path_msg;
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Path_Loader>());
  rclcpp::shutdown();
  return 0;
}
