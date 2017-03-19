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
#include <iostream>
#include <string.h>
#include "Parser.h"

using namespace lilua_interpreter_project;

const char APP_NAME[]         = "LiLuac";
const char APP_VERSION[]      = "v0.1";
const char APP_DESCRIPTION[]  =
  "The LiLua Compiler command-line application. This application takes a LiLua \n"
  "source file and then compiles it into LiLua Bytecode that can be run on top \n"
  "of the LiLua Interpreter.";
const char APP_AUTHORS[]      = "Thomas Fuller and Teddy Mopewou";
const char APP_DATE[]         = "March 14, 2017";

const char HELP_INFORMATION[] =
  "usage: liluac [options] [source file]\n"
  "\tOptions:\n"
  "\t-v\tDisplay the current version and other information about the "
  "application.\n\t-h\tPrints the help message for the application.\n"
  "\t-c arg\tTakes in an argument that represents the directory for a LiLua "
  "source\n\t\tfile. The program will then create a new .lil file in the "
  "current \n\t\tdirectory.\n";


bool checkFlag(const char *flag, const char *val) {
  return strcmp(flag,val) == 0;
}

void display_err(const char *message) {
  std::cout << "ERROR: " << message << '\n';
}

void user_err() {
  display_err("Must include an option");
  std::cout << HELP_INFORMATION << '\n';
}

int main(int argc, char const *argv[]) {
  if (argc <= 1) {
    user_err();
    return -1;
  }

  const char* flag = argv[1];
  if (checkFlag(flag, "-v")) {
    std::cout << APP_NAME << " " << APP_VERSION << "\n\n";
    std::cout << "Authors: " << APP_AUTHORS << '\n';
    std::cout << "Last Updated: " << APP_DATE << "\n\n";
    std::cout << "Description:\n" << APP_DESCRIPTION << '\n';
  } else if (checkFlag(flag, "-h")) {
    std::cout << HELP_INFORMATION << '\n';
  } else if (checkFlag(flag, "-c")) {
    if (argc < 3) {
      display_err("No input files");
      return -1;
    } else if (argc > 3) {
      display_err("Too many files. Only one file at a time.");
      return -1;
    } else {
      const char *src = argv[2];
      Parser parser(src, "comp.lil");
      if (parser.parse()) {
        return 0;
      } else {
        return -1;
      }
    }
  } else {
    user_err();
    return -1;
  }
  return 0;
}
