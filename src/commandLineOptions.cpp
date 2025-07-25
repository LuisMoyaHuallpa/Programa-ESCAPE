#include "commandLineOptions.h"
#include "dictionary.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
commandLineOptions* commandLineOptions::commandLineOptionsInstance = nullptr;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
commandLineOptions::commandLineOptions() {
}

commandLineOptions* commandLineOptions::get() {
  /* si aun no existe crea la unica instancia de dictionario*/
  if (!commandLineOptionsInstance) {
    commandLineOptionsInstance =  new commandLineOptions();
  }
  return commandLineOptionsInstance;
}


void commandLineOptions::printUsage() {
    std::cout
      << "Usage: sarsa [OPTIONS]\n"
      << "options:\n"
      << "  -p, --pythonOption <in/out>      modo python (import/export)\n"
      << "  -s, --stateMatrixFile <file>     archivo stateMatrix de la version python\n"
      << "  -h, --help                       muestra esta ayuda\n"
      << std::endl;
    std::exit(0);
}

void commandLineOptions::commandLineOptions::parse(int argc, char* argv[]) {
    static struct option longOpts[] = {
        {"input",            required_argument, nullptr, 'i'},
        {"pythonOption",     required_argument, nullptr, 'p'},
        {"stateMatrixFile",  required_argument, nullptr, 's'},
        {"output",           required_argument, nullptr, 'o'},
        {"help",             no_argument,       nullptr, 'h'},
        {nullptr,             0,                 nullptr,  0 }
    };

    int opt;
    int idx = 0;
    const char* optStr = "i:p:s:o:h";
    bool pythonOption_, stateMatrixFile_;
    std::string pythonOptionValue, stateMatrixFileValue;
    
    while ((opt = getopt_long(argc, argv, optStr, longOpts, &idx)) != -1) {
      switch (opt) {
      case 'i':
	input_           = optarg;
	break;
      case 'p':
	pythonOption_ = true;
	pythonOptionValue = optarg;
	break;
      case 's':
	stateMatrixFile_ = true;
	stateMatrixFileValue = optarg;
	break;
      case 'o':
	output_          = optarg;
	break;
      case 'h':
	printUsage();
	return;
      case '?':
      default:
	printUsage();
	return;
      }
    }
    if (pythonOption_ and stateMatrixFile_) {
      dictionary::get()->getControlDict()["computationContinued"] = true;
      dictionary::get()->getControlDict()["pythonVersion"] = true;
      dictionary::get()->getControlDict()["pythonOption"] = pythonOptionValue;
      dictionary::get()->getControlDict()["previousComputationFile"] = stateMatrixFileValue;
    }
    else if (pythonOption_ and !stateMatrixFile_) {
      std::cerr << "Error: la opción -p/--python necesita la opcion -s/ --stateMatrixFile\n";
        printUsage();
	return;
    }
}
