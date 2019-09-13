// -------------------------------------------------------------------------------------------------------------------
//
//  File: trilateration.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//
// -------------------------------------------------------------------------------------------------------------------
//

#ifndef __TRILATERATION_H__
#define __TRILATERATION_H__

#include "basetsd.h"
#include "stdio.h"

//#define SHOW_PRINTS

#define TRILATERATION (1)

#define REGRESSION_NUM (10)
#define SPEED_OF_LIGHT      (299702547.0)   // in m/s in air
#define NUM_ANCHORS (5)
#define REF_ANCHOR (5)	//anchor IDs are 1,2,3,4,5 etc. (don't start from 0!)


#define		TRIL_3SPHERES							3
#define		TRIL_4SPHERES							4

typedef struct vec3d	vec3d;
struct vec3d {
	double	x;
	double	y;
	double	z;
};

/* Return the difference of two vectors, (vector1 - vector2). */
vec3d vdiff(const vec3d vector1, const vec3d vector2);

/* Return the sum of two vectors. */
vec3d vsum(const vec3d vector1, const vec3d vector2);

/* Multiply vector by a number. */
vec3d vmul(const vec3d vector, const double n);

/* Divide vector by a number. */
vec3d vdiv(const vec3d vector, const double n);

/* Return the Euclidean norm. */
double vdist(const vec3d v1, const vec3d v2);

/* Return the Euclidean norm. */
double vnorm(const vec3d vector);

/* Return the dot product of two vectors. */
double dot(const vec3d vector1, const vec3d vector2);

/* Replace vector with its cross product with another vector. */
vec3d cross(const vec3d vector1, const vec3d vector2);

int GetLocation(vec3d *best_solution, int use4thAnchor, vec3d* anchorArray, int *distanceArray);

double vdist(const vec3d v1, const vec3d v2);
#endif
