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
#define PUSH_OP		            5000
#define POP_OP			          5001
#define ASSIGN_OP		          5002
#define ADD_OP			          5003
#define SUB_OP			          5004
#define MULT_OP		            5005
#define DIV_OP			          5006
#define GT_OP                 5007
#define GE_OP			            5008
#define LT_OP			            5009
#define LE_OP			            5010
#define EQ_OP			            5011
#define NOT_EQ_OP		          5012
#define GOTO_OP		            5013
#define GOFALSE_OP		        5014
#define HALT_OP		            5015
#define PRINT_OP		          5016

// INSTRUCTION TYPE DEFINITONS
#define NONE_TYPE             0
#define BOOLEAN_TYPE          1
#define LITERAL_INTEGER_TYPE  2
#define ID_TYPE               3
