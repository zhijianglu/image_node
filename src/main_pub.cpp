//
// Created by lab on 20-5-25.
//
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>


#include <iomanip>
#include <vector>
#include "/home/lab/cpp_lib/getfile.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);//发布图片需要用到image_transport
    image_transport::Publisher pub = it.advertise("/dji_data/image_raw", 100);

    //TODO read imgs
    std::string source = "/media/lab/DiskDocuments/Data/DJI47/960X540"; //DJI data
//    std::string source = "/home/lab/Dataset/kinect/modu_768x432"; //kinect color
    std::vector<std::string> files;
    if (getdir(source, files) >= 0) {
        printf("found %d image files in folder %s!\n", (int) files.size(), source.c_str());
    } else if (getFile(source, files) >= 0) {
        printf("found %d image files in file %s!\n", (int) files.size(), source.c_str());
    } else {
        printf("could not load file list! wrong path / file?\n");
    }

    ros::Rate loop_rate(5);
    int img_cnt = 0;
    float period = 1.0f / 30.0f;
    while (nh.ok())
    {
        if(img_cnt==files.size())break;
        cv::Mat image = cv::imread(files[img_cnt], CV_LOAD_IMAGE_UNCHANGED);

        cout<<"---------------frame: "<<img_cnt<<endl;
        std_msgs::Header frameheader;


        frameheader.stamp.fromNSec((1.0f*float(img_cnt)*1e9) / 30.0f);
        frameheader.frame_id = to_string(frameheader.stamp.sec) + "." + to_string(frameheader.stamp.nsec);
//

//        cout<<"frameheader.stamp "<<frameheader.stamp <<endl;
//
//        cout<<"frameheader.stamp.sec  "<<frameheader.stamp.sec <<endl;
//        cout<<"frameheader.stamp.nsec "<<frameheader.stamp.nsec<<endl;
//
//        cout<<"frameheader.frame_id   "<<frameheader.frame_id <<endl;
//        cout<<"frameheader.stamp.toSec() :  "<<frameheader.stamp.toSec() <<endl;

        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(frameheader, "bgr8", image).toImageMsg();

        img_cnt++;
        pub.publish(msg);

        ros::spinOnce();

//        imshow("image", image);
//        waitKey(1);
        loop_rate.sleep();
    }



}
