// =============================================================================
// Author(s): Thomas Fuller
// Project:   Module 3 - 1st Deliverable
// File:      scanner_test.cpp
// =============================================================================
// Description:
//
// =============================================================================

#include <iostream>
//#include <ifstream>
#include <cstring>
#include <cassert>
#include "Scanner.h"

using namespace lilua_interpreter_project;

bool lexeme_comp(LEXEME actual, LEXEME expected) {
    if (actual.token == expected.token) {
        return true;
    } else {
        std::cout << "Failed.\n\tAfter calling the scanner, the incorrect " <<
        "token was returned.\n\tThe expected token was: "<< expected.token <<
        ".\n\t" << "The actual token was: " << actual.token << ".\n";
        return false;
    }
}

int main() {
    std::cout << "Keyword Binary Search Test" << '\n';
    int val;
    std::cout << "Searching for the keyword \"repeat\"...";
    val = keyword_bin_search("repeat");
    if (val == REPEAT_KEYWORD) {
        std::cout << "SUCCESS!!!" << '\n';
    } else {
        std::cout << "failed. It returned: " << val << '\n';
    }
    std::cout << "Searching for the keyword \"do\"...";
    val = keyword_bin_search("do");
    if (val == DO_KEYWORD) {
        std::cout << "SUCCESS!!!" << '\n';
    } else {
        std::cout << "failed. It returned: " << val << '\n';
    }
    std::cout << "Searching for the keyword \"while\"...";
    val = keyword_bin_search("while");
    if (val == WHILE_KEYWORD) {
        std::cout << "SUCCESS!!!" << '\n';
    } else {
        std::cout << "failed. It returned: " << val << '\n';
    }
    std::cout << "Searching for the non-existent keyword \"notinthetable\"...";
    val = keyword_bin_search("notinthetable");
    if (val == -1) {
        std::cout << "SUCCESS!!!" << '\n';
    } else {
        std::cout << "failed. It returned: " << val << '\n';
    }


    std::cout << "\nScanner Test #1" << '\n';
  char simple[] = "build/test/res/simple.lua";
      std::cout << "Testing scanner with the file: \"" << simple << "\"...";
  Scanner myScanner(simple);
  size_t index = 0;
  const LEXEME ans1[] = {
      {FUNCTION_KEYWORD,"function"},
      {ID,"f"},
      {UNKNOWN_TOKEN,"("},
      {UNKNOWN_TOKEN,")"},
      {ID,"a"},
      {ASSIGNMENT_OPERATOR,"="},
      {LITERAL_INTEGER,"7"},
      {PRINT_KEYWORD,"print"},
      {UNKNOWN_TOKEN,"("},
      {ID,"a"},
      {UNKNOWN_TOKEN,")"},
      {ID,"b"},
      {ASSIGNMENT_OPERATOR,"="},
      {LITERAL_INTEGER,"8"},
      {PRINT_KEYWORD,"print"},
      {UNKNOWN_TOKEN,"("},
      {ID,"b"},
      {UNKNOWN_TOKEN,")"},
      {ID,"c"},
      {ASSIGNMENT_OPERATOR,"="},
      {ID,"a"},
      {MULT_OPERATOR,"*"},
      {ID,"b"},
      {PRINT_KEYWORD,"print"},
      {UNKNOWN_TOKEN,"("},
      {ID,"c"},
      {UNKNOWN_TOKEN,")"},
      {END_KEYWORD,"end"},
      {EOF_TOKEN,""}
  };

  LEXEME test;
  do {
    test = myScanner.lex();
    if (!lexeme_comp(test, ans1[index++])) {
        std::cout << "<FAILED AT INDEX: " << index << ">\n";
        return -1;
    }
  } while (test.token != -1);
  std::cout << "SUCCESS!!!" << '\n';

const LEXEME ans2[] = {
    {FUNCTION_KEYWORD,"function"},
    {ID,"f"},
    {UNKNOWN_TOKEN,"("},
    {UNKNOWN_TOKEN,")"},
    {ID,"n"},
    {ASSIGNMENT_OPERATOR,"="},
    {LITERAL_INTEGER,"8"},
    {IF_KEYWORD,"if"},
    {ID,"n"},
    {GT_OPERATOR,">"},
    {LITERAL_INTEGER,"0"},
    {THEN_KEYWORD,"then"},
    {ID,"a"},
    {ASSIGNMENT_OPERATOR,"="},
    {LITERAL_INTEGER,"0"},
    {ID,"b"},
    {ASSIGNMENT_OPERATOR,"="},
    {LITERAL_INTEGER,"1"},
    {PRINT_KEYWORD,"print"},
    {UNKNOWN_TOKEN,"("},
    {ID,"a"},
    {UNKNOWN_TOKEN,")"},
    {IF_KEYWORD,"if"},
    {ID,"n"},
    {EQ_OPERATOR,"=="},
    {LITERAL_INTEGER,"1"},
    {THEN_KEYWORD,"then"},
    {ID,"n"},
    {ASSIGNMENT_OPERATOR,"="},
    {ID,"n"},
    {SUB_OPERATOR,"-"},
    {LITERAL_INTEGER,"1"},
    {ELSE_KEYWORD,"else"},
    {PRINT_KEYWORD,"print"},
    {UNKNOWN_TOKEN,"("},
    {ID,"b"},
    {UNKNOWN_TOKEN,")"},
    {IF_KEYWORD,"if"},
    {ID,"n"},
    {EQ_OPERATOR,"=="},
    {LITERAL_INTEGER,"2"},
    {THEN_KEYWORD,"then"},
    {ID,"n"},
    {ASSIGNMENT_OPERATOR,"="},
    {ID,"n"},
    {SUB_OPERATOR,"-"},
    {LITERAL_INTEGER,"1"},
    {ELSE_KEYWORD,"else"},
    {ID,"c"},
    {ASSIGNMENT_OPERATOR,"="},
    {LITERAL_INTEGER,"0"},
    {ID,"n"},
    {ASSIGNMENT_OPERATOR,"="},
    {ID,"n"},
    {SUB_OPERATOR,"-"},
    {LITERAL_INTEGER,"2"},
    {WHILE_KEYWORD,"while"},
    {ID,"n"},
    {GT_OPERATOR,">"},
    {LITERAL_INTEGER,"0"},
    {DO_KEYWORD,"do"},
    {ID,"c"},
    {ASSIGNMENT_OPERATOR,"="},
    {ID,"a"},
    {ADD_OPERATOR,"+"},
    {ID,"b"},
    {ID,"a"},
    {ASSIGNMENT_OPERATOR,"="},
    {ID,"b"},
    {ID,"b"},
    {ASSIGNMENT_OPERATOR,"="},
    {ID,"c"},
    {PRINT_KEYWORD,"print"},
    {UNKNOWN_TOKEN,"("},
    {ID,"c"},
    {UNKNOWN_TOKEN,")"},
    {ID,"n"},
    {ASSIGNMENT_OPERATOR,"="},
    {ID,"n"},
    {SUB_OPERATOR,"-"},
    {LITERAL_INTEGER,"1"},
    {END_KEYWORD,"end"},
    {END_KEYWORD,"end"},
    {END_KEYWORD,"end"},
    {ELSE_KEYWORD,"else"},
    {PRINT_KEYWORD,"print"},
    {UNKNOWN_TOKEN,"("},
    {LITERAL_INTEGER,"0"},
    {UNKNOWN_TOKEN,")"},
    {END_KEYWORD,"end"},
    {END_KEYWORD,"end"},
    {EOF_TOKEN,"\0"}
};

std::cout << "\nScanner Test #2" << '\n';
char fibonacci[] = "build/test/res/fibonacci.lua";
    std::cout << "Testing scanner with the file: \"" << fibonacci << "\"...";
Scanner myScanner2(fibonacci);
index = 0;

do {
  test = myScanner2.lex();
  if (!lexeme_comp(test, ans2[index++])) {
      std::cout << "<FAILED AT INDEX: " << index << ">\n";
      return -1;
  }
} while (test.token != -1);
std::cout << "SUCCESS!!!" << '\n';

  return 0;
}
