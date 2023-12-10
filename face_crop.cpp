
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include "utils.h"
#include <filesystem>
namespace fs=std::filesystem;


class CropFace {
private:

    std::string root_path = ".";
    std::string im_path = root_path + "assets";

    std::string imgOut_path = "assets/out/";

    dlib::frontal_face_detector detector;

    void initializerDetector() {
        detector=dlib::get_frontal_face_detector();
    }

public:
    CropFace() {

        utils::createDirectory(imgOut_path);

        initializerDetector();

    }




    void detect_face(const std::string& img_path, const std::string& out_path) {
        cv::Mat inputImg = cv::imread(img_path);
        if (inputImg.empty()) {
            std::cerr << "Error: Image not loaded. Check file path or file format!" << std::endl;
            return;
        }

        
        fs::path filePath(img_path);
        std::string baseName = filePath.filename().string();
        std::string imgName = filePath.stem().string();

        dlib::cv_image<dlib::bgr_pixel> dlibImg(inputImg);

        std::vector<dlib::rectangle> faces = detector(dlibImg);

        for (size_t i = 0; i<faces.size(); ++i) {
            dlib::rectangle face = faces[i];
            cv::Rect cvRect(face.left(), face.top(), face.width(), face.height());

            cv::Mat croppedFace = inputImg(cvRect);

            std::string outpath = out_path + "face_" + imgName + std::to_string(i) + ".jpg";
            std::cout << "face: "+ outpath << std::endl;
            cv::imwrite(outpath, croppedFace);

        }
    }

    std::string getLastDirectoryName(const std::string& fullPath) {
        fs::path pathObj(fullPath);

        // Remove the trailing slash if it exists
        if (pathObj.has_filename() && *fullPath.rbegin() == '/') {
            pathObj.remove_filename(); // This handles the trailing slash
        }

        // Check if the path ends with a file
        if (!pathObj.empty() && fs::is_regular_file(pathObj)) {
            // Get the parent directory
            pathObj = pathObj.parent_path();
        }

        // Now pathObj should point to a directory, get the last directory name
        if (!pathObj.empty()) {
            return pathObj.filename().string();
        } else {
            return std::string(); // Empty string if path is empty
        }
    }



    std::vector<std::string> listFilesInDirectory(const std::string& directoryPath) {
        std::vector<std::string> files;
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            files.push_back(entry.path().string());
        }
        return files;
        }

    void process_folder(const std::string& folderPath) {
        std::cout << "Contents of directory: " << folderPath << std::endl;

        std::vector<std::string> files = listFilesInDirectory(folderPath); 

        // std::string lastFolderName = getLastDirectoryName(folderPath);
        // imgOut_path = imgOut_path+"/"+lastFolderName+"/";
        // std::cout << "lastFolderName: " << lastFolderName <<std::endl;

        utils::createDirectory(imgOut_path);

        for (const auto& file : files) {
            if (fs::is_regular_file(file)) {
                std::cout << "Processing file: " << file << std::endl;
                detect_face(file, imgOut_path); // Make sure detect_face handles the output path internally
            } else {
                std::cout << "Invalid file type: " << file << std::endl;
            }
        }
    }



};


int main() {
    CropFace cropface;
    std::string imgdir = "assets/";
    // std::string imgpath = "assets/dd.jpg";

    std::string imgpath;
    std::cout <<"input path: "; //<< std::endl;
    std::cin >>  imgpath;
    // cropface.detect_face(imgpath);
    cropface.process_folder(imgdir);


    
return 0;
}

