#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

//   /usr/bin/g++ capture_show_image.cpp -lopencv_core -lopencv_highgui

int main(int argc, const char *argv[])
{
  cv::Mat frame;
  const char win_name[] = "Live Video...";

  cv::VideoCapture vid_in(0);   // argument is the camera id
  if (!vid_in.isOpened()) {
    std::cout << "error: Camera 0 could not be opened for capture.\n";
    return -1;
  }

  cv::namedWindow(win_name);
  vid_in >> frame;
  imshow(win_name, frame);
  cv::waitKey(0);

  vid_in.release();
  return 0;
}

