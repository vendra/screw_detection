/** EuroC project: main.cpp
 *
 *
 * @author: Federico Vendramin
 *
 *
 *
 *
 *
 */

#include "../include/screw_matching.h"
#include "../include/utility.h"

const int RADIUS = 75; //point is neighbour if within radius

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <.XML>\n"
              << "\t -h, --help\t\t Show this help message\n"
              << "\t.XML \t\t\t path to the .XML file containing dataset paths" << std::endl;
}

int main(int argc, char* argv[])
{
    std::string arg = "../default.xml";
    if (argc == 2)
    {
        arg = argv[1];
        if ((arg == "-h") || (arg == "--help"))
        {
            show_usage(argv[0]);
            return -1;
        } else {
            std::cout << "XML path specified: " << argv[1] << std::endl;
        }

    } else if(argc == 1) {
        std::cout << "Using default path" << std::endl;
    } else {
        show_usage(argv[0]);
        return -1;
    }

    std::vector<std::string> far_l, close_l, mid_l, temp_l, image_list;
    int image_index = 0, template_index = 0, distance_index = 0;

    //Reading input datasets
    bool check = Utils::readInput(arg, far_l, close_l, mid_l, temp_l);

    //Loads initial frame and template
    cv::Mat init_frame = cv::imread(far_l[image_index]);
    cv::Mat init_temp = cv::imread(temp_l[template_index]);

    image_list = far_l;

    ScrewMatching screw_finder;
    //set frame, template and threshold
    screw_finder.setFrame(init_frame);
    screw_finder.ScrewMatching::setTemplate(init_temp);
    screw_finder.ScrewMatching::setThreshold(0.50);

    //Create windows to show output
    cv::namedWindow("Output", 1);
    cv::namedWindow("Template", 0);

    std::vector<cv::Point2f> detected_points;

    bool exit_key_pressed = false;
    while (!exit_key_pressed)
    {
        //read actual image and template from selected list
        cv::Mat ref = cv::imread(image_list[image_index]);
        cv::Mat tpl = cv::imread(temp_l[template_index]);
        if (ref.empty() || tpl.empty()){  //Checks everything is loaded fine
            std::cerr << "reference image or template image not loaded properly" << std::endl;
            return -1;
        }
        detected_points.resize(0);
        screw_finder.setFrame(ref);
        screw_finder.setTemplate(tpl);
        screw_finder.getMatch(detected_points);


        cv::Mat distance(detected_points.size(), detected_points.size(), CV_32F);
        std::vector<int> neighbours_counter(detected_points.size(), 0);
        std::vector<int> neighbour_weight(detected_points.size(), 0);

        for (int i = 0 ; i < detected_points.size() ; ++i)
        {
            for (int j = 0; j < detected_points.size(); ++j) //calculate number of neighbor within radius for i-th point
            {
                distance.at<float>(i, j) = norm(detected_points[i] - detected_points[j]);
                if ((distance.at<float>(i, j) < RADIUS) && (distance.at<float>(i, j) > 0)) //0 can set to a higher level to reject very close match?
                {
                    neighbours_counter[i]++;
                }
            }
            /*
            //uncomment to see radius on image
            if (neighbours_counter[i] > 4)
            {
                cv::circle(ref, detected_points[i], 2, CV_RGB(0, 255, 0), 2);
                cv::circle(ref, detected_points[i], RADIUS, CV_RGB(255, 255, 255), 2);
            }
            else
                cv::circle(ref, detected_points[i], 2, CV_RGB(255, 0, 0), 2);
                */
        }

        for (int i = 0; i < detected_points.size(); ++i)
        {
            //neighbour_weight[i] = 0;
            for (int j = 0; j < detected_points.size(); ++j)
            {
                if ((distance.at<float>(i, j) < RADIUS) && (distance.at<float>(i, j) > 0))
                {
                    neighbour_weight[i] +=  neighbours_counter[j];
                }
            }

            if (neighbour_weight[i] > 5)
                cv::circle(ref, detected_points[i], 2, CV_RGB(0, 255, 0), 2);
            else
                cv::circle(ref, detected_points[i], 2, CV_RGB(255, 0, 0), 2);
        }


        cv::imshow("Output", ref);
        cv::imshow("Template", tpl);

        //Checks what key has been pressed
        char c = (char)cv::waitKey();

        if ( c == 'q' || c == 27) //escape
        {
            exit_key_pressed = true;
        }

        if ( c == 'S' || c == -74) //right
        {
            //Next image
            if (image_index < image_list.size() - 1)
                image_index++;
        }
        if ( c == 'Q' || c == -76)  //left
        {
            //previous image
            if (image_index > 0)
                image_index--;
        }
        if ( c == 'R' || c == -72)  //up
        {
            //next template
            if (template_index < temp_l.size() - 1)
                template_index++;
        }
        if ( c == 'T' || c == -78)  //down
        {
            //previous template
            if (template_index > 0)
                template_index--;
        }
        if ( (c == -85 || c == '+') && distance_index < 2)  //Use closer image set
        {
            distance_index++;
        }
        if ( (c == -83 || c == '-' ) && distance_index > 0)  //Use farther image set
        {
            distance_index--;
        }

        if (distance_index == 0)
            image_list = far_l;
        if (distance_index == 1)
            image_list = mid_l;
        if (distance_index == 2)
            image_list = close_l;

    } //end while keypressed

    return 0;

} //end main


