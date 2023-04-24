#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class greeting : public rclcpp::Node
{
public:
  greeting():Node("hello"), _count(0){
    _timer = this->create_wall_timer(500ms, std::bind(&greeting::timer_callback, this));
  }

private:
  void timer_callback(){
    auto message = std_msgs::msg::String();
    message.data = std::to_string(_count++) + ": Hello World !" ;
    RCLCPP_INFO(this->get_logger(), "%s", message.data.c_str());
  }

  rclcpp::TimerBase::SharedPtr _timer;
  size_t _count;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<greeting>());
  rclcpp::shutdown();
  return 0;
}