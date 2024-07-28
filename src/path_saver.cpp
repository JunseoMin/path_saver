#include "path_saver/path_saver.hpp"

PathSaver::PathSaver() 
: Node("path_saver_node")
{
  subs_ = this->create_subscription<nav_msgs::msg::Path>(
    "/trajectory",10,std::bind(&PathSaver::path_callback,this,std::placeholders::_1));
  
  file_.open("/root/colcon_ws/src/path_saver/path/globalpath_v2.0.csv");  
  if (!file_.is_open()) {
    RCLCPP_ERROR(this->get_logger(), "Failed to open file!");
  } else {
    RCLCPP_INFO(this->get_logger(), "File opened successfully.");
  }
}

void PathSaver::path_callback(const nav_msgs::msg::Path::SharedPtr msg)
{
  RCLCPP_INFO(this->get_logger(),"Path Received!");

  const auto& pose = msg->poses.back();
  const double p_x = pose.pose.position.x;
  const double p_y = pose.pose.position.y;
  const double p_z = pose.pose.position.z;
  const double r_x = pose.pose.orientation.x;
  const double r_y = pose.pose.orientation.y;
  const double r_z = pose.pose.orientation.z;
  const double r_w = pose.pose.orientation.w;

  try
  {
    if(file_.is_open()){
      RCLCPP_INFO(this->get_logger(),"Writing to file...");
      file_ << p_x << "," << p_y << "," << p_z <<"," 
            << r_x <<"," << r_y <<"," << r_z <<"," 
            << r_w << "\n";
      file_.flush(); // Ensure data is written to the file

      std::cout << p_x << "," << p_y << "," << p_z <<"," 
                << r_x <<"," << r_y <<"," << r_z <<"," 
                << r_w << std::endl;
      RCLCPP_INFO(this->get_logger(),"Path added to file.");
    } 
    else {
      RCLCPP_ERROR(this->get_logger(), "File is not open!");
    }
  }
  catch(const std::exception& e)
  {
    RCLCPP_ERROR(this->get_logger(), "Exception: %s", e.what());
  } 
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PathSaver>());
  rclcpp::shutdown();
  return 0;
}
