#ifndef INC_3D_VIEWER_PARSER_H
#define INC_3D_VIEWER_PARSER_H

#include <stdio.h>
#include <string.h>

#include "vector.h"

#define MAX_LENGHT 256

void parser(char *filename, vector *vector_v, vector_int *vector_f);
void get_v(char *buffer, vector *vector_v);
void get_f(char *buffer, vector_int *vector_f);
int is_digit(char buffer);

#endif  // INC_3D_VIEWER_PARSER_H
