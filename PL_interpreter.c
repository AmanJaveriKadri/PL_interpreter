
#include <stdio.h>
#include <stdlib.h>
#include "file_input.h"

#define OR_CHAR 'v'
#define AND_CHAR '&'
#define NOT_CHAR '~'
#define COND_CHAR '>'
#define BICON_CHAR '='
#define EXIS_CHAR 'E'
#define UNIV_CHAR 'A'
#define IDEN_CHAR '-'

typedef enum operator { 
        AND = 0, OR, NOT, CONDITIONAL, BICON, EXIS, UNIV, IDEN, TERM, NONE
} operator;

typedef struct sentence {
        char *val;
        struct sentence *lval;
        struct sentence *rval;
        operator op;
} sentence;

char *getTerm(char *curr_line, int len, int *start, operator *op);
char *standard_term(char *curr_line, int len, int *i);
char *bracket_term(char *curr_line, int len, int *i);

int main()
{
        int num_lines;
        int *num_chars;
        char **sentences = read_lines("test.txt", &num_lines, &num_chars);

        char *curr_line = sentences[num_lines - 1];
        int curr_len = num_chars[num_lines - 1];
        
        int pos = 0;
        operator curr_op = NONE;

        printf("%s\n%d\n%c\n", getTerm(curr_line, curr_len, &pos, &curr_op), pos, curr_line[pos - 1]);
        
        printf("%d\n", curr_op);

        free_lines(sentences, num_chars, num_lines);

        return 0;
}

// Takes in a line, the length of the line, where to start
// reading on the line, and a pointer that will be updated
// with the main operator of the line in question.
char *getTerm(char *curr_line, int len, int *start, operator *op)
{
        for (; *start < len; ++(*start)) {

                switch (curr_line[*start])
                {
                        case '(':
                                *op = TERM;
                                return bracket_term(curr_line, len, start);

                        case ' ':
                                break;

                        case AND_CHAR:
                                *op = AND;
                                ++(*start);
                                return NULL;

                        case OR_CHAR:
                                *op = OR;
                                ++(*start);
                                return NULL;

                        case NOT_CHAR:
                                *op = NOT;
                                ++(*start);
                                return NULL;

                        default:
                                *op = TERM;
                                return standard_term(curr_line, len, start);
                }
        }
        *op = NONE;
        return NULL;
}

char *bracket_term(char *curr_line, int len, int *i)
{
        uint bracket_stack = 0;
        char *sent1;
        ++bracket_stack;

        while (curr_line[(*i)+1] == ' ')
                ++(*i);

        int end;
        for (end = (*i) + 1; bracket_stack != 0; ++end) {
                if (end == len){
                        fprintf(stderr, "Invalid syntax: %s",
                                "Missing closing bracket\n");
                        exit(1);
                }
                if (curr_line[end] == '(')
                        ++bracket_stack;
                if (curr_line[end] == ')')
                        --bracket_stack;
        }
        --end;

        while (curr_line[end] == ' ')
                --end;

        sent1 = malloc(end - (*i));
        int k = 0;
        for (int j = (*i) + 1; j < end; ++j) {
                sent1[k] = curr_line[j];
                ++k;
        }
        sent1[k] = '\0';
        *i = end + 1;

        return sent1;
}

char *standard_term(char *curr_line, int len, int *i)
{
        int end = (*i) + 1;
        while (curr_line[end] != ' ' && curr_line[end] != '(') {
                ++end;
                if (end == len) {
                        *i = end;
                        return NULL;
                }
        }

        char *sent1 = malloc(end - (*i));
        int k = 0;
        for (int j = *i; j < end; ++j) {
                sent1[k] = curr_line[j];
                ++k;
        }
        sent1[k] = '\0';
        *i = end;

        return sent1;
}

