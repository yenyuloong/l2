#ifndef _L2_ERROR_H_
#define _L2_ERROR_H_

#include "../l2_base/l2_common_type.h"

typedef enum _l2_internal_error_type {
    L2_INTERNAL_ERROR_OUT_OF_RANGE,
    L2_INTERNAL_ERROR_NULL_POINTER,
    L2_INTERNAL_ERROR_ILLEGAL_OPERATION,
    L2_INTERNAL_ERROR_UNREACHABLE_CODE,
    L2_INTERNAL_ERROR_MEM_BLOCK_NOT_MANAGED,
    L2_INTERNAL_ERROR_MEM_BLOCK_NOT_IN_GC
}l2_internal_error_type;

typedef enum _l2_parsing_error_type {
    L2_PARSING_ERROR_ILLEGAL_CHARACTER,
    L2_PARSING_ERROR_ILLEGAL_NUMBER_IN_AN_OCTAL_LITERAL,
    L2_PARSING_ERROR_INCOMPLETE_HEX_LITERAL,
    L2_PARSING_ERROR_EMPTY_CHARACTER_LITERAL,
    L2_PARSING_ERROR_INCOMPLETE_CHARACTER_LITERAL,
    L2_PARSING_ERROR_INCOMPLETE_REAL_LITERAL,
    L2_PARSING_ERROR_MULTI_CHARACTER_IN_SINGLE_CHARACTER_LITERAL,
    L2_PARSING_ERROR_INCOMPLETE_STRING_LITERAL,
    L2_PARSING_ERROR_UNEXPECTED_TOKEN,
    L2_PARSING_ERROR_MISSING_COLON,
    L2_PARSING_ERROR_MISSING_SEMICOLON,
    L2_PARSING_ERROR_MISSING_RBRACE,
    L2_PARSING_ERROR_MISSING_RP,
    L2_PARSING_ERROR_IDENTIFIER_UNDEFINED,
    L2_PARSING_ERROR_IDENTIFIER_REDEFINED,
    L2_PARSING_ERROR_REFERENCE_SYMBOL_BEFORE_INITIALIZATION,
    L2_PARSING_ERROR_INCOMPATIBLE_OPERATION,
    L2_PARSING_ERROR_DIVIDE_BY_ZERO,
    L2_PARSING_ERROR_EXPR_NOT_BOOL,
    L2_PARSING_ERROR_LEFT_SIDE_OF_OPERATOR_MUST_BE_A_BOOL_VALUE,
    L2_PARSING_ERROR_RIGHT_SIDE_OF_OPERATOR_MUST_BE_A_BOOL_VALUE,
    L2_PARSING_ERROR_LEFT_SIDE_OF_OPERATOR_MUST_BE_A_INTEGER_VALUE,
    L2_PARSING_ERROR_RIGHT_SIDE_OF_OPERATOR_MUST_BE_A_INTEGER_VALUE,
    L2_PARSING_ERROR_DUALISTIC_OPERATOR_CONTAINS_INCOMPATIBLE_TYPE,
    L2_PARSING_ERROR_UNITARY_OPERATOR_CONTAINS_INCOMPATIBLE_TYPE,
    L2_PARSING_ERROR_INVALID_CONTINUE_IN_CURRENT_CONTEXT,
    L2_PARSING_ERROR_INVALID_BREAK_IN_CURRENT_CONTEXT,
    L2_PARSING_ERROR_INVALID_RETURN_IN_CURRENT_CONTEXT,
    L2_PARSING_ERROR_SYMBOL_IS_NOT_PROCEDURE,
    L2_PARSING_ERROR_TOO_MANY_PARAMETERS,
    L2_PARSING_ERROR_TOO_FEW_PARAMETERS,
    L2_PARSING_ERROR_EXPR_RESULT_WITHOUT_VALUE,
    L2_PARSING_ERROR_INCOMPATIBLE_EXPR_TYPE,
    L2_PARSING_ERROR_INCOMPATIBLE_SYMBOL_TYPE
}l2_parsing_error_type;

void l2_clean_before_abort();
/* void l2_internal_error_en(l2_internal_error_type error_type, ...); */
/* void l2_parsing_error_en(l2_parsing_error_type error_type, int lines, int cols, ...); */
void l2_internal_error(l2_internal_error_type error_type, ...);
void l2_parsing_error(l2_parsing_error_type error_type, int lines, int cols, ...);

#endif