#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "distance.h"


void test_distance(){
    const int dimension = 2;
    DistanceType vec1[] = {1.0f, 1.0f};
    DistanceType vec2[] = {2.0f, 2.0f};

    DistanceType euclidean_dist = calculate_euclidean_distance(vec1, vec2, dimension);
    DistanceType expected_euclidean = 1.4142135623731;

    assert(fabs(euclidean_dist - expected_euclidean) < 0.0001f);
    printf("\t✅ Euclidean distance test passed\n");

    DistanceType cosine_dist = calculate_cosine_distance(vec1, vec2, dimension);
    DistanceType expected_cosine = 2.220446049250313e-16f; // 1 - (32 / (sqrt(14) * sqrt(77))) = 0.025368

    assert(fabs(cosine_dist - expected_cosine) < 0.0001f);
    printf("\t✅ Cosine distance test passed\n");
}



int main() {
    printf("🧪 Testing Distance Calculation\n");
    test_distance();
    printf("🥳 ALL TESTS PASSED\n");

    return 0;
}