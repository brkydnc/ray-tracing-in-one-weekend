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
#include "camera.h"

#define OBJECT_COUNT 2
#define VIEWPORT_HEIGHT 2.0
#define FOCAL_LENGTH 1.0

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

Color ray_color(Ray ray, int depth) {
  if(depth <= 0) return color_from(0.0, 0.0, 0.0);

  HitRecord record;
  if (world_hit(ray, 0.0001, INFINITY, &record)) {
    vec3 target = vec3_add(record.normal, vec3_random_in_unit_sphere());
    Ray child = { record.point, target };
    return vec3_mul(ray_color(child, depth - 1), 0.5);
  }

  vec3 unit_direction = vec3_unit(ray.direction);
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
  initialize_camera(&camera, aspect_ratio, VIEWPORT_HEIGHT, FOCAL_LENGTH);

  // Write image file header
  printf("P3\n%i %i\n255\n", width, height);

  register int h, w;
  for (h=0; h<height; h++) {
    for (w=0; w<width; w++) {
      Color pixel = { 0.0, 0.0, 0.0 };
      register int s;
      for (s=0; s < samples_per_pixel; s++) {
        double u = (double) (width - w + random_double()) / width;
        double v = (double) (height - h + random_double()) / height;
        Ray ray = get_ray(camera, u, v);
        pixel = vec3_add(pixel, ray_color(ray, max_depth));
      }
      write_color(stdout, pixel, samples_per_pixel);
    }
  }
}
