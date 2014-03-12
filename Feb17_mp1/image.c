
# include "ray.h"

void camera_store_pixel(
camera_t *cam,
int x,
int y,
drgb_t pix);

static inline void make_pixel(
model_t *model,
int x,
int y)
{

  vec_t raydir;
  drgb_t d_pix = {0.0, 0.0, 0.0};
  camera_t *cam = model->cam;

/* This function was written previously */

   camera_getdir(cam, x, y, raydir);

  #ifdef DBG_PIX

   fprintf(stderr, "\nPIX %4d %4d - ", y, x);

  #endif

/* The ray_trace function determines the pixel color in */
/* d_rgb units.. The last two parameters are used ONLY */
/* in the case of specular (bouncing) rays which we are */
/* not doing yet. */

   ray_trace(model, cam->view_point,
   raydir, d_pix, 0.0, NULL);

/* This function must convert the pixel value from drgb_t */
/* [0.0, 1.0] to irgb_t (0, 255) and to store it in the */
/* “upside down” location in the pixmap */

   camera_store_pixel(cam, x, y, d_pix);

return;
}

static inline void make_row(
model_t *model,
int y)
{
  int x;
   camera_t *cam = model->cam;
  for (x = 0; x < cam->pixel_dim[0]; x++)
  {
   make_pixel(model, x, y);
  }

}

void image_create(
model_t *model)
{
  int y;
  camera_t *cam = model->cam;
  

/* Fire ray(s) through each pixel in the window */

  for (y = 0; y < cam->pixel_dim[1]; y++)
  {
   make_row(model, y);
  }
/* Ask camera_write_image to ppm image */

  camera_write_image(model->cam, stdout);
}






