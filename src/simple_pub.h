#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class SimplePub : public rclcpp::Node
{
public:
    SimplePub()
        : Node("simple_pub"), m_Count(0)
    {
        m_Publisher = this->create_publisher<std_msgs::msg::String>("topic", 10);
        m_Timer = this->create_wall_timer(500ms, std::bind(&SimplePub::timer_callback, this));
    }

private:
    void timer_callback()
    {
        std_msgs::msg::String message;
        message.data = "Hello, world! " + std::to_string(m_Count++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        m_Publisher->publish(message);
    }

private:
    rclcpp::TimerBase::SharedPtr m_Timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr m_Publisher;
    size_t m_Count;
};