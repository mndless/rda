/*raytrace.c*/

#include "ray.h"


object_t *find_closest_object(
list_t *list, /* Model structure */
vec_t base, /* Base of ray (viewpoint) */
vec_t dir, /* unit direction of ray */
object_t *last_hit, /* object last hit */
double *retdist) /* store dist to hit point here */
{
   object_t *minobj = NULL;
   double mindist = -1.0;
   double dist;

   list_reset(list);
   while(list_not_end(list))
   {
	object_t *obj = list_get_entity(list);

	   if(obj == last_hit)
	   {

		list_next_link(list);
		continue;

	   }
		
	   dist = obj->hits(obj, base, dir);

	   if(dist >= 0.0)
	   {
	        if(dist < mindist || minobj == NULL)
	        {
	         mindist = dist;
	         minobj = obj;
	        }
	   }
		
	   list_next_link(list);
  }
   *retdist = mindist;
  return(minobj);
}



void ray_trace(
model_t *model,
vec_t base, /* location of viewer or previous hit */
vec_t dir, /* unit vector in direction of object */
drgb_t dpix, /* pixel return location */
double total_dist, /* distance ray has traveled so far */
object_t *last_hit) /* most recently hit object */
{

  object_t *closest;
  object_t *obj;
  //material_t *mat;
  double mindist;
  drgb_t thisray = {0.0, 0.0, 0.0};

/*Ask find_closest_object() to set the closest pointer
If it returns an object pointer*/

  closest = find_closest_object(model->objs, base, dir, closest, &mindist);   
    if(closest != NULL)
     {

        closest->ambient(obj, closest->mat, thisray);

       }

{
  #ifdef DBG_HIT
   fprintf(stderr, "%-12s HIT:(%5.1lf, %5.1lf, %5.1lf)",
   closest->obj_name,
   closest->last_hit[X],
   closest->last_hit[Y],
   closest->last_hit[Z]);
  #endif

/*use the objects polymorphic closest>
ambient() function copy the object's ambient
reflectivity to “thisray”*/

   
}
/*scale the values of “thisray” by 1 / distance to the closest object
add the value of “thisray” to pix*/
   
   thisray[0] = thisray[0] / mindist;
   thisray[1] = thisray[1] / mindist;
   thisray[2] = thisray[2] / mindist;

   dpix[0] = thisray[0] + dpix[0];
   dpix[1] = thisray[1] + dpix[1];
   dpix[2] = thisray[2] + dpix[2];

  #ifdef DBG_DRGB
   fprintf(stderr, "%-12s DRGB:(%5.2lf, %5.2lf, %5.2lf)",
   closest->objname, dpix[R], dpix[G], dpix[B]);
  #endif
}
