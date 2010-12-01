/*
 * SphereMath.h
 *
 *  Created on: 20-11-2010
 *      Author: tmroczkowski
 */

#ifndef MATH_SPHEREMATH_H_
#define MATH_SPHEREMATH_H_

#include <vector>
#include "Math.h"


class SphereMath {

public:
	static int create (double r, int n, std::vector<std::vector<Triplet<float> > > &triplets) {

		double theta1,theta2,theta3,cost1,cost2,cost3,sint1,sint2,sint3;
		Vector3<float> e,p;

		for (register int j=0;j<n/2;j++) {

		    theta1 = j * Math::_2PI / n - Math::_PI2;
		    theta2 = (j + 1) * Math::_2PI / n - Math::_PI2;
		    cost1 = cos(theta1);
		    cost2 = cos(theta2);
		    sint1 = sin(theta1);
		    sint2 = sin(theta2);
		    std::vector<Triplet<float> > triplet;
			for (register int i=0;i<=n;i++) {

		        theta3 = i * Math::_2PI / n;

			    cost3 = cos(theta3);
			    sint3 = sin(theta3);

		         e.x = cost2 * cost3;
		         e.y = sint2;
		         e.z = cost2 * sint3;

		         triplet.push_back((Triplet<float>){
			       	Vector3 <float> (e.x, e.y, e.z),
			       	Vector2 <float> (i/(double)n,2*(j+1)/(double)n),
			       	Vector3 <float> (r * e.x, r * e.y, r * e.z)
			     });

		         e.x = cost1 * cost3;
		         e.y = sint1;
		         e.z = cost1 * sint3;

		         triplet.push_back((Triplet<float>){
			       	Vector3 <float> (e.x, e.y, e.z),
			       	Vector2 <float> (i/(double)n,2*j/(double)n),
			       	Vector3 <float> (r * e.x, r * e.y, r * e.z)
			     });

			}

		    triplets.push_back(triplet);

		}

		return 0;
	}
};

#endif
