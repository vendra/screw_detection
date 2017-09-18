/** EuroC project: screw_matching.cpp
  *
  *
  *
  * @author: Vendramin Federico
  *
  *
  */

#include "../include/screw_matching.h"

ScrewMatching::ScrewMatching(const cv::Mat& frame, const cv::Mat& template_image, float threshold)
{

}

ScrewMatching::ScrewMatching() {}

void ScrewMatching::setFrame(const cv::Mat& frame)
{
  try
  {
    cv::cvtColor(frame, frame_, CV_BGR2GRAY);
  }
  catch(...)
  {
      frame_ = frame;
  }
}

void ScrewMatching::setTemplate(const cv::Mat& template_image)
{
  try
  {
    cv::cvtColor(template_image, template_image_, CV_BGR2GRAY);
  }
  catch(...)
  {
      template_image_ = template_image;
  }


}

void ScrewMatching::setThreshold(float threshold)
{
  if (threshold < 0)
  {
    //error ?
  }
  else if (threshold < 1)
  {
    threshold_ = threshold;
  }
}

void ScrewMatching::getMatch(std::vector<cv::Point2f>& output, std::vector<double>& score)
{
  //TEMPLATE MATCH
  cv::Mat res(frame_.rows - template_image_.rows + 1, frame_.cols - template_image_.cols + 1, CV_32FC1);
  matchTemplate(frame_, template_image_, res, CV_TM_CCOEFF_NORMED);
  threshold(res, res, 0.4, 1., CV_THRESH_TOZERO);

  double minval, maxval, threshold = (double)threshold_;
  cv::Point minloc, maxloc;

  do
  {
    minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);
    cv::Point push_point(maxloc.x + template_image_.rows / 2 , maxloc.y + template_image_.cols / 2);
    output.push_back(push_point);
    score.push_back(maxval);
    cv::floodFill(res, maxloc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));
  } while (maxval >= threshold);

}//end getMatch
