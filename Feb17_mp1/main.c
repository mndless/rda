/* main.c */

#include "ray.h"

int main(
int argc,
char *argv[])
{
   model_t *model;

/* Load and dump the model */

   model = model_init(stdin);
   assert(model != NULL);

   model_print(model, stderr);

#if 0
/* Raytrace the image */

   image_create(model);

#endif

   return(0);
}

