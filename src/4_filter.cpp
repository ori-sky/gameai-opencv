#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/ocl/ocl.hpp"
#include <iostream>

//   /usr/bin/g++ capture_show_record_image.cpp -lopencv_core -lopencv_highgui

int main(int argc, const char *argv[])
{
  cv::Mat frame;
  cv::Mat frame2;

  double fps = 30;
  const char win_name[] = "Live Video...";
  const char file_out[] = "recorded.avi";

  cv::VideoCapture vid_in(0);   // argument is the camera id
  if (!vid_in.isOpened()) {
    std::cerr << "error: Camera 0 could not be opened for capture.\n";
    return -1;
  }

  double width  = vid_in.get(CV_CAP_PROP_FRAME_WIDTH);
  double height = vid_in.get(CV_CAP_PROP_FRAME_HEIGHT);
  cv::Size_<double> sz(width,height);
  cv::Rect r1(0,           0,            width / 2.0, height / 2.0);
  cv::Rect r2(width / 2.0, 0,            width / 2.0, height / 2.0);
  cv::Rect r3(0,           height / 2.0, width / 2.0, height / 2.0);
  cv::Rect r4(width / 2.0, height / 2.0, width / 2.0, height / 2.0);
  cv::Mat src1, src2, src3, src4, dst1, dst2, dst3, dst4;

  cv::VideoWriter vid_out(file_out, CV_FOURCC('F','F','D','S'), fps, sz);
  if (!vid_out.isOpened()) {
    std::cerr << "error: File "<< file_out << " could not be opened.\n";
    return -1;
  }

  cv::namedWindow(win_name);
  while (1) {
    vid_in  >> frame;
    vid_out << frame;

    cv::Sobel    (frame(r2), frame(r2), CV_8U, 1, 1, 5);
    cv::Laplacian(frame(r3), frame(r3), CV_8U, 3, 100);
    cv::Scharr   (frame(r4), frame(r4), CV_8U, 1, 0);

    imshow(win_name, frame);
    if (cv::waitKey(1000/fps) >= 0) // how long to wait for a key (milliseconds)
      break;
  }

  vid_in.release();
  return 0;
}

