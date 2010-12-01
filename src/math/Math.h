/*
 * Math.h
 *
 *  Created on: 20-11-2010
 *      Author: tmroczkowski
 */

#ifndef MATH_MATH_H_
#define MATH_MATH_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Point3f {float x, y, z;};


class Vector {

};

template <typename T>
class Vector2 : public Vector {
public:
	T x;
	T y;
	Vector2() : x(0.), y(0.) {}
	Vector2(T x, T y) {
		this->x = x;
		this->y = y;
	}
	~Vector2() {}

};

template <typename T>
class Vector3 {
public:
	T x;
	T y;
	T z;
	Vector3() : x(0), y(0), z(0) {}
	Vector3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	~Vector3 () {}
	void normalize () {
        float length =
        		(float) sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

        if(length == 0.0f)
        	length = 1.0f;

                x /= length;
                y /= length;
                z /= length;
	}
	T *array;
	float *asArray() {
		array = new T[3];
		array[0] = x;
		array[1] = y;
		array[2] = z;
		return array;
	}

	char *toString() {
		char *buffer = new char[64];
		int len = sprintf(buffer, "%10.10f, %10.10f, %10.10f", x, y, z);
//		char *buffer = new char[len];
//		copy(tmp, buffer);
//		free(tmp);
		return buffer;
	}
};

template <typename T>
struct Triplet {
	Vector3<T> normal;
	Vector2<T> texCoords;
	Vector3<T> vertex;
};

class Math {

	public:

		static const double _PI;
		static const double _2PI;
		static const double _PI2;

		static const double ANGRAD;
		static const double RADANG;

		static double RAD(int value) {
			return value * ANGRAD;
		}

		static double RAD(double value) {
			return value * ANGRAD;
		}

		static double ANG(int value) {
			return value * RADANG;
		}

		static double ANG(double value) {
			return value * RADANG;
		}

		static Point3f normal (float ax, float ay, float az, float bx, float by, float bz) {
			return
					(Point3f) {ay * bz - az * by,  ax * bz - az * bx, ax * by - ay * bx};
		}

		static Point3f normalize (float ax, float ay, float az) {
			double length = sqrt((ax * ax) + (ay * ay) + (az * az));
			if(length == 0)
				length = 1.;
			return (Point3f) {ax / length, ay / length, az / length};
		}

		static void normalize (float vector[3]) {
	        float length =
	        		(float) sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));

	        if(length == 0.0f)
	        	length = 1.0f;

	                vector[0] /= length;
	                vector[1] /= length;
	                vector[2] /= length;

		}

		static int randm(int mod) {
			return
				rand () % mod;
		}

		Math();
		virtual ~Math();
};

#endif /* MATH_H_ */
