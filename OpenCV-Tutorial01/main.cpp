#include <opencv2/highgui.hpp>

int main() {
  cv::Mat image = cv::imread("Lenna.png");
  cv::imshow("Image", image);
  cv::waitKey(0);
  return 0;
}