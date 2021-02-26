#include "vec3.h"
#include "hit.h"
#include "material.h"
#include "ray.h"
#include "color.h"

bool lambertian_scatter(Material *material, const Ray* ray, HitRecord *record, Color* attenuation, Ray* scattered) {
  vec3 scatter_direction = vec3_add(record->normal, vec3_random_unit());
  *scattered = ray_from(record->point, scatter_direction);
  *attenuation = material->albedo;

  if (near_zero(scatter_direction))
    scatter_direction = record->normal;

  *scattered = ray_from(record->point, scatter_direction);
  *attenuation = material->albedo;

  return true;
}

bool metal_scatter(Material *material, const Ray* ray, HitRecord* record, Color* attenuation, Ray* scattered) {
  double fuzz = (material->fuzz < 1) ?  material-> fuzz : 1;
  vec3 reflected = vec3_reflect(vec3_unit(ray->direction), record->normal);
  *scattered = ray_from(record->point, vec3_add(reflected, vec3_mul(vec3_random_in_unit_sphere(), fuzz)));
  *attenuation = material->albedo;
  return (vec3_dot(scattered->direction, record->normal) > 0);
}
