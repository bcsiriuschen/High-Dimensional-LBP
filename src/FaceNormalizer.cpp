#include <string>
#include <iostream>
#include <vector>
#include <utility>

#include <cv.h>
#include "FaceNormalizer.h"
using namespace std;
using namespace cv;

FaceNormalizer::FaceNormalizer(const double eyeDistanceX, const double eyeDistanceUp, const double eyeDistanceDown)
{
   setParameters(eyeDistanceX, eyeDistanceUp, eyeDistanceDown);
}
void FaceNormalizer::setParameters(const double eyeDistanceX, const double eyeDistanceUp, const double eyeDistanceDown)
{
   this->eyeDistanceX = eyeDistanceX;
   this->eyeDistanceDown = eyeDistanceDown;
   this->eyeDistanceUp = eyeDistanceUp;
}

bool FaceNormalizer::normalize(const Mat inputFaceImage, const vector< pair<double, double> > landmarks, Mat &outputFaceImage, vector< pair<double, double> > &newLandmarks)
{
   double eyeXdis = landmarks[1].first-landmarks[0].first;
   double eyeYdis = landmarks[1].second-landmarks[0].second;
   double angle = atan(eyeYdis/eyeXdis);
   double degree = angle*180/CV_PI;

   //rotate image and corresponding points to make the eyes horizontal even
   for(int i=0; i<landmarks.size(); i++) {
      pair<double,double> pt;
      pt.first = (landmarks[i].first - landmarks[0].first)*cos(angle) + (landmarks[i].second - landmarks[0].second)*sin(angle)\
         + landmarks[0].first;
      pt.second = (landmarks[i].second - landmarks[0].second)*cos(angle) - (landmarks[i].first - landmarks[0].first)*sin(angle)\
         + landmarks[0].second;
      newLandmarks.push_back(pt);
   }
   Mat rotMat = getRotationMatrix2D(Point2f(landmarks[0].first,landmarks[0].second), degree, 1.0);
   //printf("%d %d\n", inputFaceImage.cols, inputFaceImage.rows);
   warpAffine(inputFaceImage, outputFaceImage, rotMat, Size(inputFaceImage.cols, inputFaceImage.rows));

   //crop face region from the image
   double eyeDist = abs((newLandmarks[0].first - newLandmarks[1].first));
   double eyeCenterX = (newLandmarks[0].first + newLandmarks[1].first)/2 + int(eyeDistanceX*eyeDist);
   double eyeCenterY = (newLandmarks[0].second + newLandmarks[1].second)/2 + int(eyeDistanceUp*eyeDist);
   int leftbound = int((eyeCenterX - eyeDistanceX*eyeDist));
   int rightbound = int((eyeCenterX + eyeDistanceX*eyeDist));
   int topbound = int((eyeCenterY - eyeDistanceUp*eyeDist));
   int bottombound = int((eyeCenterY + eyeDistanceDown*eyeDist));
   copyMakeBorder(outputFaceImage, outputFaceImage, int(eyeDistanceUp*eyeDist), int(eyeDistanceDown*eyeDist),
      int(eyeDistanceX*eyeDist), int(eyeDistanceX*eyeDist), BORDER_CONSTANT, Scalar(0));
/*
   if (leftbound < 0 || topbound < 0 || rightbound >=outputFaceImage.cols || bottombound >=outputFaceImage.rows) {
      cerr<<"Error: face out of bound!\n";
      return false;
   }
   */
   for(int i=0; i<newLandmarks.size(); i++)
   {  
      newLandmarks[i].first = newLandmarks[i].first - leftbound + int(eyeDistanceX*eyeDist);
      newLandmarks[i].second =  newLandmarks[i].second - topbound + int(eyeDistanceUp*eyeDist);
   }
   outputFaceImage = outputFaceImage(Rect(leftbound, topbound, rightbound-leftbound, bottombound-topbound));      
   //outputFaceImage = outputFaceImage;//(Rect(leftbound, topbound, rightbound-leftbound, bottombound-topbound));      
   return true;
}
