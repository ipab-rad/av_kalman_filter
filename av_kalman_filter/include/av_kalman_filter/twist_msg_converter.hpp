#pragma once

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist_with_covariance_stamped.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

namespace util {

class TwistMsgConverter : public rclcpp::Node {
public:
    explicit TwistMsgConverter(const rclcpp::NodeOptions &options);

private:
    void imu_callback(const geometry_msgs::msg::TwistStamped &msg);

    // Params
    double linear_vel_std_;
    double angular_vel_std_;

    rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr twist_sub_;
    rclcpp::Publisher<geometry_msgs::msg::TwistWithCovarianceStamped>::SharedPtr twist_pub_;
};

}  // namespace util
