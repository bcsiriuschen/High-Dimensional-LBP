#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cv.h>
#include <highgui.h>

#include "ArgumentParser.h"
#include "FaceDetector.h"
#include "LBPFeatureExtractor.h"
#include "FaceNormalizer.h"
#include "sirius_util.h"
#include "FaceAlignment.h"
#include "XXDescriptor.h"

using namespace std;
using namespace cv;

const int notFace = 0.5;
const vector<int>scales = {300, 212, 150, 106, 75};
const int patchSize = 10;
const int gridNumX = 4;
const int gridNumY = 4;
const int lbpDim = 59;
const int landmarkNum = 16;
const double eyeDistanceX = 2;
const double eyeDistanceUp = 1.5;
const double eyeDistanceDown = 2.5;
const int totalDim = scales.size()*gridNumX*gridNumY*lbpDim*landmarkNum;
const map<string, string> defaultArguments = {{"-m", "../data/"}, {"-o", "./"}, {"-d", "0"}};

int main(int argc, const char **argv)
{
   const string usage = "Usage: extract-lbp [-m model_dir -o output_dir] input_images\n";
   ArgumentParser argParser(argc, argv, usage, defaultArguments);
   vector<string> inputList = argParser.getInputList();
   if (inputList.size() == 0) {
      argParser.printUsage();
      return 0;
   }

   const int DEBUG = atoi(argParser.getArgument("-d").c_str());
   LBPFeatureExtractor lbpFeatureExtractor(scales, patchSize, gridNumX, gridNumY, true);
   string detectionModel(argParser.getArgument("-m") + "/DetectionModel-v1.5.yml");
   string trackingModel(argParser.getArgument("-m") + "TrackingModel-v1.10.yml");
   INTRAFACE::XXDescriptor xxd(4);
   INTRAFACE::FaceAlignment *fa;
   fa = new INTRAFACE::FaceAlignment(detectionModel, trackingModel, &xxd);
   if (!fa->Initialized()) {
      cerr << "FaceAlignmentDetect cannot be initialized." << endl;
      return -1;
   }
   int errorCount = 0;
   for(int i=0; i<inputList.size(); i++) {
      if(DEBUG) {
         printf("%s\n", inputList[i].c_str());
      }
      Mat image = imread(inputList[i], CV_LOAD_IMAGE_COLOR);
      Mat landmarks;
      float score;
      if (image.empty()) {
         continue;
      }
      Rect face(image.rows/4, image.cols/4, image.rows/2, image.cols/2);
      if(DEBUG) {
         Mat out = image;
         imwrite("out1.jpg", out);
         out.release();
      }
      vector< pair<double, double> > points;
      if (fa->Detect(image,face,landmarks,score) == INTRAFACE::IF_OK)
      {
         
         if (score <= notFace){
            errorCount++;
            printf("Landmark Error: %s\n", inputList[i].c_str());
            image.release();
            continue;
         }
         pair<double, double>point;
         //Left and Right eye center
         point.first = 0.5*(landmarks.at<float>(0,19) + landmarks.at<float>(0,22));
         point.second = 0.5*(landmarks.at<float>(1,19) + landmarks.at<float>(1,22));
         points.push_back(point);
         point.first = 0.5*(landmarks.at<float>(0,25) + landmarks.at<float>(0,28));
         point.second = 0.5*(landmarks.at<float>(1,25) + landmarks.at<float>(1,28));
         points.push_back(point);
         const int landmarkPosition[] = {0, 4, 5, 9, 19, 22, 25, 28, 13, 14, 18, 31, 34, 37}; 
         for(int i = 0; i<landmarkNum - 2; i++){
            point.first = landmarks.at<float>(0,landmarkPosition[i]);
            point.second = landmarks.at<float>(1,landmarkPosition[i]);
            points.push_back(point);
         }
         if(DEBUG) {
           for(int j=0; j<points.size(); j++)
               circle(image, Point(int(points[j].first), int(points[j].second)), 2, Scalar(0,0,255), CV_FILLED);
            imwrite("out2.jpg", image);
         }
      }else
      {
         errorCount++;
         printf("Landmark Error: %s\n", inputList[i].c_str());
         image.release();
         continue;
      }
      int *feature = new int[totalDim];
      Mat faceImage;
      vector< pair<double, double> > newPoints;
      FaceNormalizer faceNormalizer(eyeDistanceX, eyeDistanceUp, eyeDistanceDown);
      if (faceNormalizer.normalize(image, points, faceImage, newPoints)) {
         string outName = argParser.getArgument("-o") + baseName(inputList[i],false) + string(".lbp");
         ofstream flbp(outName.c_str());
         lbpFeatureExtractor.extractAt(faceImage, newPoints, feature);
         for(int j=0; j<totalDim; j++) {
            flbp<<feature[j]<<' ';
         }
         if(DEBUG) {
            imwrite("out3.jpg", faceImage);
         }
         flbp<<'\n';
         flbp.close();
      }
      faceImage.release();
      points.clear();
      newPoints.clear();
      image.release();
      delete feature;
      printProgress(i, inputList.size());
   }
   printProgress(inputList.size(), inputList.size());
   printf("Error: %d\n", errorCount);
   return 0;
}
