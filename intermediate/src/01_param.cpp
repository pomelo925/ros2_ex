#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam(): Node("minimal_param_node")
  {
    this->declare_parameter("print_text", "Hello");
    this->declare_parameter("print_count", 1);

    timer_ = this->create_wall_timer(
      200ms, std::bind(&MinimalParam::timer_callback, this));
  }

  void timer_callback()
  {
  // print_text callback
    if (count>=20) this->set_parameter(rclcpp::Parameter("print_text", "Bye"));
    text = this->get_parameter("print_text").as_string();

  // print_num callback
    count = this->get_parameter("print_count").as_int();
    this->set_parameter(rclcpp::Parameter("print_count", ++count));

  // print all params
    RCLCPP_INFO(this->get_logger(), "%d: %s World!", count, text.c_str());
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  int count=0;
  std::string text;
};


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}