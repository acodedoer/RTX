#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray {
public:
	point3 origin;
	vec3 direction;

public:
	ray() {};
	ray(point3 o, vec3 dir): origin {o}, direction{dir} {}

	vec3 get_direction()const { return direction; }
	vec3 get_origin()const { return origin; }
	point3 at(const double t) const
	{
		return origin + (t * direction);
	}

};
#endif // !RAY_H
