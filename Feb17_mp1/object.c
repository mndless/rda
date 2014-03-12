/* object.c */

#include "ray.h"

double     object_no_hit(
object_t   *obj,      /* Candidate object    */
vec_t      base,     /* Start point of ray  */
vec_t      dir)      /* MUST be unit vector */
{
   assert(obj->cookie == OBJ_COOKIE);
   fprintf(stderr, "Object %s failed to provide hit func \n",
                    obj->obj_name);

   return(-1.0);    // negative distance means miss.
}

/**/
void object_print(
object_t *obj,
FILE     *out)
{

//material_t *mat;

   assert(obj->cookie == OBJ_COOKIE);

	fprintf(out, "%4s", obj->obj_type);
	fprintf(out, "%8s\n", obj->obj_name);
	fprintf(out, "material");
	fprintf(out, "%10s\n",obj->mat->name);



}

/**/
void object_list_print(
model_t *model,
FILE *out)
{
   object_t *obj;

/* For each object in model->objs invoke polymorphic printer */


   list_reset(model->objs);
   while(list_not_end(model->objs))
   {
	obj = list_get_entity(model->objs);
	obj->printer(obj, out);
	list_next_link(model->objs);
   }


}

void     object_init(
FILE       *in,
model_t    *model)
{
   object_t   *obj;
   material_t *mat;
   char buf[NAME_LEN];
   int count = 0;

/* Create a new object structure and zero it */

   obj = malloc(sizeof(object_t));
   assert(obj != NULL);

   memset(obj, 0, sizeof(object_t));
   obj->cookie = OBJ_COOKIE;

/* Read the descriptive name of the object */
/* left_wall, center_sphere, etc.          */

   count = fscanf(in, "%s", obj->obj_name);
   assert(count == 1);

/* Consume the delimiter { */

   count = fscanf(in, "%s", buf);
   assert(buf[0] == '{');

/* The first attribute must be material */

   count = fscanf(in, "%s", buf);
   assert(count == 1);
   assert(strcmp(buf, "material") == 0);


/* Now get the name of the material (blue, green, etc) */

   count = fscanf(in, "%s", buf);
   assert(count == 1);

/* If the material is defined,  save a pointer to the */
/* mat structure in the object structure. Failure to  */
/* find the material is a fatal error.                */

   mat = material_getbyname(model, buf);
   assert(mat != NULL);

   obj->mat = mat;

/* Initialize default handlers */

   obj->printer  = object_print;
   obj->hits     = object_no_hit;
   obj->ambient  = material_getamb;
   obj->diffuse  = material_getdiff;
   obj->specular = material_getspec;

/* Finally add the object to the list */

   list_add(model->objs, (void *)obj);

}

