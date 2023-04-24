#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalNode : public rclcpp::Node{
public:
  MinimalNode(): Node("minimal_node"){
    publisher_ = this->create_publisher<std_msgs::msg::String>("hello", 10);
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "hello", 10, std::bind(&MinimalNode::topic_callback, this, _1));
    
    timer_ = this->create_wall_timer(
      std::chrono::seconds(1), std::bind(&MinimalNode::timer_callback, this));
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const{
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
  }

  void timer_callback(){
    auto message = std_msgs::msg::String();
    message.data = "Hello, world!";
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char* argv[]){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalNode>());
  rclcpp::shutdown();
  return 0;
}