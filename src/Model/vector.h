#ifndef INC_3D_VIEWER_S21_VECTOR_H
#define INC_3D_VIEWER_S21_VECTOR_H

#include <math.h>
#include <stdlib.h>

// double vector
typedef struct vector {
  double *data;
  unsigned size;
  unsigned index;
  double max_value;
} vector;

vector s21_create_vector();
void s21_push(vector *storage, double value);

// unsigned vector
typedef struct vector_int {
  unsigned *data;
  unsigned size;
  unsigned index;
  unsigned max_value;
} vector_int;

vector_int s21_create_vector_int();
void s21_push_int(vector_int *storage, unsigned value);

#endif  // INC_3D_VIEWER_S21_VECTOR_H
