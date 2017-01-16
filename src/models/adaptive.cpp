/**
* @Author: daemonslayer
* @Date:   2017-01-16T15:36:21+05:30
* @Last modified by:   daemonslayer
* @Last modified time: 2017-01-16T21:46:23+05:30
*/


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/photo/photo.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "../util.h"


using namespace std;
using namespace cv;


int main(int argc, char const *argv[]) {
  title("Text Extractor");
  string win_name = "textextractor";

  Mat img_b;
  img_b = imread("../input/sample.jpg");

  if(img_b.empty()) {
    err_report("Image couldn't be opened");
  }

  Mat img_b_gray;
  cvtColor(img_b, img_b_gray, CV_BGR2GRAY);
  stat_comp("color to gray");

  Mat img_b_blur;

  GaussianBlur(img_b_gray, img_b_blur, Size(3, 3), 0, 0);
  stat_comp("image smoothed");
  // medianBlur(img_b_gray, img_b_blur, 3);
  // stat_comp("image smoothed");

  equalizeHist(img_b_blur, img_b_blur);
  stat_comp("equalize histogram");
  // GaussianBlur(img_b_blur, img_b_blur, Size(3, 3), 0, 0);

  Mat img_b_thres;
  adaptiveThreshold(img_b_blur, img_b_thres, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 4);
  stat_comp("adaptive threshold");

  fastNlMeansDenoising(img_b_thres, img_b_thres, 3, 7, 21);
  stat_comp("denoising image");

  namedWindow(win_name + "_b", CV_WINDOW_AUTOSIZE);
  imshow(win_name + "_b", img_b_thres);

  imwrite("../output/output_b.jpg", img_b_thres);

  waitKey(0);
  return 0;
}
