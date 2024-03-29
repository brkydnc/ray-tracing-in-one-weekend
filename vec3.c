#include <stdbool.h>
#include <math.h>
#include "vec3.h"
#include "util.h"

vec3 vec3_from(double x, double y, double z) {
  vec3 vector = {x, y, z};
  return vector;
};

double vec3_length(vec3 vector) {
  return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
};

vec3 vec3_add(vec3 vector1, vec3 vector2) {
  vector1.x += vector2.x;
  vector1.y += vector2.y;
  vector1.z += vector2.z;
  return vector1;
};

vec3 vec3_sub(vec3 vector1, vec3 vector2) {
  vector1.x -= vector2.x;
  vector1.y -= vector2.y;
  vector1.z -= vector2.z;
  return vector1;
};

vec3 vec3_mul(vec3 vector, double n) {
  vector.x *= n;
  vector.y *= n;
  vector.z *= n;
  return vector;
};

vec3 vec3_mul_vec(vec3 v, vec3 u) {
  return vec3_from(v.x * u.x, v.y * u.y, v.z * u.z);
}

vec3 vec3_div(vec3 vector, double n) {
  vector.x /= n;
  vector.y /= n;
  vector.z /= n;
  return vector;
};

vec3 vec3_unit(vec3 vector) {
  double length = vec3_length(vector);
  return vec3_div(vector, length);
};

double vec3_dot(vec3 vector1, vec3 vector2) {
   return vector1.x*vector2.x + vector1.y*vector2.y + vector1.z*vector2.z;
};

vec3 vec3_cross(vec3 vector1, vec3 vector2) {
  vec3 product;
  product.x = vector1.y * vector2.z - vector1.z * vector2.y;
  product.y = vector1.z * vector2.x - vector1.x * vector2.z;
  product.z = vector1.x * vector2.y - vector1.y * vector2.x;
  return product;
};

vec3 vec3_random() {
  vec3 vector = { random_double(), random_double(), random_double() };
  return vector;
}

vec3 vec3_random_in(double min, double max) {
  vec3 vector = { random_double_in(min, max), random_double_in(min,max), random_double_in(min,max) };
  return vector;
}

vec3 vec3_random_in_unit_sphere() {
  while (1) {
    vec3 p = vec3_random_in(-1,1);
    if (vec3_length(p) >= 1) continue;
    return p;
  }
}

vec3 vec3_random_unit() {
  return vec3_unit(vec3_random_in_unit_sphere());
}

vec3 vec3_random_in_hemisphere(vec3 normal) {
  vec3 in_unit_sphere = vec3_random_in_unit_sphere();
  return (vec3_dot(in_unit_sphere, normal) > 0.0) ? in_unit_sphere : vec3_mul(in_unit_sphere, -1);
}

bool near_zero(vec3 v) {
  const double s = 1e-8;
  return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

vec3 vec3_reflect(vec3 v, vec3 n) {
    return vec3_sub(v, vec3_mul(n, 2 * vec3_dot(v, n)));
}
