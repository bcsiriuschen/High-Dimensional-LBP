#include <string>
#include <vector>
#include <utility>

#include <cv.h>
using namespace std;
using namespace cv;

class LBPFeatureExtractor{
public:
   LBPFeatureExtractor(const vector<int> scales, const int patchSize, const int numCellX, const int numCellY, const bool uniform);
   void setParameters(const vector<int> scales, const int patchSize, const int numCellX, const int numCellY, const bool uniform);
   int* extractAt(const Mat &image, const vector< pair<double, double> >points, int *outputFeature);
   void lbpImage(const Mat &image, Mat &lbpImage);
private:
   int lbpCode (unsigned char seq[9]);
   int* lbpHist(Mat &img, int* lbpHist);
   bool uniform;
   vector<int> scale;
   int patchSize;
   int numCellX;
   int numCellY;
   int mapping[256] = {0, 1, 2, 3, 4, 58, 5, 6, 7, 58, 58, 58, 8, 58, 9, 10, 11, 58, 58, 58, 58, 58, 58, 58, 12, 58, 58, 58, 13, 58, 14, 15, 16, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 17, 58, 58, 58, 58, 58, 58, 58, 18, 58, 58, 58, 19, 58, 20, 21, 22, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 23, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 24, 58, 58, 58, 58, 58, 58, 58, 25, 58, 58, 58, 26, 58, 27, 28, 29, 30, 58, 31, 58, 58, 58, 32, 58, 58, 58, 58, 58, 58, 58, 33, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 34, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 35, 36, 37, 58, 38, 58, 58, 58, 39, 58, 58, 58, 58, 58, 58, 58, 40, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 41, 42, 43, 58, 44, 58, 58, 58, 45, 58, 58, 58, 58, 58, 58, 58, 46, 47, 48, 58, 49, 58, 58, 58, 50, 51, 52, 58, 53, 54, 55, 56, 57};
};

