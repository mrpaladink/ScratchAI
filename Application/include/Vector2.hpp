#pragma once

#include <cstdint>

template <class T>
class Vector2 {
public:
	union {
		struct {
			T x, y;
		};
		struct {
			T w, h;
		};
		struct {
			T left, top;
		};
		struct {
			T width, height;
		};
	};

	Vector2() {
		x = 0;
		y = 0;
	}

	Vector2(T e) {
		x = e;
		y = e;
	}

	Vector2(T e1, T e2) {
		x = e1;
		y = e2;
	}

	Vector2(const Vector2<T>& v) {
		x = v.x;
		y = v.y;
	}

	template <typename U>
	Vector2(const Vector2<U>& v) {
		x = (T)v.x;
		y = (T)v.y;
	}

	Vector2<T> operator+(Vector2<T> v) {
		return Vector2<T>(x + v.x, y + v.y);
	}

	Vector2<T> operator-(Vector2<T> v) {
		return Vector2<T>(x - v.x, y - v.y);
	}

	Vector2<T> operator*(Vector2<T> v) {
		return Vector2<T>(x * v.x, y * v.y);
	}

	Vector2<T> operator/(Vector2<T> v) {
		return Vector2<T>(x / v.x, y / v.y);
	}

	void operator+=(Vector2<T> v) {
		x += v.x;
		y += v.y;
	}
	
	void operator-=(Vector2<T> v) {
		x -= v.x;
		y -= v.y;
	}
	
	void operator*=(Vector2<T> v) {
		x *= v.x;
		y *= v.y;
	}
	
	void operator/=(Vector2<T> v) {
		x /= v.x;
		y /= v.y;
	}
};

typedef Vector2<float> vec2;
typedef Vector2<int64_t> vec2i;
typedef Vector2<uint64_t> vec2u;