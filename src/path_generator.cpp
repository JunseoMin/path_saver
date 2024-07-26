#include "path_saver/path_generator.hpp"

using namespace std::chrono_literals;

Path_Generator::Path_Generator() 
: Node("path_generator"), buffer_(this->get_clock()),listener_(buffer_)
{
  timer_ = this -> create_wall_timer(100ms, std::bind(&Path_Generator::timer_cb,this));
  file_.open("/root/path/globalpath_with_rot.csv");
  // file_<<"px,py,pz,ox,oy,oz,ow \n";

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
    double o_x = ts.transform.rotation.x;
    double o_y = ts.transform.rotation.y;
    double o_z = ts.transform.rotation.z;
    double o_w = ts.transform.rotation.w;

    if (file_.is_open())
    {
      RCLCPP_INFO(this->get_logger(),"file opened!");
      file_<<p_x << ','<< p_y << ',' << p_z << ',' << o_x<< ',' << o_y<< ',' << o_z << ',' << o_w << '\n';
    }

    RCLCPP_INFO(this->get_logger(),"path recieved!");
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