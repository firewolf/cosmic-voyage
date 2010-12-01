/*
 * Orbit.h
 *
 *  Created on: 20-11-2010
 *      Author: tmroczkowski
 */

#ifndef MATH_ORBIT_H_
#define MATH_ORBIT_H_

#include "Math.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/gl.h>

struct PlanetData {
	const char *name;
	double
		semiMajorAxis, eccentricity, inclination, o, w, l, period, radius, rotateDelta;
	Vector3<float>
		center;
	std::string texturePath;
	GLuint textureId;
};

class Orbit {
	private:

		static Orbit *instance;

		/**
			e eccentricity (0=circle, 0-1=ellipse, 1=parabola)
			M mean anomaly (0 at perihelion; increases uniformly with time)
		 */

		double eccentricAnomaly(double M, double e, double E) {

			double E1 = E + ((M + e * sin(E * Math::ANGRAD) - E) / (1. - (e * Math::ANGRAD) * cos(E * Math::ANGRAD)));

//			printf("E=%10.10f %10.10f E1=%10.10f\n", E, E1 - E, E1);

			if(std::abs(E1 - E) > 1E-3)
				return eccentricAnomaly(M, e, E1);

			return E1;
		}

		double eccentricAnomaly2(double M, double e, double E) {

			if(E == 0)
				E = M + e * Math::ANGRAD * sin(M) * (1.0 + e * cos(M));

			double E1 = E - (E - e * Math::ANGRAD * sin(E) - M ) / ( 1 - e * cos(E) );

//			printf("E=%10.10f %10.10f E1=%10.10f\n", E, E1 - E, E1);

			if(std::abs(E1 - E) > 1E-3)
				return eccentricAnomaly(M, e, E1);

			return E1;
		}
		Orbit() {};
		Orbit(const Orbit&) {};
		Orbit &operator= (const Orbit&);

	public:

		static Orbit *getInstance () {
			if(instance == 0)
				instance = new Orbit;

			return instance;
		}

		virtual ~Orbit() {};
		Point3f position(double angle, double r) {
			double x = cos(Math::RAD(angle)) * r;
			double y = sin(Math::RAD(angle)) * r;
			double z = 0;
			return (Point3f) {x, z, y};
		}

		/**
			N - longitude of the ascending node
			i inclination to the ecliptic (plane of the Earth's orbit)
			w argument of perihelion
			a semi-major axis, or mean distance from Sun (AU) - for moon (earth radii)
			e eccentricity (0=circle, 0-1=ellipse, 1=parabola)
			ep eccentricity calculation part
			M mean anomaly (0 at perihelion; increases uniformly with time)
		 */

		Point3f position(double N, double i, double w, double a, double e, double M) {

//			M = Math::RAD(M);
//			N = Math::RAD(N);
//			w = Math::RAD(w);

			double sinN = sin(N);
			double cosN = cos(N);
			double sini = sin(i);
			double cosi = cos(i);

			double E = eccentricAnomaly(M, e, 0);

//			printf("N:%10.10f,i:%10.10f,w:%10.10f,a:%10.10f,e:%10.10f,M:%10.10f,E:%10.10f\n", N,i,w,a,e,M,E);

			double xv = a * cos(E) - e;
			double yv = a * sqrt(1. - e * e) * sin(E);

			double v  = atan2(yv, xv);
			double r  = sqrt(xv * xv + yv * yv);

			double vw = v+w;

			double sinvw = sin(vw);
			double cosvw = cos(vw);

			double sinvwcosi = sinvw * cosi;

			double x = r * (cosN * cosvw - sinN * sinvwcosi);
			double y = - r * (sinN * cosvw + cosN * sinvwcosi);
			double z = r * (sinvw * sini);


//			printf("x:%10.10f,y:%10.10f,z:%10.10f\n", x, y, z);
//			printf("r:%10.10f, r2:%10.10f\n", r, sqrt(x*x+y*y+z*z));

			return (Point3f) {x, z, y};
		}

		Point3f position2(double N, double i, double w, double a1, double e, double M) {

//			double E = eccentricAnomaly(M, e, M);

//			double F =  cos(Math::RAD(N));
//			double G =  sin(Math::RAD(N)) * cos(Math::RAD(e));
//			double H =  sin(Math::RAD(N)) * sin(Math::RAD(e));
//			double P = -sin(Math::RAD(N)) * cos(Math::RAD(i));
//			double Q =  cos(Math::RAD(N)) * cos(Math::RAD(i)) * cos(Math::RAD(e)) - sin(Math::RAD(i)) * sin(Math::RAD(e));
//			double R =  cos(Math::RAD(N)) * cos(Math::RAD(i)) * sin(Math::RAD(e)) + sin(Math::RAD(i)) * cos(Math::RAD(e));
//
//			double A = atan2(Math::RAD(F), Math::RAD(P));
//			double B = atan2(Math::RAD(G), Math::RAD(Q));
//			double C = atan2(Math::RAD(H), Math::RAD(R));
//			double a = sqrt(F*F + P*P);
//			double b = sqrt(G*G + Q*Q);
//			double c = sqrt(H*H + R*R);

//			std::cout << "test: " << F * F + G * G + H * H << ", " << P * P + Q * Q + R * R << std::endl;
//			double r = a1 * (1 - e * cos(Math::RAD(E)));
//			double v = 2*atan (sqrt((1+e)/(1-e)*tan (Math::RAD(E/2))));
//			double L = p + v;

//			double v = atan2(sqrt(1 + e / 1 - e) * tan (E / 2);
			double x, y, z;
//			double x = r * a * sin(A + w + v);
//			double y = r * b * sin(B + w + v);
//			double z = r * c * sin(C + w + v);

			return (Point3f) {x, z, y};
		}

		double calcDay(int year, int month, int day, double hour) {
			return
					(367 * year - 7 * (year + int((month + 9)/12.) ) / 4. +  275 * int(month / 9.) + day - 730530) + (hour / 24.);
		}

		Vector3<float> generateOrbit (PlanetData *pd, double time) {
			double
				T  = 4000. + time;
			double
				d  = Math::_2PI / pd->period;
			double
				co = cos(Math::RAD(pd->o)),
				so = sin(Math::RAD(pd->o)),
				ci = cos(Math::RAD(pd->inclination)),
				si = sin(Math::RAD(pd->inclination)),
				u  = Math::RAD(pd->w + pd->l),
				b  = sqrt((1 + pd->eccentricity) / (1 - pd->eccentricity));

			return
				cartCoord(keppler(pd->eccentricity, T, d), pd->eccentricity, co, so, b, u, ci, si, pd->semiMajorAxis);
		}

		double keppler(double eccentricity, double T, double d) {
			double
				m  = T * d,
				e0 = m + eccentricity * sin(m);

			return
				m + eccentricity * sin(e0);
		}


		Vector3<float> cartCoord(double em, double e, double co, double so, double b, double u, double ci, double si, float a) {

			double
				v = 2 * atan(b * tan(em/2)) + u,
				r = a * (1 - e * cos(em));

			return
				Vector3<float>(
						r * (co * cos(v) - so * ci * sin(v)),
						r * (so * cos(v) + co * ci * sin(v)),
						r * si * sin (v)
				);
		}

};

#endif /* ORBIT_H_ */
