#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
using namespace std;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
//sensor_msgs::Image ROS中image传递的消息形式
    try
    {
        cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        cv::waitKey(1);
        cout<<"frame info:"<<endl;
        cout<<"            frame id:"<<msg->header.frame_id<<endl;
        cout<<"                 sec:"<<msg->header.stamp.sec<<endl;
        cout<<"                nsec:"<<msg->header.stamp.nsec<<endl;
        cout<<"                 seq:"<<msg->header.seq<<endl;
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_sub_node");
    ros::NodeHandle nh;
    cv::namedWindow("view");
    cv::startWindowThread();
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/cam0/image_raw", 1, imageCallback);
    ros::spin();
    cv::destroyWindow("view");  //窗口
}  
