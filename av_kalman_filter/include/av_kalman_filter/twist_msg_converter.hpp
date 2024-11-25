#pragma once

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist_with_covariance_stamped.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

namespace util
{

    using namespace geometry_msgs::msg;

    class TwistMsgConverter : public rclcpp::Node
    {
    public:
    
        TwistMsgConverter(const rclcpp::NodeOptions &options);

    private:

        void imu_callback(const TwistStamped & msg);

        // Params
        double linear_vel_std_;
        double angular_vel_std_;


        rclcpp::Subscription<TwistStamped>::SharedPtr twist_sub_;
        rclcpp::Publisher<TwistWithCovarianceStamped>::SharedPtr twist_pub_;
    };

}// namespace util