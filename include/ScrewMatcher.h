/** EuroC project: screw_matching.h
  *
  *
  *
  * @author: Vendramin Federico
  *
  *
  */
#ifndef SCREW_MATCHER_H
#define SCREW_MATCHER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/*
 * Class that allows to identify a given template in a frame
 */
class ScrewMatcher
{
private:
    cv::Mat frame_, template_image_;
    float threshold_;

public:
    ScrewMatcher(const cv::Mat& frame, const cv::Mat& template_image, float threshold);
    ScrewMatcher();

    //Set the frame to use for template matching
    void setFrame(const cv::Mat& frame);

    //Set the template to search on the frame
    void setTemplate(const cv::Mat& template_image);

    //Set the threshold level to filter results below a certain threshold
    void setThreshold(float threshold);

    //Actually executes the template match search
    void getMatch(std::vector<cv::Point2f>& output, std::vector<double>& score);
};

#endif
