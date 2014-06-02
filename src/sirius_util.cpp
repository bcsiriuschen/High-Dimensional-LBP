#include <cstdio>
#include <string>
#include <algorithm>

#include "sirius_util.h"

using namespace std;

void printProgress(int now, int total)
{
   printf("\r%3d%(%d/%d)", int(double(now)/total*100), now, total);
   if(now == total)
      printf("Done!\n");
   fflush(stdout);
}

string baseName(const string fullName, bool ext)
{
   int head = int(fullName.find_last_of('/'))+1;
   if(ext)
      return fullName.substr(head, fullName.size() - head);
   else
      return fullName.substr(head, fullName.rfind('.') - head);
}
