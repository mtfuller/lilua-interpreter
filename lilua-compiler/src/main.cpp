// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 3 - 1st Deliverable
// File:      Scanner.cpp
// =============================================================================
// Description:
// This file is the implementation of the scanner class.
// =============================================================================
#include <iostream>           // Console output
#include <string.h>           // strcmp
#include <string>
#include <cstdlib>            // exit()
#include <cassert>            // assert()
#include "Parser.h"           // Parser class

using namespace lilua_interpreter_project;

// =============================================================================
// String Constants For Console Application
// =============================================================================

const char APP_NAME[]         = "LiLuac";
const char APP_VERSION[]      = "v1.0";

const char APP_DESCRIPTION[]  =
"The LiLua Compiler command-line application. This application takes a LiLua \n"
"source file and then compiles it into LiLua Bytecode that can be run on top \n"
"of the LiLua Interpreter.";

const char APP_AUTHORS[]      = "Thomas Fuller and Teddy Mopewou";
const char APP_DATE[]         = "March 19, 2017";

const char HELP_INFORMATION[] =
"usage: liluac [options] [source file]\n"
"\tOptions:\n"
"\t-v\t\tDisplay the current version and other information about the "
      "application.\n"
"\t-h\t\tPrints the help message for the application.\n"
"\t-c arg1 [arg2]\tTakes in two arguments. The first is a file path for the "
          "LiLua source\n\t\t\tfile. The program will then create a new .lil "
          "file in the current \n\t\t\tdirectory.\n";

// =============================================================================
// bool checkFlag(const char *flag, const char *val)
// Returns true if flag string matches val string
// =============================================================================
bool checkFlag(const char *flag, const char *val) {
  return strcmp(flag,val) == 0;
}

// =============================================================================
// void display_err(const char *message)
// Outputs an error message to the console. Prints "ERROR: " followed by the
// given message.
// =============================================================================
void display_err(const char *message) {
  std::cout << "ERROR: " << message << '\n';
}

// =============================================================================
// void user_version()
// Prints version information to the console
// =============================================================================
void user_version() {
  std::cout << APP_NAME << " " << APP_VERSION << "\n\n";
  std::cout << "Authors: " << APP_AUTHORS << '\n';
  std::cout << "Last Updated: " << APP_DATE << "\n\n";
  std::cout << "Description:\n" << APP_DESCRIPTION << '\n';
}

// =============================================================================
// void user_help()
// Prints help information to the console
// =============================================================================
void user_help() {
  std::cout << HELP_INFORMATION << '\n';
}

// =============================================================================
// void user_help()
// Prints a generic user error message, and then prints out help information to
// the console
// =============================================================================
void user_err() {
  display_err("Must include an option");
  user_help();
}

// =============================================================================
// void user_help()
// Prints a generic user error message, and then prints out help information to
// the console
// =============================================================================
void get_output_path(const std::string& src, std::string& output) {
  const static char lil[] = ".lil";

  // Gets the index of the last "." in the string
  size_t ext = src.find_last_of(".");
  assert(ext != std::string::npos);

  // sets output equal to the path of the src and file name, and then adds the
  // ".lil" extension.
  output = src.substr(0,ext).append(lil).c_str();
}

int main(int argc, char const *argv[]) {
  // Checks if the user didn't enter enough arguments
  if (argc <= 1) {
    user_err();
    return -1;
  }

  // Checks which flag the user chose
  const char* flag = argv[1];
  if (checkFlag(flag, "-v")) {
    // Displays version information
    user_version();
    exit (EXIT_SUCCESS);
  } else if (checkFlag(flag, "-h")) {
    // Displays help information
    user_help();
    exit (EXIT_SUCCESS);
  } else if (checkFlag(flag, "-c")) {
    // Checks to make sure the user entered the right number of arguments
    if (argc < 3) {
      // Did not include source file path
      display_err("No input files");
      exit (EXIT_FAILURE);
    } else if (argc > 3) {
      // Gave too many arguments
      display_err("Too many files. Only one file at a time.");
      exit (EXIT_FAILURE);
    } else {
      // Ready to run the Parser

      // Initialize source and output paths
      std::string src(argv[2]);
      std::string output_path;
      get_output_path(src,output_path);

      // Create parser
      Parser parser(src.c_str(), output_path.c_str());

      // Runs the parser
      if (parser.parse()) {
        // Parsing was successful
        exit (EXIT_SUCCESS);
      } else {
        // Encountered a parsing error
        display_err("Could not parse specified file.");
        exit (EXIT_FAILURE);
      }
    }
  } else {
    // User gave some unknown flag
    user_err();
    exit (EXIT_FAILURE);
  }
  return 0;
}
