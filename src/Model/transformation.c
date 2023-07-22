#include "transformation.h"

void scale(vector *vector_v, double value) {
  if (value != 0) {
    value /= 100;
    for (unsigned i = 0; i < vector_v->index; ++i) {
      vector_v->data[i] *= value;
    }
  }
}

void move_x(vector *vector_v, double value) {
  value /= 100;
  for (unsigned i = 0; i < vector_v->index; i += 3) {
    vector_v->data[i] += value;
  }
}

void move_y(vector *vector_v, double value) {
  value /= 100;
  for (unsigned i = 1; i < vector_v->index; i += 3) {
    vector_v->data[i] += value;
  }
}

void move_z(vector *vector_v, double value) {
  value /= 100;
  for (unsigned i = 2; i < vector_v->index; i += 3) {
    vector_v->data[i] += value;
  }
}

void rotate_x(vector *vector_v, double value) {
  double temp;
  value /= 100;
  for (unsigned i = 0; i < vector_v->index; i += 3) {
    temp = vector_v->data[i + 1];
    vector_v->data[i + 1] =
        vector_v->data[i + 1] * cos(value) + vector_v->data[i + 2] * sin(value);
    vector_v->data[i + 2] =
        -1 * temp * sin(value) + vector_v->data[i + 2] * cos(value);
  }
}

void rotate_y(vector *vector_v, double value) {
  double temp;
  value /= 100;
  for (unsigned i = 1; i < vector_v->index; i += 3) {
    temp = vector_v->data[i - 1];
    vector_v->data[i - 1] =
        vector_v->data[i - 1] * cos(value) + vector_v->data[i + 1] * sin(value);
    vector_v->data[i + 1] =
        -1 * temp * sin(value) + vector_v->data[i + 1] * cos(value);
  }
}

void centralize(vector *vector_v) {
  if (vector_v->max_value > 1) {
    for (unsigned i = 0; i < vector_v->index; ++i) {
      vector_v->data[i] /= vector_v->max_value;
    }
  } else {
    for (unsigned i = 0; i < vector_v->index; ++i) {
      vector_v->data[i] *= 0.95;
    }
  }
}
