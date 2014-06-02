#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cv.h>
#include <highgui.h>

#include "ArgumentParser.h"
#include "FaceDetector.h"
#include "sirius_util.h"
using namespace std;
using namespace cv;

const int DEBUG = 0;
const map<string, string> defaultArguments = {{"-m", "../data/fdetector_model.dat"}, {"-s", "250"}, {"-o", "./"}, {"-l", "100"}};

int main(int argc, const char **argv)
{
   const string usage = "Usage: face-detection [-m model_file -o output_dir -s output_scale -l min_size] input_images\n";
   ArgumentParser argParser(argc, argv, usage, defaultArguments);
   const int scale = stoi(argParser.getArgument("-s"));
   const int minSize = stoi(argParser.getArgument("-l"));
   vector<string> inputList = argParser.getInputList();
   if (inputList.size() == 0) {
      argParser.printUsage();
      return 0;
   }

   FaceDetector faceDetector(argParser.getArgument("-m"));
   vector<Rect> outputFaces;
   int derrorCount = 0;
   clock_t start = clock();
   for(int i=0; i<inputList.size(); i++) {
      if(DEBUG) {
         printf("%s\n", inputList[i].c_str());
      }
      Mat image = imread(inputList[i], CV_LOAD_IMAGE_COLOR);
      if (image.empty()) {
         derrorCount++;
         continue;
      }
      faceDetector.detect(image, outputFaces, Size(minSize, minSize));
      if(outputFaces.size() == 0) {
         derrorCount++;
         image.release();
         continue;
      }
      Rect largestFace(0,0,0,0);
      for( vector<Rect>::const_iterator r = outputFaces.begin(); r != outputFaces.end(); r++) {
         if (r->width > largestFace.width)
            largestFace = *r;
         if(DEBUG) {
            printf("%d %d %d %d\n", r->x, r->y, r->width, r->height);
         }
      }
      copyMakeBorder(image, image, int(largestFace.height), int(largestFace.height),
         int(largestFace.width), int(largestFace.width), BORDER_CONSTANT, Scalar(0));
      Mat faceImage = image(Rect(largestFace.x + largestFace.width/2, largestFace.y + largestFace.height/2, 
         largestFace.width*2, largestFace.height*2));
      resize(faceImage, faceImage, Size(scale, scale));
      string outName = argParser.getArgument("-o") + baseName(inputList[i],true);
      imwrite(outName, faceImage);
      faceImage.release();
      outputFaces.clear();
      image.release();
      if(!argParser.hasArgument("-q"))
         printProgress(i, inputList.size());
   }
   double sec = double(clock() - start)/CLOCKS_PER_SEC;
   if(!argParser.hasArgument("-q"))
      printProgress(inputList.size(), inputList.size());
   if(!argParser.hasArgument("-q"))
      printf("miss: %d total: %d time: %lf avg: %lf\n",  derrorCount, inputList.size(), sec,
         sec/inputList.size());
   return 0;
}
