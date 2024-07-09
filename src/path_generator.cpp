#include "path_saver/path_generator.hpp"

Path_Generator::Path_Generator() : Node("path_generator")
{
  
}


int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Path_Generator>());
  rclcpp::shutdown();
  return 0;
}