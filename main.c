#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "util.h"
#include "vec3.h"
#include "hit.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"
#include "camera.h"

#define OBJECT_COUNT 4

Sphere WORLD[OBJECT_COUNT];

bool world_hit(const Ray *ray, double t_min, double t_max, HitRecord *record) {
  HitRecord temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;

  int i;
  for (i=0; i<OBJECT_COUNT; i++) {
    if (ray_hits_sphere(&WORLD[i], ray, t_min, closest_so_far, &temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      *record = temp_rec;
    }
  }

  return hit_anything;
}

Color ray_color(const Ray *ray, int depth) {
  if(depth <= 0) return color_from(0.0, 0.0, 0.0);

  HitRecord record;

  if (world_hit(ray, 0.0001, INFINITY, &record)) {
    Ray scattered;
    Color attenuation;
    if (record.material->scatter(record.material, ray, &record, &attenuation, &scattered))
      return vec3_mul_vec(attenuation, ray_color(&scattered, depth-1));
    return color_from(0.0, 0.0, 0.0);
  }

  vec3 unit_direction = vec3_unit(ray->direction);
  double t = 0.5 * (unit_direction.y + 1.0);
  return vec3_add(vec3_mul(WHITE, 1.0 - t), vec3_mul(SKY_BLUE, t));
}

int main() {
  srand(time(0));
  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int width = 256;
  const int height = (int) (width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  // Camera
  Camera camera;
  vec3 lookfrom = { -2.0, 2.0, 1.0 };
  vec3 lookat = { 0.0, 0.0 , -1.0 };
  vec3 abs_vertical = { 0.0, 1.0, 0.0 };
  initialize_camera(&camera, lookfrom, lookat, abs_vertical, 20.0, aspect_ratio);

  Material ground =  { lambertian_scatter, {0.8, 0.8, 0.0}, 0};
  Material center =  { lambertian_scatter, {0.7, 0.3, 0.3}, 0};
  Material left =  { metal_scatter, {0.8, 0.8, 0.8}, 0.0};
  Material right =  { metal_scatter, {0.8, 0.6, 0.2}, 0.6};

  WORLD[0] = sphere_from(vec3_from(0.0, -100.5, -1.0), 100.0, ground);
  WORLD[1] = sphere_from(vec3_from(0.0,    0.0, -1.0),   0.5, left);
  WORLD[2] = sphere_from(vec3_from(-1.0,   0.0, -1.0),   0.5, center);
  WORLD[3] = sphere_from(vec3_from(1.0,    0.0, -1.0),   0.5, right);

  // Write image file header
  printf("P3\n%i %i\n255\n", width, height);

  register int h, w;
  for (h=0; h<height; h++) {
    for (w=0; w<width; w++) {
      Color pixel = { 0.0, 0.0, 0.0 };
      register int s;
      for (s=0; s < samples_per_pixel; s++) {
        double u = (double) (w + random_double()) / width;
        double v = (double) (height - h + random_double()) / height;
        Ray ray = get_ray(&camera, u, v);
        pixel = vec3_add(pixel, ray_color(&ray, max_depth));
      }
      write_color(stdout, &pixel, samples_per_pixel);
    }
  }
}
