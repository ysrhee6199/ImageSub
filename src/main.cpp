#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

class ImageSubscriberNode : public rclcpp::Node {
public:
    ImageSubscriberNode() : Node("image_subscriber_node") {
// Set up the QoS
        rclcpp::QoS qos(rclcpp::QoSInitialization::from_rmw(rmw_qos_profile_sensor_data));
        qos.best_effort();

        // Subscribe to the image topic with best_effort QoS
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/LV/carla/camera", qos,
            std::bind(&ImageSubscriberNode::imageCallback, this, std::placeholders::_1));
    }

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
    
        try {
            // Convert the ROS image message to an OpenCV image
            cv_bridge::CvImagePtr cv_ptr;
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);

            // Display the image using OpenCV
            cv::imshow("Image Window", cv_ptr->image);
            cv::waitKey(1);
        } catch (cv_bridge::Exception& e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSubscriberNode>());
    rclcpp::shutdown();
    return 0;
}