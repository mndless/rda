
#include "ray.h"

int sphere_load_attributes(
FILE *in,
sphere_t *sph)
{
char attrib_name[16];
int count = 0; // number of items read
int attrcount = 0; // total number of attributes


/* Read first attribute name... */

	count = fscanf(in, "%s", attrib_name);
	assert(count == 1);

/* '}' means end of the material definition */

while (attrib_name[0] != '}')
{



  if (strcmp(attrib_name, "center") == 0)
{
	count = fscanf(in, "%lf %lf %lf",
	  &sph->center[X], &sph->center[Y], &sph->center[Z]);

	assert(count == 3);
	attrcount += 1;
}
else if (strcmp(attrib_name, "scale") == 0)
{

	count = fscanf(in, "%lf %lf %lf", 
	  &sph->scale[X], &sph->scale[Y], &sph->scale[Z]);
	
	assert(count == 3);
	attrcount += 1;

}
else if (strcmp(attrib_name, "radius") == 0)
{
	count = fscanf(in, "%lf", &sph->radius);
	assert(count == 1);
	attrcount =+ 1;
}

else
{
	fprintf(stderr, "Bad sphere attribute: %s \n", attrib_name);
	exit(1);
}
/* Read next attribute name */

	fscanf(in, "%s", attrib_name);
}
	return (attrcount);

}

void sphere_print(
object_t *obj,
FILE *out)
{

   sphere_t *sph;

   object_print(obj, out);
   sph = obj->priv;

   fprintf(out, "center");
   fprintf(out, "%8.1lf %8.1lf %8.1lf\n", 
   sph->center[X], sph->center[Y], sph->center[Z]);

   fprintf(out, "radius");
   fprintf(out, "%8.1lf\n", 
   sph->radius);
   
   fprintf(out, "\n");



}

void sphere_init(
FILE *in,
model_t *model,
int attrmax) // maximum number of attributes
{
sphere_t *sph;
object_t *obj;
int count;
{

   object_init(in, model);

   obj = (object_t*)list_get_entity(model->objs);
   sph = malloc(sizeof(sphere_t));
   obj->priv = sph;
   strcpy(obj->obj_type, "sphere");
   count = sphere_load_attributes(in, sph);
   /*assert(count == 2);*/


   obj->printer = sphere_print;
   obj->hits = sphere_hits;


}

}

double sphere_hits(
object_t *obj,
vec_t base, /* ray base */
vec_t dir) /* unit direction vector */
{

sphere_t *sph;
vec_t new_base;
vec_t hitpoint_minus_center;
vec_t temp, hitpoint_location;


/* extract sph pointer from object structure */

sph = obj->priv;

   vec_diff(sph->center, base, new_base);
   
   double a = vec_dot(dir, dir);
   double b = (vec_dot(new_base, dir)) * 2;
   double c = (vec_dot(new_base, new_base)) - 
	      (sph->radius * sph->radius);
   double a_times_c = a * c;
   double b_squared = b * b;
   double discriminate = (b_squared - 4 * a_times_c);

if(discriminate <= 0)
	return (-1);

   double sqrt_discriminate = sqrt(discriminate);
   double dist = (-b - sqrt_discriminate)/ (2 * a);

   /*hitpoint location*/

   vec_unit(dir, dir);
   vec_scale(dist, dir, temp);
   vec_sum(base, temp, hitpoint_location);

   /*normal*/

   vec_diff(sph->center, hitpoint_location, hitpoint_minus_center);
   vec_unit(hitpoint_minus_center, obj->last_normal);

   vec_copy(hitpoint_location, obj->last_hit);

   
   
   	return (dist);
}


