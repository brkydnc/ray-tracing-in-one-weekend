#ifndef HIT_H
#define HIT_H 
#include <stdbool.h>
#include "vec3.h"
#include "sphere.h"
#include "ray.h"

typedef struct {
  vec3 point;
  vec3 normal;
  double t;
  bool front_face;
} HitRecord;

void set_face_normal(HitRecord *record, Ray ray, vec3 outward_normal);
bool ray_hits_sphere(Sphere sphere, Ray ray, double t_min, double t_max, HitRecord *record);

#endif
