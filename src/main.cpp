#include "../include/ImageHandle.h"
#include "../include/LaneFitting.h"

#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {
    std::cout << "hello world" << std::endl;

    cv::Mat superman;
    superman = cv::imread("/home/HwHiAiUser/HIAI_PROJECTS/Atlas_LaneDetection/TEST_Date/lane4.jpg");

    auto image_hanle_start = std::chrono::high_resolution_clock::now();
    
    ImageHandle handler;
    handler.setImage(&superman);
    // handler.TEST();
    cv::Mat superman_pers = handler.handleImage();
    
    // TODO: Debug之后删除
    auto image_handle_finished = std::chrono::high_resolution_clock::now();
    auto image_handle_millise = std::chrono::duration_cast<std::chrono::milliseconds>(image_handle_finished - image_hanle_start);
    std::cout<<"use "<< image_handle_millise.count()<<" millise\n";
    // cv::imshow("superman pers", superman_pers);
    // cv::waitKey(0);

    LaneFitting lane_fit;
	
    auto lane_fit_start = std::chrono::high_resolution_clock::now();
    lane_fit.findLane(superman_pers);
    lane_fit.laneFitting(superman_pers);
    auto lane_fit_end = std::chrono::high_resolution_clock::now();


    auto lane_fit_millise = std::chrono::duration_cast<std::chrono::milliseconds>(lane_fit_end - lane_fit_start);
    std::cout<<"use "<< lane_fit_millise.count()<<" millise\n";

    return 1;
}
