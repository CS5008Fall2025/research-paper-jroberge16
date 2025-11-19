#include <stdio.h>
#include <math.h>
#include <string.h>
#include "distance.h"


DistanceType calculate_euclidean_distance(const DistanceType* vec1, const DistanceType* vec2, int dimension){
    DistanceType sum = 0.0f;

    for (int i = 0; i < dimension; i++){
        DistanceType diff = vec1[i] - vec2[i];
        sum += powf(diff, 2);
    }
    return sqrtf(sum);
}

DistanceType calculate_cosine_distance(const DistanceType* vec1, const DistanceType* vec2, int dimension){
    if (dimension <= 0){
        return DISTANCE_TYPE_MAX;
    }

    DistanceType dot_product = 0.0f;
    DistanceType norm1 = 0.0f;
    DistanceType norm2 = 0.0f;

    for (int i = 0; i < dimension; i++){
        dot_product += vec1[i] * vec2[i];
        norm1 += powf(vec1[i], 2);
        norm2 += powf(vec2[i], 2);
    }

    return 1.0f - (dot_product / (sqrtf(norm1) * sqrtf(norm2)));
}

DistanceFunction get_distance_function(const char* metric_string){
    if (strcmp(metric_string, "euclidean") == 0) {
        return &calculate_euclidean_distance;
    } else if (strcmp(metric_string, "cosine") == 0) {
        return &calculate_cosine_distance;
    }
    perror("Unknown distance metric: please use: 'euclidean' or 'cosine'.\n");
    return NULL;
}







