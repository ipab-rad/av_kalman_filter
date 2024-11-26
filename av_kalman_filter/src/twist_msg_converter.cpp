#include "av_kalman_filter/twist_msg_converter.hpp"

namespace util
{

TwistMsgConverter::TwistMsgConverter(const rclcpp::NodeOptions &options) :
                                Node("twist_msg_convertor", options)
{
    linear_vel_std_ = this->declare_parameter<double>("linear_vel_std", 0.1);
    angular_vel_std_ = this->declare_parameter<double>("angluar_vel_std", 0.01);

    twist_sub_ = this->create_subscription<geometry_msgs::msg::TwistStamped>(
        "twist_in", 10,
            std::bind(&TwistMsgConverter::imu_callback, this, std::placeholders::_1));

    twist_pub_ =
        this->create_publisher<geometry_msgs::msg::TwistWithCovarianceStamped>("twist_out", 10);

    RCLCPP_INFO(
        this->get_logger(),
        "\nTwist msg converter started! Using:\n\tlinear_vel_std: %f\n\tangular_vel_std: %f",
        linear_vel_std_, angular_vel_std_);
}

void TwistMsgConverter::imu_callback(const geometry_msgs::msg::TwistStamped &msg)
{
    // Convert to TwistWithCovarianceSTamped

    geometry_msgs::msg::TwistWithCovarianceStamped new_msg;

    new_msg.header = msg.header;
    new_msg.twist.twist = msg.twist;

    double linear_vel_variance = linear_vel_std_ * linear_vel_std_;
    double angular_vel_variance = angular_vel_std_ * angular_vel_std_;

    // Set the diagonal covariance values
    new_msg.twist.covariance = {
        linear_vel_variance, 0.0, 0.0, 0.0, 0.0, 0.0,   // Covariance for linear x
        0.0, linear_vel_variance, 0.0, 0.0, 0.0, 0.0,   // Covariance for linear y
        0.0, 0.0, linear_vel_variance, 0.0, 0.0, 0.0,   // Covariance for linear z
        0.0, 0.0, 0.0, angular_vel_variance, 0.0, 0.0,  // Covariance for angular x
        0.0, 0.0, 0.0, 0.0, angular_vel_variance, 0.0,  // Covariance for angular y
        0.0, 0.0, 0.0, 0.0, 0.0, angular_vel_variance   // Covariance for angular z
    };

    twist_pub_->publish(new_msg);
}


}  // namespace util

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(util::TwistMsgConverter)
