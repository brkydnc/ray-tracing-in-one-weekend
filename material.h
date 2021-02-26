#ifndef MATERIAL_H
#define MATERIAL_H 

#include <stdbool.h>
#include "color.h"

struct HitRecord;
typedef struct Material {
  bool (*scatter)(struct Material*, const Ray*, struct HitRecord*, Color*, Ray*);
  Color albedo;
  double fuzz;
} Material;

bool lambertian_scatter(Material*, const Ray*, struct HitRecord*, Color*, Ray*);
bool metal_scatter(Material*, const Ray*, struct HitRecord*, Color*, Ray*);

#endif
