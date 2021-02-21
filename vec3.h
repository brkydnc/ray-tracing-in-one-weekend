#ifndef VEC3_H
#define VEC3_H

typedef struct {
  double x;
  double y;
  double z;
} vec3;

vec3 vec3_from(double x, double y, double z);
double vec3_length(vec3 vector);
vec3 vec3_add(vec3 vector1, vec3 vector2);
vec3 vec3_sub(vec3 vector1, vec3 vector2);
vec3 vec3_mul(vec3 vector, double value);
vec3 vec3_div(vec3 vector, double value);
vec3 vec3_unit(vec3 vector);
double vec3_dot(vec3 vector1, vec3 vector2);
vec3 vec3_cross(vec3 vector1, vec3 vector2);

#endif
