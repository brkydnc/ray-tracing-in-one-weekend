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

Ray get_ray(Camera camera, double u, double v);
void initialize_camera(Camera *camera, double aspect_ratio, double viewport_height, double focal_length);

#endif
