#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

//   /usr/bin/g++ capture_show_image.cpp -lopencv_core -lopencv_highgui

int main(int argc, const char *argv[])
{
  cv::Mat frame;
  double fps = 30;
  const char win_name[] = "Live Video...";

  cv::VideoCapture vid_in(0);   // argument is the camera id
  if (!vid_in.isOpened()) {
    std::cout << "error: Camera 0 could not be opened for capture.\n";
    return -1;
  }

  cv::namedWindow(win_name);
  while (1) {
    vid_in >> frame;
    imshow(win_name, frame);
    if (cv::waitKey(1000/fps) >= 0) // how long to wait for a key (milliseconds)
      break;
  }

  vid_in.release();
  return 0;
}

