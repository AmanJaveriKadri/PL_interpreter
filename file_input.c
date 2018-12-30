#include "file_input.h"

#include <stdlib.h>

typedef struct char_node {
        struct char_node *next;
        char val;
} char_node;

typedef struct string_node {
        struct string_node *next;
        char *val;
        int num_chars;
} string_node;


static void free_list(char_node *head);

char **read_lines(char *filename, int *num_lines, int **num_chars)
{
        string_node *head = malloc(sizeof(*head));
        string_node *curr = head;
        string_node *prev = NULL;
        curr->next = NULL;

        FILE *infile = fopen(filename, "r");

        *num_lines = 0;
        for (*num_lines = 0; 1; ++(*num_lines)) {
                curr->num_chars = read_line(infile, &(curr->val));

                if (curr->num_chars == -1) {
                        
                        if (prev != NULL) {
                                free(prev->next);
                                prev->next = NULL;
                        }
                        break;
                }

                curr->next = malloc(sizeof(*head));
                prev = curr;
                curr = curr->next;
        }


        char **all_lines = malloc(sizeof(*all_lines) * (*num_lines));
        *num_chars = malloc(sizeof(**num_chars) * (*num_lines));

        curr = head;
        for (int i = 0; curr != NULL; ++i) {
                all_lines[i] = curr->val;
                (*num_chars)[i] = curr->num_chars;
                head = curr;
                curr = curr->next;
                free(head);
        }

        fclose(infile);
        return all_lines;
}

void free_lines(char **lines, int *num_chars, int num_lines)
{
        for (int i = 0; i < num_lines; ++i)
                free(lines[i]);
        free(lines);
        free(num_chars);
}

int count_lines(char *filename)
{
        FILE *to_count = fopen(filename, "r");
        char *dump;
        if (to_count == NULL) {
                fprintf(stderr, "%s\n", "Invalid File");
                exit(1);
        }
        int i;
        for (i = 0; read_line(to_count, &dump) != -1; i++) {
                if (dump != NULL)
                        free(dump);
        }
        fclose(to_count);
        return i;
}

int read_line(FILE *infile, char **line)
{
        char_node *head = malloc(sizeof(*head));
        char_node *curr = head;
        curr->next = NULL;

        int i;
        int tempC;
        for (i = 0; 1; ++i) {
                tempC = fgetc(infile);
                

                if (tempC == (int)'\n') {
                        curr->val = '\0';
                        curr->next = NULL;
                        break;
                }

                if (tempC == -1) {
                        curr->next = NULL;
                        free_list(head);
                        return -1;
                }

                curr->val = tempC;
                curr->next = malloc(sizeof(*head));
                curr = curr->next;
        }

        *line = malloc(sizeof(*line) * (i));
        curr = head;

        char_node *temp;
        for (int j = 0; curr != NULL; ++j) {
                (*line)[j] = curr->val;

                temp = curr;
                curr = curr->next;
                free(temp);
        }

        return i - 1;
}

static void free_list(char_node *head) 
{
        char_node *temp = head;
        while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp);
        }
}