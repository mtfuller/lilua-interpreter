// =============================================================================
// Author(s): Thomas Fuller
// Project:   Module 3 - 1st Deliverable
// File:      scanner_test.cpp
// =============================================================================
// Description:
//
// =============================================================================

#include <iostream>
#include <cstring>
#include <string>
#include "Scanner.h"

#define TABLE_WIDTH   42

using namespace lilua_interpreter_project;

const std::string token_arr[] = {
  "EOF","UNKNOWN_TOKEN","LEFT_PAREN_TOKEN","RIGHT_PAREN_TOKEN","ID",
  "LITERAL_INTEGER","ASSIGNMENT_OPERATOR","LE_OPERATOR","LT_OPERATOR",
  "GE_OPERATOR","GT_OPERATOR","EQ_OPERATOR","NE_OPERATOR","ADD_OPERATOR",
  "SUB_OPERATOR","MULT_OPERATOR","DIV_OPERATOR","NULL_KEYWORD","DO_KEYWORD",
  "ELSE_KEYWORD","END_KEYWORD","FUNCTION_KEYWORD","IF_KEYWORD","PRINT_KEYWORD",
  "REPEAT_KEYWORD","THEN_KEYWORD","UNTIL_KEYWORD","WHILE_KEYWORD"
};

int get_token_index(token_type token_code) {
  return token_code + 1;
}

bool lexeme_comp(LEXEME actual, LEXEME expected) {
    if (actual.token == expected.token) {
        char substring[11];
        memcpy(substring, actual.lex, 10);
        printf("| %-20s | %-15s |\n", token_arr[get_token_index(actual.token)].c_str(), substring);
        return true;
    } else {
        std::cout << "Failed.\n\tAfter calling the scanner, the incorrect " <<
        "token was returned.\n\tThe expected token was: "<< token_arr[get_token_index(expected.token)] <<
        ".\n\t" << "The actual token was: " << token_arr[get_token_index(actual.token)] << ".\n";
        return false;
    }
}

bool keyword_test(const char* key, int expected) {
    std::cout << "Searching for the keyword \"" << key << "\"...";
    int val = keyword_bin_search(key);
    if (val == expected) {
        std::cout << "SUCCESS!!!" << '\n';
        return true;
    } else if (val == -1) {
        std::cout << "failed. Keyword does not exist." << '\n';
        return false;
    } else {
        std::cout << "failed. It returned: " << token_arr[get_token_index(val)] << '\n';
        return false;
    }
}

bool scanner_test(const char* file, const LEXEME* ans) {
    size_t index = 0;
    std::cout << "Testing scanner with the file: \"" << file << "\"...\n";
    Scanner myScanner(file);
    LEXEME test;
    for (int i = 0; i < TABLE_WIDTH; i++) printf("=");
    printf("\n| %-20s | %-15s |\n", "TOKEN CODE", "LEXEME");
    for (int i = 0; i < TABLE_WIDTH; i++) printf("=");
    printf("\n");
    do {
        test = myScanner.lex();
        if (!lexeme_comp(test, ans[index++])) {
            printf("\n");
            std::cout << "LEXEME: " << test.lex << "\n";
            std::cout << "<FAILED AT INDEX: " << index << ">\n";
            return false;
        }
    } while (test.token != -1);
    for (int i = 0; i < TABLE_WIDTH; i++) printf("=");
    std::cout << "\nSUCCESS!!!" << '\n';
    return true;
}

// =============================================================================
// Test 1 - simple.lua
// =============================================================================
bool test1() {
    const char simple[] = "build/test/res/simple.lua";
    const LEXEME ans1[] = {
        {FUNCTION_KEYWORD,"function"},
        {ID,"f"},
        {LEFT_PAREN_TOKEN,"("},
        {RIGHT_PAREN_TOKEN,")"},
        {ID,"a"},
        {ASSIGNMENT_OPERATOR,"="},
        {LITERAL_INTEGER,"7"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"a"},
        {RIGHT_PAREN_TOKEN,")"},
        {ID,"b"},
        {ASSIGNMENT_OPERATOR,"="},
        {LITERAL_INTEGER,"8"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"b"},
        {RIGHT_PAREN_TOKEN,")"},
        {ID,"c"},
        {ASSIGNMENT_OPERATOR,"="},
        {ID,"a"},
        {MULT_OPERATOR,"*"},
        {ID,"b"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"c"},
        {RIGHT_PAREN_TOKEN,")"},
        {END_KEYWORD,"end"},
        {EOF_TOKEN,""}
    };
    std::cout << "\nScanner Test #1" << '\n';
    return scanner_test(simple, ans1);
}

// =============================================================================
// Test 2 - fibonacci.lua
// =============================================================================
bool test2() {
    char fibonacci[] = "build/test/res/fibonacci.lua";
    const LEXEME ans2[] = {
        {FUNCTION_KEYWORD,"function"},
        {ID,"f"},
        {LEFT_PAREN_TOKEN,"("},
        {RIGHT_PAREN_TOKEN,")"},
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
        {LEFT_PAREN_TOKEN,"("},
        {ID,"a"},
        {RIGHT_PAREN_TOKEN,")"},
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
        {LEFT_PAREN_TOKEN,"("},
        {ID,"b"},
        {RIGHT_PAREN_TOKEN,")"},
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
        {LEFT_PAREN_TOKEN,"("},
        {ID,"c"},
        {RIGHT_PAREN_TOKEN,")"},
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
        {LEFT_PAREN_TOKEN,"("},
        {LITERAL_INTEGER,"0"},
        {RIGHT_PAREN_TOKEN,")"},
        {END_KEYWORD,"end"},
        {END_KEYWORD,"end"},
        {EOF_TOKEN,"\0"}
    };

    std::cout << "\nScanner Test #2" << '\n';
    return scanner_test(fibonacci, ans2);
}

// =============================================================================
// Test 3 - comparison.lua
// =============================================================================
bool test3() {
    char comparison[] = "build/test/res/comparison.lua";
    const LEXEME ans3[] = {
        {FUNCTION_KEYWORD,"function"},
        {ID,"f"},
        {LEFT_PAREN_TOKEN,"("},
        {RIGHT_PAREN_TOKEN,")"},
        {ID,"a"},
        {ASSIGNMENT_OPERATOR,"="},
        {LITERAL_INTEGER,"7"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"a"},
        {RIGHT_PAREN_TOKEN,")"},
        {ID,"b"},
        {ASSIGNMENT_OPERATOR,"="},
        {LITERAL_INTEGER,"8"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"b"},
        {RIGHT_PAREN_TOKEN,")"},
        {ID,"c"},
        {ASSIGNMENT_OPERATOR,"="},
        {ID,"a"},
        {MULT_OPERATOR,"*"},
        {ID,"b"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"c"},
        {RIGHT_PAREN_TOKEN,")"},
        {ID,"d"},
        {ASSIGNMENT_OPERATOR,"="},
        {ID,"a"},
        {DIV_OPERATOR,"/"},
        {ID,"b"},
        {ID,"e"},
        {ASSIGNMENT_OPERATOR,"="},
        {ID,"a"},
        {ADD_OPERATOR,"+"},
        {ID,"b"},
        {ID,"f"},
        {ASSIGNMENT_OPERATOR,"="},
        {ID,"a"},
        {SUB_OPERATOR,"-"},
        {ID,"b"},
        {IF_KEYWORD,"if"},
        {ID,"d"},
        {GT_OPERATOR,">"},
        {LITERAL_INTEGER,"1"},
        {THEN_KEYWORD,"then"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"d"},
        {RIGHT_PAREN_TOKEN,")"},
        {ELSE_KEYWORD,"else"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {LITERAL_INTEGER,"2"},
        {RIGHT_PAREN_TOKEN,")"},
        {END_KEYWORD,"end"},
        {IF_KEYWORD,"if"},
        {ID,"f"},
        {LT_OPERATOR,"<"},
        {LITERAL_INTEGER,"0"},
        {THEN_KEYWORD,"then"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"f"},
        {RIGHT_PAREN_TOKEN,")"},
        {ELSE_KEYWORD,"else"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {LITERAL_INTEGER,"0"},
        {RIGHT_PAREN_TOKEN,")"},
        {END_KEYWORD,"end"},
        {IF_KEYWORD,"if"},
        {ID,"e"},
        {LE_OPERATOR,"<="},
        {LITERAL_INTEGER,"15"},
        {THEN_KEYWORD,"then"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {ID,"e"},
        {RIGHT_PAREN_TOKEN,")"},
        {ELSE_KEYWORD,"else"},
        {PRINT_KEYWORD,"print"},
        {LEFT_PAREN_TOKEN,"("},
        {LITERAL_INTEGER,"0"},
        {RIGHT_PAREN_TOKEN,")"},
        {END_KEYWORD,"end"},
        {END_KEYWORD,"end"},
        {EOF_TOKEN,"\0"}
    };

    std::cout << "\nScanner Test #3" << '\n';
    return scanner_test(comparison, ans3);
}

int main() {
    std::cout << "Keyword Binary Search Test" << '\n';
    if (!keyword_test("repeat", REPEAT_KEYWORD)) return -1;
    if (!keyword_test("do", DO_KEYWORD)) return -1;
    if (!keyword_test("while", WHILE_KEYWORD)) return -1;
    if (!keyword_test("notinthetable", -1)) return -1;

    if (!test1()) return -1;
    if (!test2()) return -1;
    if (!test3()) return -1;

    return 0;
}
