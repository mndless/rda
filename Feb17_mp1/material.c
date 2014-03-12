/* material.c */

#include "ray.h"

void material_load_attributes(
FILE *in,
material_t *mats)
{

/* Use same basic approach as camera_load_attributes()  */

  char attrib_name[16];
int count = 0; // number of items read
int attrcount = 0; // total number of attributes

/* First read material name string into cam->name */

	count = fscanf(in, "%s", mats->name);
	assert(count == 1);
/* Now consume "{" */

	count = fscanf(in, "%s", attrib_name);
	assert(count == 1);
	assert(attrib_name[0] == '{');

/* Read first attribute name... */

	count = fscanf(in, "%s", attrib_name);
	assert(count == 1);

/* '}' means end of the material definition */

while (attrib_name[0] != '}')
{



  if (strcmp(attrib_name, "ambient") == 0)
{
	count = fscanf(in, "%lf %lf %lf",
	  &mats->ambient[R], &mats->ambient[G], &mats->ambient[B]);

	assert(count == 3);
	attrcount += 1;
}
else if (strcmp(attrib_name, "diffuse") == 0)
{

	count = fscanf(in, "%lf %lf %lf", 
	  &mats->diffuse[R], &mats->diffuse[G], &mats->diffuse[B]);
	
	assert(count == 3);
	attrcount += 1;

}
else if (strcmp(attrib_name, "specular") == 0)
{

	count = fscanf(in, "%lf %lf %lf", 
	  &mats->specular[R], &mats->specular[G], &mats->specular[B]);

	assert(count == 3);
	attrcount += 1;
}

else
{
	fprintf(stderr, "Bad material attribute: %s \n", attrib_name);
	exit(1);
}
/* Read next attribute name */

	fscanf(in, "%s", attrib_name);
}
	

}


/**/
/* Create a new material description */

void material_init(
FILE       *in,
model_t    *model,
int        attrmax)    // ignore
{
   material_t *mat;

/* malloc() a material_t structure, use memset() to */
/* initialize it to 0 and store the MAT_COOKIE      */


/* Load attributes as in camera.c                      */
/* Unlike the camera the number of attributes is       */
/* optional.   Attributes should be initialized to 0.0 */
	
   
/* Ask list_add to add the material entity to the end  */
/* of the mats list in the model structure. */

   mat = (material_t *)malloc(sizeof(material_t));
   memset(mat, 0, sizeof(material_t));
   mat->cookie = MAT_COOKIE;
   material_load_attributes(in, mat);
   list_add(model->mats, mat);

}

material_t *material_getbyname(
model_t *model,
char    *name)    // requested material name (e.g. yellow)
{

/*assert(mat->cookie == MAT_COOKIE);*/
   material_t *mat;

   list_reset(model->mats);
   while(list_not_end(model->mats))
   {
	mat = list_get_entity(model->mats);
	if(strcmp(mat->name, name) == 0)
	  return(mat);
	list_next_link(model->mats);
   }

return 0;
}
static inline void material_print(
material_t *mat,
FILE *out)
{
   assert(mat->cookie == MAT_COOKIE);


	fprintf(out, "material ");
	fprintf(out, "%6s\n", mat->name);


	fprintf(out, "ambient ");
	fprintf(out, "%5.1lf %5.1lf %5.1lf\n", mat->ambient[R], mat->ambient[G], mat->ambient[B]);

	fprintf(out, "diffuse ");
	fprintf(out, "%5.1lf %5.1lf %5.1lf\n", mat->diffuse[R], mat->diffuse[G], mat->diffuse[B]);

	fprintf(out, "specular");
	fprintf(out, "%5.1lf %5.1lf %5.1lf\n", 
	  mat->specular[R], mat->specular[G], mat->specular[B]); 
	fprintf(out, "\n");
	fprintf(out, "\n");


}


/**/
/* Produce a formatted dump of the material list */

void material_list_print(
model_t *model,
FILE *out)
{
   material_t *mat;

   list_reset(model->mats);
   while(list_not_end(model->mats))
   {
	mat = list_get_entity(model->mats);
	material_print(mat, out);
	list_next_link(model->mats);
   }

}

void material_getamb(
object_t *obj,
material_t *mat,
drgb_t      dest)   /* fill in ambient reflectivity here */
{
  
   pix_copy(mat->ambient, dest);
}

void material_getdiff(
object_t *obj,
material_t *mat,
drgb_t dest) /* diffuse here */
{
   pix_copy(mat->diffuse, dest);
}


void material_getspec(
object_t *obj,
material_t *mat,
drgb_t dest) /* specular here */
{
   pix_copy(mat->specular, dest);
}




