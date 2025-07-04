#include <stdio.h>
#include "vector.h"

#define TO_BOOL(x) ((x) ? "true" : "false")

struct data_t  // Example structure to use with xvector
{
    int value;
};


int main(int argc, char *argv[]) {

    xvector(struct data_t*) v = NULL;

    struct data_t *data = malloc(sizeof(struct data_t));
    data->value = 42;
    xvector_push_back(v, (data));
    data = malloc(sizeof(struct data_t));    
    data->value = 43;
    xvector_push_back(v, (data));
    data = malloc(sizeof(struct data_t));    
    data->value = 44;
    xvector_push_back(v, (data));
    data = malloc(sizeof(struct data_t));    
    data->value = 41;
    xvector_insert(v, 0, (data));

    data = xvector_last(v);
    xvector_pop_back(v);
    free(data);

    printf("v[%d] = %d at pointer (%p)\n", 1, ((struct data_t*)xvector_at(v, 1))->value, v[1]);

    printf("v is Empty  = %s\n", TO_BOOL(xvector_empty(v)));
    for(int i = 0; i < xvector_size(v); i++)
        printf("v[%d] = %d at pointer (%p)\n", i, v[i]->value, v[i]);
    for(int i = 0; i < xvector_size(v); i++)
        free(v[i]);
    xvector_free(v);
    printf("v is Empty  = %s\n", TO_BOOL(xvector_empty(v)));

    return 0;
}