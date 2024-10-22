#pragma once

#include "Vector2.hpp"

template <class T>
class Rect {
public:
	union {
		struct {
			Vector2<T> position, size;
		};
		struct {
			Vector2<T> xy, wh;
		};
		struct {
			T x, y, w, h;
		};
		struct {
			T r, g, b, a;
		};
		struct {
			T left, top, width, height;
		};
	};

	Rect() {
		x = 0;
		y = 0;
		w = 0; 
		h = 0;
	}

	Rect(T e) {
		x = e; 
		y = e;
		w = e;
		h = e;
	}

	Rect(Vector2<T> position, Vector2<T> size) {
		x = position.x;
		y = position.y;
		w = size.w;
		h = size.h;
	}

	Rect(T x, T y, T w, T h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	Rect(const Rect<T>& rect) {
		x = rect.x;
		y = rect.y;
		w = rect.w;
		h = rect.h;
	}

	template <typename U>
	Rect(const Rect<U>& rect) {
		x = (T)rect.x;
		y = (T)rect.y;
		w = (T)rect.w;
		h = (T)rect.h;
	}
};

typedef Rect<uint64_t> UIntRect;
typedef Rect<int64_t> IntRect;
typedef Rect<float> FloatRect;
typedef Rect<float> Color;