#include "sphere.h"

Sphere sphere_from(vec3 position, double radius, Material material) {
  Sphere sphere = { position, radius, material };
  return sphere;
}
