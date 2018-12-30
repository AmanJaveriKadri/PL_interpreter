#ifndef FILE_INPUT_H_
#define FILE_INPUT_H_

#include <stdio.h>

// Parameter: C-string filename
// Returns: int number of line in file.
// Contract: Opens file with given filename, counts number of lines
//           of text in file. Returns number of lines.
int count_lines(char *filename);

// Parameters: FILE pointer, string pointer.
// Returns: int number of characters in line
// Contract: Reads a single line from the file given in as
//           a parameter and places line at location given
//           by second param. Mallocs space needed to store chars
//           must be freed. Does not save line on which EOF is hit.
int read_line(FILE *infile, char **line);

// Parameters: String filename, address of int, pointer to location
//             for int array.
// Returns: Array of string with lines.
// Contract: Opens file associated with filename passed in and reads
//           every line of the file into array of strings each index
//           representing a line. Updates value of pointer given
//           as second parameter to the number of lines read in,
//           allocates and populates an array at pointer given
//           by third param where each index corresponds to the 
//           number of characters in the line at the same index of the
//           string array.
char **read_lines(char *filename, int *num_lines, int **num_chars);

// Parameters: Array of strings, array of ints, int
// Returns: void
// Contract: Takes in the array of strings (lines) and the array of
//           ints (num_chars) and deallocates all memory previously
//           allocated to them.
void free_lines(char **lines, int *num_chars, int num_lines);

#endif