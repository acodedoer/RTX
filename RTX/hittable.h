#pragma once
#include "vec3.h"
#include "ray.h"

struct hit_record
{
	point3 p;
	double t;
	vec3 normal;
	bool front_face;

	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.get_direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& hit) const = 0;
};