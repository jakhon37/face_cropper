
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>
#include <iostream>
#include "utils.h"

int main() {

    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    cv::Mat inputImg = cv::imread("assets/d.jpg");
    if (inputImg.empty()) {
        std::cerr << "Error: Image not loaded. Check file path or file format!" << std::endl;
    }

    dlib::cv_image<dlib::bgr_pixel> dlibImg(inputImg);

    std::vector<dlib::rectangle> faces = detector(dlibImg);

    for (size_t i = 0; i<faces.size(); ++i) {
        dlib::rectangle face = faces[i];
        cv::Rect cvRect(face.left(), face.top(), face.width(), face.height());

        cv::Mat croppedFace = inputImg(cvRect);
        std::string img_path = "assets/out/";
        // if (!std::filesystem::exists(img_path)) {
        //     std::filesystem::create_directories(img_path);
        // }
        utils::createDirectory(img_path);
        std::string impath = img_path+"face_"+std::to_string(i) + ".jpg";
        std::cout << "face: "+ impath << std::endl;
        cv::imwrite(impath, croppedFace);

    }
return 0;
}

