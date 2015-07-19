#ifndef VEC2_H
#define VEC2_H

#include <cmath>

struct vec2 {
	union {
		struct {
			float x, y;
		};
		float v[2];
	};

	#define BINOP(op) \
	vec2& operator op##=(const vec2& o){ \
		x op##= o.x; \
		y op##= o.y; \
		return *this; \
	} \
	vec2 operator op(const vec2& o) const { \
		vec2 tmp{x,y}; \
		tmp op##= o; \
		return tmp; \
	}

	BINOP(+)
	BINOP(-)
	BINOP(*)
	BINOP(/)

	float magnitude() const {
		auto msqr = x*x + y*y;
		return std::sqrt(magnitude_squared());
	}
	float magnitude_squared() const {
		return x*x + y*y;
	}
};

#endif