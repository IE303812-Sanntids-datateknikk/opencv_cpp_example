
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"

#include <iostream>
#include <thread>

#include "detect_face.hpp"

using namespace cv;

int main() {

    namedWindow("Display Image", WINDOW_AUTOSIZE);

    CascadeClassifier cascade, nestedCascade;
    std::string cascadeName("../cascades/haarcascades/haarcascade_frontalface_alt.xml");
    std::string nestedCascadeName("../cascades/haarcascades/haarcascade_eye_tree_eyeglasses.xml");

    if (!nestedCascade.load(nestedCascadeName))
        std::cerr << "WARNING: Could not load classifier cascade for nested objects" << std::endl;
    if (!cascade.load(cascadeName)) {
        std::cerr << "ERROR: Could not load classifier cascade" << std::endl;
        return -1;
    }

    bool stop = false;
    std::thread t([&stop] {
      waitKey(0);
      stop = true;
    });

    Mat image;
    VideoCapture capture(0);

    while (!stop && capture.isOpened()) {
        capture >> image;
        detect(image, cascade, nestedCascade);
        imshow("Display Image", image);
    }

    t.join();
}