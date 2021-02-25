#ifndef HIT_H
#define HIT_H 
#include <stdbool.h>
#include "vec3.h"
#include "sphere.h"
#include "ray.h"
#include "color.h"

typedef struct HitRecord {
  vec3 point;
  vec3 normal;
  double t;
  bool front_face;
  Material *material;
} HitRecord;

void set_face_normal(HitRecord *record, const Ray *ray, vec3 *outward_normal);
bool ray_hits_sphere(const Sphere *sphere, const Ray *ray, double t_min, double t_max, HitRecord *record);

#undef Material
#endif
