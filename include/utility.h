/** EuroC project: utility.h
  *
  *
  *
  * @author: Vendramin Federico
  *
  *
  */
#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/flann/flann.hpp>
#include <opencv2/flann/flann_base.hpp>


/* Class Utils
 * read the input path file and loads the image and template lists
 */
class Utils
{
public:
    Utils();

    /* Loads the frames and templates lists from the XML file provided
     * Returns true if the inputs have been correctly loaded
     */
    bool static readInput(std::string path, std::vector<std::string>& far_list, std::vector<std::string>& close_list,
                   std::vector<std::string>& mid_list, std::vector<std::string>& temp_list);
};

#endif
