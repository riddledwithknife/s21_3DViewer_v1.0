#include "vector.h"

// float vector
vector s21_create_vector() {
  vector storage;
  storage.size = 10;
  storage.index = 0;
  storage.max_value = 0;
  storage.data = malloc(storage.size * sizeof(double));

  return storage;
}

void s21_push(vector *storage, double value) {
  if (storage->size == storage->index) {
    storage->size *= 3;
    double *tmp = realloc(storage->data, storage->size * sizeof(double));

    if (tmp) {
      storage->data = tmp;
    } else {
      free(storage->data);
    }
  }

  storage->data[storage->index] = value;
  storage->index++;
  if (storage->max_value < fabs(value)) storage->max_value = value;
}

// unsigned vector
vector_int s21_create_vector_int() {
  vector_int storage;
  storage.size = 10;
  storage.index = 0;
  storage.max_value = 0;
  storage.data = malloc(storage.size * sizeof(unsigned));

  return storage;
}

void s21_push_int(vector_int *storage, unsigned value) {
  if (storage->size == storage->index) {
    storage->size *= 3;
    unsigned *tmp = realloc(storage->data, storage->size * sizeof(unsigned));

    if (tmp) {
      storage->data = tmp;
    } else {
      free(storage->data);
    }
  }

  storage->data[storage->index] = value;
  storage->index++;

  if (storage->max_value < value) storage->max_value = value;
}