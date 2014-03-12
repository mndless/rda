/*model.c*/

#include "ray.h"

static void model_load_entities(
FILE *in,
model_t *model)
{

  char entityname[NAME_LEN];
  int count = 0;

   memset(entityname, 0, sizeof(entityname));

/* Here entityname should be one of "material", */

count = fscanf(in, "%s", entityname);
while (count == 1)
{

if (strcmp(entityname, "material") == 0)
{

   material_init(in, model, 0);
    count += 1;

}
/* "light", "plane", "camera", etc */

else if (strcmp(entityname, "plane") == 0)
{

   plane_init(in, model, 0);
    count +=1;
}

else if (strcmp(entityname, "camera") == 0)
{
   camera_init(in, model, 0);
    count += 1;
}

else if (strcmp(entityname, "sphere") == 0)
{
   sphere_init(in, model, 0);
    count += 1;
}

else
{
   fprintf(stderr, "Bad model entity: %s \n", entityname);
	exit(1);

}


/*process one entity and read next entity name*/

count = fscanf(in, "%s", entityname);
assert(count != 0);
   }
}



/* Init model data */
model_t *model_init(
FILE *in)
{
   model_t *model = malloc(sizeof(model_t));
   assert(model != NULL);
   memset(model, 0, sizeof(model_t));
   
/* Create and initialize material structure list */

   model->mats = list_init();
   assert(model->mats != NULL);

/* Create and initialize visible object structure list */

   model->objs = list_init();
   assert(model->objs != NULL);

/* Create and initialize light structure list */

   /*model->lgts = list_init();
   assert(model->lgts != NULL);*/

/* read in the camera, materials, objects, lights */

   model_load_entities(in, model);
   return(model);
}

/* dump model data */
void model_print(
model_t *model,
FILE *out)
{
  
   camera_print(model->cam, out);
   material_list_print(model, out);
   object_list_print(model, out);
}
