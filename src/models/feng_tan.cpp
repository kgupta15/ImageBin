/**
* @Author: daemonslayer
* @Date:   2017-01-17T10:42:31+05:30
* @Last modified by:   daemonslayer
* @Last modified time: 2017-01-17T16:50:00+05:30
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
  title("Text Extractor : Feng Tan");
  string win_name = "textextractor";

  Mat img_c;
  img_c = imread("../input/sample.jpg");

  Mat img_c_gray;
  cvtColor(img_c, img_c_gray, CV_BGR2GRAY);
  stat_comp("color to gray");


  Mat img_c_bin = Mat::zeros(img_c_gray.rows, img_c_gray.cols, CV_8UC1);

  int s_win = 17;
  int l_win = 35;

  double min_tau = 10;

  Rect roi_s = Rect(-s_win/2, -s_win/2, s_win, s_win);
  Rect roi_l = Rect(-l_win/2, -l_win/2, l_win, l_win);
  Rect img_c_roi = Rect(0, 0, img_c_gray.cols, img_c_gray.rows);

  for (size_t r = 0; r < img_c_gray.rows; r++) {
    for (size_t c = 0; c < img_c_gray.cols; c++) {
      double pthres = 255;

      Rect sROI = roi_s + Point(c, r);
      sROI = sROI & img_c_roi;
      if(sROI.width == 0 || sROI.height == 0) {
        continue;
      }

      Rect lROI = roi_l + Point(c, r);
      lROI = lROI & img_c_roi;
      if(lROI.width == 0 || lROI.height == 0) {
        continue;
      }

      Mat sROI_gray = img_c_gray(sROI);
      Mat lROI_gray = img_c_gray(lROI);

      double s_stdDev = 0;
      double l_stdDev = 0;
      double s_mean = 0;
      double l_mean = 0;
      double l_min = DBL_MAX;

      for (size_t r = 0; r < sROI_gray.rows; r++) {
        for (size_t c = 0; c < sROI_gray.cols; c++) {
          s_mean += sROI_gray.at<unsigned char>(r, c);
        }
      }

      s_mean = s_mean / static_cast<double> (sROI_gray.cols * sROI_gray.rows);

      for (size_t r = 0; r < sROI_gray.rows; r++) {
        for (size_t c = 0; c < sROI_gray.cols; c++) {
          double diff = sROI_gray.at<unsigned char> (r, c) - s_mean;
          s_stdDev += diff * diff;
        }
      }

      s_stdDev = sqrt(s_stdDev / static_cast<int> (sROI_gray.cols * sROI_gray.rows));

      for (size_t r = 0; r < lROI_gray.rows; r++) {
        for (size_t c = 0; c < lROI_gray.cols; c++) {
          l_mean += lROI_gray.at<unsigned char> (c, r);

          if(lROI_gray.at<unsigned char> (r, c) < l_min) {
            l_min = lROI_gray.at<unsigned char> (r, c);
          }
        }
      }
      l_mean = l_mean / static_cast<double> (lROI_gray.cols * lROI_gray.rows);

      for (size_t r = 0; r < lROI_gray.rows; r++) {
        for (size_t c = 0; c < lROI_gray.cols; c++) {
          double diff = lROI_gray.at<unsigned char> (r, c) - l_mean;
          l_stdDev += diff * diff;
        }
      }
      l_stdDev = sqrt(l_stdDev / static_cast<double> (lROI_gray.cols * lROI_gray.rows));

      double tau = ((s_mean - l_min) * (1 - s_stdDev / l_stdDev)) / 2.0;
      if(tau < min_tau) {
        tau = min_tau;
      }

      double threshold = s_mean - tau;

      unsigned char pixel_val = img_c_gray.at<unsigned char>(r, c);
      if(pixel_val >= threshold) {
        img_c_bin.at<unsigned char> (r, c) = 255;
      } else {
        img_c_bin.at<unsigned char> (r, c) = 0;
      }
    }
  }

  namedWindow(win_name + "_c", CV_WINDOW_AUTOSIZE);
  imshow(win_name + "_c", img_c_bin);

  imwrite("../output/output_c.jpg", img_c_bin);
  waitKey(0);
  return 0;
}
