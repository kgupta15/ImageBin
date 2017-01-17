
/**
* @Author: daemonslayer
* @Date:   2017-01-16T15:36:21+05:30
* @Last modified by:   daemonslayer
* @Last modified time: 2017-01-16T21:58:55+05:30
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
  title("Text Extractor : Otsu");
  string win_name = "textextractor";

  Mat img_a;
  img_a = imread("../input/sample.jpg");

  if(img_a.empty()) {
    err_report("Image couldn't be opened");
  }

  Mat img_a_gray;
  cvtColor(img_a, img_a_gray, CV_BGR2GRAY);
  stat_comp("color to gray");

  Mat img_a_blur;

  GaussianBlur(img_a_gray, img_a_blur, Size(3, 3), 0, 0);
  stat_comp("image smoothed");
  // medianBlur(img_a_gray, img_a_blur, 3);
  // stat_comp("image smoothed");

  equalizeHist(img_a_blur, img_a_blur);
  stat_comp("equalize histogram");
  // GaussianBlur(img_a_blur, img_a_blur, Size(3, 3), 0, 0);

  Mat img_a_thres;
  threshold(img_a_blur, img_a_thres, 0, 255, THRESH_OTSU);
  stat_comp("otsu threshold");

  fastNlMeansDenoising(img_a_thres, img_a_thres, 3, 7, 21);
  stat_comp("denoising image");

  namedWindow(win_name + "_a", CV_WINDOW_AUTOSIZE);
  imshow(win_name + "_a", img_a_thres);

  imwrite("../output/output_a.jpg", img_a_thres);

  waitKey(0);
  return 0;
}
