#include "path_saver/path_generator.hpp"

using namespace std::chrono_literals;

Path_Generator::Path_Generator() 
: Node("path_generator"), buffer_(this->get_clock()),listener_(buffer_)
{
  timer_ = this -> create_wall_timer(100ms, std::bind(&Path_Generator::timer_cb,this));
  file_.open("path/globalpath.csv");
  file_<<"x,y,z \n";

  RCLCPP_INFO(this->get_logger(), "**** path_generator initalized!! ****");
}

void Path_Generator::timer_cb(){
  try
  {
    geometry_msgs::msg::TransformStamped ts;
    ts = buffer_.lookupTransform("map","base_link",tf2::TimePointZero);
    double p_x = ts.transform.translation.x;
    double p_y = ts.transform.translation.y;
    double p_z = ts.transform.translation.z;

    if (file_.is_open())
    {
      file_<<p_x << ','<< p_y << ',' << p_z << '\n';
    }
    
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
}


int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Path_Generator>());
  rclcpp::shutdown();
  return 0;
}