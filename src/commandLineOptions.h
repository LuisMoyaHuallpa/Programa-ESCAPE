#ifndef commandLineOptions_h
#define commandLineOptions_h

#include <getopt.h>
#include <iostream>

class commandLineOptions{
 private:
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // static member
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  static commandLineOptions* commandLineOptionsInstance;

  std::string input_;           // -i, --input
  std::string pythonOption_;    // -p, --pythonOption
  std::string stateMatrixFile_; // -s, --stateMatrixFile
  std::string output_;          // -o, --output
  bool        help_ = false;    // -h, --help
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // constructor
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  commandLineOptions();

 public:
  /// Parsea argc/argv y llena los campos
  void parse(int argc, char* argv[]);
  static void printUsage();
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // static getters
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  static commandLineOptions* get();



};
#endif
