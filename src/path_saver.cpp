#include "path_saver/path_saver.hpp"

PathSaver::PathSaver() : Node("path_saver_node")
{
  subs_ = this->create_subscription<nav_msgs::msg::Path>(
    "/path",10,std::bind(&PathSaver::path_callback,this,std::placeholders::_1));
}

void PathSaver::path_callback(const nav_msgs::msg::Path::SharedPtr msg)
{
  RCLCPP_INFO(this->get_logger(),"Path Recieved!");
  PathSaver::path_to_csv(msg);
}

void PathSaver::path_to_csv(const nav_msgs::msg::Path::SharedPtr path)
{
  std::ofstream file("path/global_path.csv");
  file << "x,y,z \n";

  for (const auto& pose : path->poses){
    const auto& position = pose.pose.position;

    file << position.x << "," << position.y << "," << position.z << "\n";
  }

  RCLCPP_INFO(this->get_logger(),"Path saved!!");
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PathSaver>());
  rclcpp::shutdown();
  return 0;
}
