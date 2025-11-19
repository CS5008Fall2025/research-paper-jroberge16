#ifndef DISTANCE_H
#define DISTANCE_H

#include <float.h>

#define DISTANCE_TYPE_MAX FLT_MAX

typedef float DistanceType; 

DistanceType calculate_euclidean_distance(const DistanceType* vec1, const DistanceType* vec2, int dimension);
DistanceType calculate_cosine_distance(const DistanceType* vec1, const DistanceType* vec2, int dimension);


#endif