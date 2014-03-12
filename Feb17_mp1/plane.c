/* plane.c */

#include "ray.h"


/**/
/* Determine if a vector projected from location *base  */
/* in direction *dir hits the plane.. If so the return */
/* value is the distance from the base to the point of  */
/* contact.                                             */

double  plane_hits(
object_t  *obj,
vec_t     base,      /* ray base              */
vec_t     dir)       /* unit direction vector */
{
   plane_t *pln;
   double temp, dist;
   double ndotq, ndotb, ndotd, diff;
   vec_t hitpoint_location;

   assert(obj->cookie == OBJ_COOKIE);

/* extract pln pointer from object structure */

pln = obj->priv;

/* We will use the following notation in the comments below */
/*  Q = point on the plane  (plane attribute )              */
/*  N = normal to the plane (plane attribute )              */
/*  B = base of ray (input parameter )                      */
/*  D = direction of ray                                    */

/*  ndotd = N dot D */
/*  ndotb = N dot B */
/*  ndotq = N dot Q --- which was precomputed in plane_init */
/*  dist  = signed distance from base to hitpoint location  */


/* Compute ndotd and if 0 return(-1.0); */


   temp = vec_dot(pln->normal, dir);
   if(temp == 0)	
	return (-1.0);



/* Compute ndotb */


   vec_dot(pln->normal, base);


/* Compute dist = (ndotq - ndotb) / ndotd;  */

   ndotq = pln->ndotq;
   ndotb = vec_dot(pln->normal, base);
   ndotd = vec_dot(pln->normal, dir);
   diff = ndotq - ndotb;
   

   dist = diff / ndotd;


/* If dist <= 0.0 return(-1.0); */


   if(dist <= 0.0)
	return (-0.1);



/* Compute location of hit point by scaling dir by dist and */
/* adding to base                                           */

   vec_scale(dist, dir, hitpoint_location);
   vec_sum(hitpoint_location, base, hitpoint_location);


/* if hitpoint_location[Z]  is postive  return(-1).         */


   if(hitpoint_location[Z] > 0)
	return (-1);


/* Copy hitpoint_location to obj->last_hit                 */
/* and  pln->normal to obj->last_normal                    */
  
  vec_copy(hitpoint_location, obj->last_hit);
  vec_copy(pln->normal, obj->last_normal);

   return (dist);
}

void plane_print(
object_t *obj,
FILE *out)
{
   plane_t *pln;

   object_print(obj, out);
   pln = obj->priv;
   
   fprintf(out, "normal");
   fprintf(out, "%8.1lf %8.1lf %8.1lf\n", 
   pln->normal[X], pln->normal[Y], pln->normal[Z]);

   fprintf(out, "point");
   fprintf(out, "%9.1lf %8.1lf %8.1lf\n", 
   pln->point[X], pln->point[Y], pln->point[Z]);



}

int plane_load_attributes(
FILE    *in,
plane_t *pln)
{

/* Use same basic approach as camera_load_attributes()  */

  char attrib_name[16];
int count = 0; // number of items read
int attrcount = 0; // total number of attributes


/* Read first attribute name... */

	count = fscanf(in, "%s", attrib_name);
	assert(count == 1);

/* '}' means end of the material definition */

while (attrib_name[0] != '}')
{



  if (strcmp(attrib_name, "normal") == 0)
{
	count = fscanf(in, "%lf %lf %lf",
	  &pln->normal[X], &pln->normal[Y], &pln->normal[Z]);

	assert(count == 3);
	attrcount += 1;
}
else if (strcmp(attrib_name, "point") == 0)
{

	count = fscanf(in, "%lf %lf %lf", 
	  &pln->point[X], &pln->point[Y], &pln->point[Z]);
	
	assert(count == 3);
	attrcount += 1;

}

else
{
	fprintf(stderr, "Bad plane attribute: %s \n", attrib_name);
	exit(1);
}
/* Read next attribute name */

	fscanf(in, "%s", attrib_name);
}
	return(attrcount);
}







/**/
/* Create a new plane object and initialize it */

void plane_init(
FILE *in,
model_t *model,
int  attrmax)
{
   plane_t  *pln;
   object_t *obj;

  int       count;

/* Call the object_init()function to create the object_t */
/* and process the "material" attribute                  */

   object_init(in, model);
   

/* Use list_get_entity() to make obj point to the newly  */
/* created object_t structure.Your  list_add() function */
/* MUST set current to the last element in the list for */
/* this to work correctly.                              */

  obj = (object_t*)list_get_entity(model->objs);

/* malloc a plane_t structure and set the priv pointer */
/* in the object_t structure to point to the plane_t   */

   pln = malloc(sizeof(plane_t));
   obj->priv = pln;

/* Store the word "plane" in the object_type field of   */
/* the object_t structure. Use the strcpy() function    */

   strcpy(obj->obj_type, "plane");

/* Ask plane_load_attributes to load the attributes */
/* Attributes are normal and point                  */

   count = plane_load_attributes(in, pln);
   assert(count == 2);

/* Setup polymorphic function pointers in object_t */


   obj->printer = plane_print;
   obj->hits = plane_hits;




/* pre-compute ndotq                                 */

   pln->ndotq = vec_dot(pln->point, pln->normal);




}



