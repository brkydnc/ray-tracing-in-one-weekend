#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "util.h"
#include "hit.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"

#define OBJECT_COUNT 2

const Sphere WORLD[OBJECT_COUNT] = {
  {{ 0.0, 0.0, -1.0 }, 0.5},
  {{ 0.0, -100.5, -1.0 }, 100.0},
};

bool world_hit(Ray ray, double t_min, double t_max, HitRecord *record) {
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    int i;
    for (i=0; i<OBJECT_COUNT; i++) {
      if (ray_hits_sphere(WORLD[i], ray, t_min, closest_so_far, &temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        *record = temp_rec;
      }
    }

    return hit_anything;
}

Color ray_color(Ray ray) {
  HitRecord record;
  if (world_hit(ray, 0, INFINITY, &record)) {
    vec3 point_light = {-1.0, 1.0, 0.0};
    vec3 point_to_light = vec3_sub(point_light, record.point);
    double I = 100.0;
    double distance = vec3_length(point_to_light);
    double cos_angle = vec3_dot(point_to_light, record.normal) / (vec3_length(record.normal) * distance);
    double E = cos_angle * I / distance * distance;
    double clamped = clamp(E, 0.0, 255.0);
    return color_from(clamped, clamped, clamped);
  }

  vec3 unit_direction = vec3_unit(ray.direction);
  double t = 0.5 * (unit_direction.y + 1.0);
  return vec3_add(vec3_mul(WHITE, 1.0 - t), vec3_mul(SKY_BLUE, t));
}

int main() {
  srand(time(0));
  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int width = 1366;
  const int height = (int) (width / aspect_ratio);

  // Camera
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;

  vec3 origin = {0.0, 0.0, 0.0};
  vec3 horizontal = {viewport_width, 0, 0};
  vec3 vertical = {0, viewport_height, 0};
  vec3 lower_left_corner = {-viewport_width/2, -viewport_height/2, -focal_length};

  printf("P3\n%i %i\n255\n", width, height);
  int h, w;
  for (h=0; h<height; h++) {
    for (w=0; w<width; w++) {
      double h_ratio = (double) (height - h) / height;
      double w_ratio = (double) (width - w) / width;
      // the point on viewport, relative to the lower left corner
      vec3 r_blc = { w_ratio * viewport_width, h_ratio * viewport_height, 0.0};
      // relative to the origin
      vec3 r_origin = vec3_add(lower_left_corner, r_blc);

      Ray ray = { origin, vec3_sub(r_origin, origin) };
      Color pixel = ray_color(ray);
      write_color(stdout, pixel);
    }
  }
}
