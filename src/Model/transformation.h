#ifndef INC_3D_VIEWER_TRANSFORMATION_H
#define INC_3D_VIEWER_TRANSFORMATION_H

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "vector.h"

void scale(vector *vector_v, double value);

void move_x(vector *vector_v, double value);
void move_y(vector *vector_v, double value);
void move_z(vector *vector_v, double value);

void rotate_x(vector *vector_v, double value);
void rotate_y(vector *vector_v, double value);

void centralize(vector *vector_v);

#endif  // INC_3D_VIEWER_TRANSFORMATION_H
