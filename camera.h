#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"

typedef struct {
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
} Camera;

void initialize_camera(Camera *camera, vec3 lookfrom, vec3 lookat, vec3 vup,
                       double vfov, double aspect_ratio);

Ray get_ray(const Camera *camera, double u, double v);

#endif
