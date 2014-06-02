#include <map>
#include <vector>
#include <iostream>
#include "ArgumentParser.h"

using namespace std;

ArgumentParser::ArgumentParser(const int argc, const char *argv[], const string& msg, const map<string, string> defaultArguments)
{
	parseArgument(argc, argv);
	usage = msg;
   for(auto iter = defaultArguments.cbegin(); iter != defaultArguments.cend(); iter++) {
      if (arguments.find(iter->first) == arguments.end())
         arguments[iter->first] = iter->second;
   }
}

void ArgumentParser::parseArgument (const int argc, const char *argv[])
{
	arguments.clear();
	inputList.clear();
	for (int i=1 ;i<argc ;i++)
	{
		if (argv[i][0] == '-' && i != argc - 1 && argv[i+1][0] != '-')
		{
			string index = argv[i];
			arguments[index] = argv[++i];
		}
		else if((argv[i][0] == '-' && i == argc - 1) || (argv[i][0] == '-' && argv[i+1][0] == '-'))
		{
			string index = argv[i];
			arguments[index] = "ON";
		}else
			inputList.push_back (argv[i]);
	}
}
bool ArgumentParser::hasArgument(const string& in)
{
   if(arguments.find(in) !=arguments.end())
      return true;
   else
      return false;
}

string ArgumentParser::getArgument(const string& in)
{
	if(arguments.find(in) != arguments.end())
		return arguments[in];
	else
		return "";
}

vector<string> ArgumentParser::getInputList()
{
	return inputList;
}

void ArgumentParser::printUsage()
{
	cerr<<usage;
}
