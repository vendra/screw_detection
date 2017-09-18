/** EuroC project: utility.cpp
  *
  *
  *
  * @author: Vendramin Federico
  *
  *
  */

#include "../include/utility.h"

Utils::Utils() {}

bool Utils::readInput(std::string path, std::vector<std::string>& far_list, std::vector<std::string>& close_list,
               std::vector<std::string>& mid_list, std::vector<std::string>& temp_list)
{
    std::cout << "Reading input file.. ";

    far_list.resize(0);
    mid_list.resize(0);
    close_list.resize(0);
    temp_list.resize(0);

    cv::FileStorage fs(path, cv::FileStorage::READ);
    if ( !fs.isOpened() )
    {
        std::cout << "Cannot open " << path << std::endl;
        return false;
    }

    cv::FileNode n = fs["far"];                                 //reading far distance dataset images
    if ( n.type() != cv::FileNode::SEQ )
    {
        std::cout << "Invalid data type. A list of images is required" << std::endl;
        return false;
    }
    cv::FileNodeIterator it = n.begin(), it_end = n.end();
    for ( ; it != it_end; ++it )
        far_list.push_back((std::string)*it);

    n = fs["mid"];                                 //reading mid distance dataset
    if ( n.type() != cv::FileNode::SEQ )
    {
        std::cout << "Invalid data type. A list of images is required" << std::endl;
        return false;
    }
    it = n.begin();
    it_end = n.end();
    for ( ; it != it_end; ++it )
        mid_list.push_back((std::string)*it);

    n = fs["close"];                                 //reading close image dataset
    if ( n.type() != cv::FileNode::SEQ )
    {
        std::cout << "Invalid data type. A list of images is required" << std::endl;
        return false;
    }
    it = n.begin();
    it_end = n.end();
    for ( ; it != it_end; ++it )
        close_list.push_back((std::string)*it);

    n = fs["template"];                                 //Reading template image list
    if ( n.type() != cv::FileNode::SEQ )
    {
        std::cout << "Invalid data type. A list of images is required" << std::endl;
        return false;
    }
    it = n.begin();
    it_end = n.end();
    for ( ; it != it_end; ++it )
        temp_list.push_back((std::string)*it);

    //Check I actually read something
    if (temp_list.empty() || close_list.empty() || mid_list.empty() || far_list.empty())
    {
        std::cout << "On or more string list is empty" << std::endl;
        return -1;
    }
    std::cout << "DONE!" << std::endl;
    return 1;

}//end readInput



