#include "array.h"
#include <assert.h>

typedef struct array {
        void **slots;
        int len;
        int capacity;
} array;

void expand(ray)
{
        void **temp_ray = malloc(sizeof(*temp_ray) *(ray->capacity * 2))
        for (int i = 0; i < ray->len; ++i)
        {
                temp_ray[i] = ray->slots[i];
        }
        ray->capacity *= 2;
        free(ray->slots);
        ray->slots = temp_ray;
}

array new_array() 
{
        array ray = malloc(sizeof(*ray));
        ray->slots = malloc(sizeof(void *) * 23);
        ray->len = 0;
        ray->capacity = 23;

        return ray;
}

void free_array(array ray)
{
        assert(ray);
        free(ray->slots);
        free(ray);
}

void *get_at(array ray, int i)
{
        assert(i < ray->len);

        return (ray->slots)[i];
}

void put_at(array ray, void *val, int i)
{
        assert(i < ray->len);

        (ray->slots)[i] = val;
}

void push(array ray, void *val)
{
        if (ray->len == ray->capacity)
                expand(ray);

        (ray->slots)[ray->len - 1] = val;
}

void *pop(array ray, void *val)
{
        assert(ray->len > 0);

        return (ray->slots)[ray->len - 1];
}

