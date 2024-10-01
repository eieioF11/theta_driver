#ifndef THETA_DERIVER_LIB_HPP
#define THETA_DERIVER_LIB_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <gst/app/gstappsink.h>
#include <libuvc/libuvc.h>
#include <opencv2/core.hpp>
#include "thetauvc.h"

namespace theta_driver {

class ThetaDriver : public rclcpp::Node {
    template<class T>
    T param(const std::string& name, const T& def) {
        T value;
        declare_parameter(name, def);
        get_parameter(name, value);
        return value;
    }
    void show_array(const std::vector<double>& v) {
        for (auto& e : v) {
            std::cout << e << ", ";
        }
        std::cout << std::endl;
    }
    sensor_msgs::msg::CameraInfo camera_info_;
    void get_camera_param() {
        camera_info_.header.frame_id = camera_frame_;
        camera_info_.width = param<int>("camera_param.image_width", 1920);
        camera_info_.height = param<int>("camera_param.image_height", 960);
        std::vector<double> k = param<std::vector<double>>("camera_param.camera_matrix.data", std::vector<double>{452.97016, 0., 932.16609,
                                                                                                           0., 403.75627, 520.10583,
                                                                                                           0., 0., 1.});
        std::vector<double> d = param<std::vector<double>>("camera_param.distortion_coefficients.data", std::vector<double>{-0.133120, 0.011309, 0.009001, 0.012501, 0.000000});
        std::vector<double> r = param<std::vector<double>>("camera_param.rectification_matrix.data", std::vector<double>{1., 0., 0.,
                                                                                                                  0., 1., 0.,
                                                                                                                  0., 0., 1.});
        std::vector<double> p = param<std::vector<double>>("camera_param.projection_matrix.data", std::vector<double>{434.32685, 0., 689.02068, 0.,
                                                                                                               0., 419.17151, 421.29719, 0.,
                                                                                                               0., 0., 1., 0.});
        camera_info_.distortion_model = param<std::string>("camera_param.distortion_model", "plumb_bob");
        std::cout << "camera_info" << std::endl;
        std::cout << "width: " << camera_info_.width << std::endl;
        std::cout << "height: " << camera_info_.height << std::endl;
        std::cout << "k: ";
        show_array(k);
        std::cout << "d: ";
        show_array(d);
        std::cout << "r: ";
        show_array(r);
        std::cout << "p: ";
        show_array(p);
        std::cout << "distortion_model: " << camera_info_.distortion_model << std::endl;
        std::copy(k.begin(), k.end(), camera_info_.k.begin());
        camera_info_.d = d;
        // std::copy(d.begin(), d.end(), camera_info_.d.begin());//
        std::copy(r.begin(), r.end(), camera_info_.r.begin());
        std::copy(p.begin(), p.end(), camera_info_.p.begin());
        // camera_info_.k = ;
        // camera_info_.d = ;
        // camera_info_.r = ;
        // camera_info_.p = ;
    }

public:
    ThetaDriver(const rclcpp::NodeOptions& options);
    virtual ~ThetaDriver();
    void onInit();
    bool init();
    bool open();
    void publishImage(GstMapInfo map);

    bool streaming_ = false;
    uvc_device_handle_t* devh_;
    uvc_stream_ctrl_t ctrl_;
    uvc_context_t* ctx_;
    bool use4k_ = false;
    std::string serial_ = "";
    std::string camera_frame_ = "camera_link";
    std::string pipeline_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;
    rclcpp::Publisher<sensor_msgs::msg::CameraInfo>::SharedPtr info_pub_;
};

struct gst_src {
    GstElement* pipeline;
    GstElement* appsrc;

    GMainLoop* loop;
    GTimer* timer;
    guint framecount;
    guint id;
    guint bus_watch_id;
    uint32_t dwFrameInterval;
    uint32_t dwClockFrequency;
};

} // namespace theta_driver

#endif // THETA_DERIVER_LIB_HPP
