#include <string>
#include <vector>

#include <cv.h>
#include <highgui.h>

#include "FaceDetector.h"

using namespace std;
using namespace cv;

FaceDetector::FaceDetector(const string& modelFileName) {
   setDetector(modelFileName);
}

bool FaceDetector::setDetector(const string& modelFileName) {
   return this->cascade.load(modelFileName);
}

vector<Rect>& FaceDetector::detect(const Mat& inputImage, vector<Rect>& outputFaces, Size minFaceSize, float scaleFactor, int minNeighbor) {
   outputFaces.clear();
   Mat processedImage;
   if (inputImage.channels() == 3) {
      cvtColor(inputImage, processedImage, CV_BGR2GRAY );
   }
   else {
      processedImage = inputImage;
   }
   equalizeHist(processedImage, processedImage);
   cascade.detectMultiScale(processedImage, outputFaces, scaleFactor, minNeighbor, CV_HAAR_DO_CANNY_PRUNING, minFaceSize);
   return outputFaces;
}
