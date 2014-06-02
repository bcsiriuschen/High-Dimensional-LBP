#include <string>
#include <vector>
#include <utility>

#include <cv.h>
using namespace std;
using namespace cv;

class FaceNormalizer{
public:
   FaceNormalizer(const double eyeDistanceX, const double eyeDistanceUp, const double eyeDistanceDown); 
   void setParameters(const double eyeDistanceX, const double eyeDistanceUp, const double eyeDistanceDown); 
   bool normalize(const Mat inputFaceImage, const vector< pair<double, double> > landmarks, Mat &outputFaceImage, vector< pair<double, double> > &newLandmarks); 
private:
   double eyeDistanceX;
   double eyeDistanceUp;
   double eyeDistanceDown;
};

