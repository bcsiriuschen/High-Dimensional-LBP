#include <string>
#include <vector>

#include <cv.h>
using namespace std;
using namespace cv;

class FaceDetector{
public:
   FaceDetector(const string& modelFileName);
   bool setDetector(const string& modelFileName);
   vector<Rect>& detect(const Mat& inputImage, vector<Rect> &outputFaces, Size minFaceSize=Size(30,30));
   //bool detectAndSave(const Mat& inputImage, const string& outputFileName);
private:
   CascadeClassifier cascade;
};
