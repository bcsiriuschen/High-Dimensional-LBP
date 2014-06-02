#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class ArgumentParser {

public:
   ArgumentParser(const int argc, const char *argv[], const string& usage, const map<string, string> defaultArguments);
   void parseArgument (const int argc, const char *argv[]);
   string getArgument(const string& in);
   bool hasArgument(const string& in);
   vector<string> getInputList();
   void printUsage();

private:
   map<string, string> arguments;
   vector<string> inputList;
   string usage;
};
#endif
