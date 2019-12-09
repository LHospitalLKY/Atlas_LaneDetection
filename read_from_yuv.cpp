
#include <iostream>
#include <fstream>
#include <memory>

#include <opencv2/opencv.hpp>

void read_txt(char* data_block, std::string file_name) {
    std::ifstream read_file;
    read_file.open(file_name, std::ios::binary);
    for(int i = 0; i < 3110400; i++) {
        read_file >> data_block[i];
    }
    read_file.close();
}

int main(int argc, char **argv) {
    std::string file_name = "/home/lho/MyProgramm/Dev/LaneDetection/TEST_Date/yuv.txt";
    char data[3110400];
    read_txt(data, file_name);

    cv::Mat yuv_img;
    yuv_img.create(1080*3/2, 1920, CV_8UC1);
	memcpy(yuv_img.data, data, 3110400*sizeof(char));

    // cv::imshow("yuv", yuv_img);
    // cv::waitKey(0);

    cv::Mat rgb_img;
    cv::cvtColor(yuv_img, rgb_img, CV_YUV420sp2BGR);

    // cv::imshow("rgb", rgb_img);
    // cv::waitKey(0);

    cv::imwrite("RGBImage.jpg", rgb_img);

    return 1;

}