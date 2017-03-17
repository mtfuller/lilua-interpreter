// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 3 - 1st Deliverable
// File:      lilua_symbol.h
// =============================================================================
// Description:
// Token code definitions for each token
// =============================================================================

// TOKEN DEFINITIONS:
#define ERR_TOKEN               -2
#define EOF_TOKEN               -1
#define UNKNOWN_TOKEN           0
#define LEFT_PAREN_TOKEN        1
#define RIGHT_PAREN_TOKEN       2
#define ID                      3
#define LITERAL_INTEGER         4
#define ASSIGNMENT_OPERATOR     5
#define LE_OPERATOR             6
#define LT_OPERATOR             7
#define GE_OPERATOR             8
#define GT_OPERATOR             9
#define EQ_OPERATOR             10
#define NE_OPERATOR             11
#define ADD_OPERATOR            12
#define SUB_OPERATOR            13
#define MULT_OPERATOR           14
#define DIV_OPERATOR            15

// KEYWORD DEFINITIONS
#define UKNOWN_KEYWORD          16
#define DO_KEYWORD              17
#define ELSE_KEYWORD            18
#define END_KEYWORD             19
#define FUNCTION_KEYWORD        20
#define IF_KEYWORD              21
#define PRINT_KEYWORD           22
#define REPEAT_KEYWORD          23
#define THEN_KEYWORD            24
#define UNTIL_KEYWORD           25
#define WHILE_KEYWORD           26

// INSTRUCTION SET DEFINITONS
#define PUSH_OPP		  5000
#define POP_OPP			  5001
#define ASSIGN_OPP		5002
#define ADD_OPP			  5003
#define SUB_OPP			  5004
#define MULT_OPP		  5005
#define DIV_OPP			  5006
#define GT_OPP        5007
#define GE_OPP			  5008
#define LT_OPP			  5009
#define LE_OPP			  5010
#define EQ_OPP			  5011
#define NOT_EQ_OPP		5012
#define GOTO_OPP		  5013
#define GOFALSE_OPP		5014
#define HALT_OPP		  5015
#define PRINT_OPP		  5016
