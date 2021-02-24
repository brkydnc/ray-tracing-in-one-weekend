#include "camera.h"
#include "vec3.h"

void initialize_camera(Camera *camera, double aspect_ratio, double viewport_height, double focal_length) {
  double viewport_width = aspect_ratio * viewport_height;
  camera->origin = vec3_from(0.0, 0.0, 0.0);
  camera->horizontal = vec3_from(viewport_width, 0.0, 0.0);
  camera->vertical = vec3_from(0.0, viewport_height, 0.0);
  camera->lower_left_corner = vec3_from(-viewport_width/2, -viewport_height/2, -focal_length);
}

Ray get_ray(const Camera *camera, double u, double v) {
  vec3 point = vec3_add(vec3_mul(camera->horizontal, u), vec3_mul(camera->vertical, v));
  vec3 direction = vec3_sub(vec3_add(camera->lower_left_corner, point), camera->origin);
  Ray ray = { camera->origin, direction };
  return ray;
}
