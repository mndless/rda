#include "ray.h"


int camera_load_attributes(
FILE *in,
camera_t *cam)
{

char attrib_name[16];
int count = 0; // number of items read
int attrcount = 0; // total number of attributes

/* First read camera name string into cam->name */

	count = fscanf(in, "%s", cam->name);
	assert(count == 1);
/* Now consume "{" */

	count = fscanf(in, "%s", attrib_name);
	assert(count == 1);
	assert(attrib_name[0] == '{');

/* Read first attribute name... */

	
	count = fscanf(in, "%s", attrib_name);
	assert(count == 1);

/* '}' means end of the camera definition */

while (attrib_name[0] != '}')
{
  if (strcmp(attrib_name, "pixeldim") == 0)

{
	count = fscanf(in, "%d %d",
	  &cam->pixel_dim[X], &cam->pixel_dim[Y]);

	assert(count == 2);
	attrcount += 1;
}
else if (strcmp(attrib_name, "worlddim") == 0)
{

	count = fscanf(in, "%lf %lf", 
	  &cam->world_dim[X], &cam->world_dim[Y]);
	
	assert(count == 2);
	attrcount += 1;

}
else if (strcmp(attrib_name, "viewpoint") == 0)
{

	count = fscanf(in, "%lf %lf %lf", 
	  &cam->view_point[X], &cam->view_point[Y], 
          &cam->view_point[Z]);

	assert(count == 3);
	attrcount += 1;
}

else
{

	fprintf(stderr, "Bad camera attribute: %s \n", attrib_name);
	exit(1);
}


/* Read next attribute name */

	fscanf(in, "%s", attrib_name);
}
	return(attrcount);
}

void camera_init(
FILE *in,
model_t *model,
int attrmax)
{

int   attribcount;
  camera_t *cam;

/* Allocate camera structure and store cookie code */

  	cam = (camera_t *)malloc(sizeof(camera_t));
  	cam->cookie = CAM_COOKIE;

/* Read attributes into camera data structure */

	attribcount = camera_load_attributes(in, cam);
	assert(attribcount == 3);

/* Allocate a pixmap to hold the ppm image data */

	cam->pixmap = malloc(sizeof(irgb_t)
        * cam->pixel_dim[X]  *  cam->pixel_dim[Y]);

/* Save camera pointer in model structure */

	model->cam = cam;

}

void camera_print(
camera_t *cam,
FILE *out)
{

	assert(cam->cookie == CAM_COOKIE);

	fprintf(out, "camera");
	fprintf(out, "%10s\n", cam->name);


	fprintf(out, "pixeldim ");
	fprintf(out, "%8d %8d\n", cam->pixel_dim[X], 
	cam->pixel_dim[Y]);

	fprintf(out, "worlddim ");
	fprintf(out, "%8.1lf %8.1lf\n", cam->world_dim[X], 
	cam->world_dim[Y]);

	fprintf(out, "viewpoint");
	fprintf(out, "%8.1lf %8.1lf %8.1lf\n", 
	  cam->view_point[X], cam->view_point[Y], 
	  cam->view_point[Z]); 
	fprintf(out, "\n");

}

void camera_getdir(
camera_t *cam,
int x, /* pixel coordinates */
int y,
vec_t uvec) /* Unit vector to be filled in */
{

vec_t world;
vec_t direction;

	assert(cam->cookie == CAM_COOKIE);
/*(1) convert pixel coordinates to world screen coordinates*/

	world[X] = cam->world_dim[X] * x / (cam->pixel_dim[X] - 1.0);
	world[Y] = cam->world_dim[Y] * y / (cam->pixel_dim[Y] - 1.0);
	world[Z] = 0.0;

/*(2) compute vector from viewpoint to world screen coordinate*/
	
	vec_diff(cam->view_point, world, direction);

/*(3) convert vector to unit length vector*/

	vec_unit(direction, uvec);
}

void camera_store_pixel(
camera_t *cam,
int x,
int y,
drgb_t pix)
{

int row, col;
irgb_t    *ipix;

assert(cam->cookie == CAM_COOKIE);

row = cam->pixel_dim[1] - y - 1;
   col = x;	
	
	pix[R] = pix[R] * 255 + 0.5;
	pix[G] = pix[G] * 255 + 0.5;
	pix[B] = pix[B] * 255 + 0.5;

if(pix[R] < 0.0) 
   pix[R] = 0.0;

if(pix[R] > 255.0)
   pix[R] = 255.0;

if(pix[G] < 0.0) 
   pix[G] = 0.0;

if(pix[G] > 255.0)
   pix[G] = 255.0;

if(pix[B] < 0.0) 
   pix[B] = 0.0;

if(pix[B] > 255.0)
   pix[B] = 255.0;

ipix =  cam->pixmap + row * cam->pixel_dim[X] + col;	

	(*ipix)[R] = pix[R];	
	(*ipix)[G] = pix[G];  
	(*ipix)[B] = pix[B];	
}

void camera_write_image(
camera_t *cam,
FILE *out)
{

fprintf(out, "P6\n");
fprintf(out, "%d %d, 255\n",cam->pixel_dim[X],cam->pixel_dim[Y]);
fwrite(cam->pixmap, sizeof(irgb_t), 
cam->pixel_dim[X]*cam->pixel_dim[Y], out);

}
