#include <math.h>
#include "util.h"
#include "camera.h"
#include "vec3.h"

void initialize_camera(Camera *camera, vec3 lookfrom, vec3 lookat, vec3 vup,
                       double vfov, double aspect_ratio)
{
  double theta = degrees_to_radians(vfov);
  double h = tan(theta/2);
  double viewport_height = 2.0 * h;
  double viewport_width = aspect_ratio * viewport_height;

  vec3 w = vec3_unit(vec3_sub(lookfrom, lookat));
  vec3 u = vec3_unit(vec3_cross(vup, w));
  vec3 v = vec3_cross(w, u);

  camera->origin = lookfrom;
  camera->horizontal = vec3_mul(u, viewport_width);
  camera->vertical = vec3_mul(v, viewport_height);
  vec3 p = vec3_add(vec3_mul(camera->horizontal, 0.5), vec3_mul(camera->vertical, 0.5));
  camera->lower_left_corner = vec3_sub(lookfrom, vec3_add(p, w));
}

Ray get_ray(const Camera *camera, double u, double v) {
  vec3 point = vec3_add(vec3_mul(camera->horizontal, u), vec3_mul(camera->vertical, v));
  vec3 direction = vec3_sub(vec3_add(camera->lower_left_corner, point), camera->origin);
  Ray ray = { camera->origin, direction };
  return ray;
}
