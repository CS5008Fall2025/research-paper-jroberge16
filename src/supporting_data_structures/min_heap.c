#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "vector.h"


// Supporting Functions

int __get_parent(int i){
    return (i-1)/2;
}

int __get_left_child(int i){
    return (2*i + 1);
}

int __get_right_child(int i){
    return(2*i +2);
}
