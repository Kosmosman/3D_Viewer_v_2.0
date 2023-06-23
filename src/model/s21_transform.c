#include "./common/s21_matrix.h"
#include "s21_3DViewer_v1.h"
#include "string.h"

void s21_move_x(data_t *data, long double a) {
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    data->massiv[i] += a;
  }
}
void s21_move_y(data_t *data, long double a) {
  for (int i = 1; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    data->massiv[i] += a;
  }
}
void s21_move_z(data_t *data, long double a) {
  for (int i = 2; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    data->massiv[i] += a;
  }
}

void s21_rotate_x(data_t *data, long double angle) {
  angle = s21_degres_to_radians(angle);
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    long double y = data->massiv[i + 1];
    long double z = data->massiv[i + 2];

    // x'=x;
    // y':=y*cos(L)+z*sin(L) ;
    // z':=-y*sin(L)+z*cos(L) ;

    data->massiv[i + 1] = y * cosl(angle) + z * sinl(angle);
    data->massiv[i + 2] = -y * sinl(angle) + z * cosl(angle);
  }
}
void s21_rotate_y(data_t *data, long double angle) {
  angle = s21_degres_to_radians(angle);
  for (int i = 0;
       data->massiv && data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    long double x = data->massiv[i];
    long double z = data->massiv[i + 2];

    // x'=x*cos(L)+z*sin(L);
    // y'=y;
    // z'=-x*sin(L)+z*cos(L);

    data->massiv[i] = x * cosl(angle) + z * sinl(angle);
    data->massiv[i + 2] = -x * sinl(angle) + z * cosl(angle);
  }
}
void s21_rotate_z(data_t *data, long double angle) {
  angle = s21_degres_to_radians(angle);
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    long double x = data->massiv[i];
    long double y = data->massiv[i + 1];

    // x'=x*cos(L)-y*sin(L);
    // y'=x*sin(L)+y*cos(L);
    // z'=z;

    data->massiv[i] = x * cosl(angle) - y * sinl(angle);
    data->massiv[i + 1] = x * sinl(angle) + y * cosl(angle);
  }
}
long double s21_degres_to_radians(long double angle) {
  return angle * acos(-1) / 180.0;
}

void s21_scale(data_t *data, long double scale) {
  printf("scale = %Lf\n", scale);
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3; i++) {
    data->massiv[i] *= scale;
  }
}
