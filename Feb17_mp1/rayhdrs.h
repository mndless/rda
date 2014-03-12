
/* == main.c == */

/* == camera.c == */

void camera_getdir(
camera_t *cam,
int      x,
int      y,
vec_t    dir);

void camera_setpix(
camera_t *cam,
int      x,
int      y,
drgb_t   pix);

/* Initialize viewpoint data */

void camera_init(
FILE *in,
model_t *model,
int  attrmax);

/* Dump the camera data */

void camera_print(
camera_t *cam,
FILE   *out);


void camera_write_image(
camera_t *cam,
FILE     *out);

/* == list.c == */

/* malloc a new list header and initialize it */

list_t *list_init(
void);

/* Add an element to the end of a list */

void list_add(
list_t *list,
void   *entity);

void list_reset(
list_t *list);

int list_not_end(
list_t *list);

void list_next_link(
list_t *list);

void *list_get_entity(
list_t *list);


/* == model.c == */

/* Init model data */

model_t *model_init(
FILE *in);

/* dump model data */

void model_print(
model_t *model,
FILE    *out);

/* == material.c == */

/* Create a new material description */

void material_init(
FILE       *in,
model_t    *model,
int        attrmax);

/* Produce a formatted dump of the material list */

void material_list_print(
model_t *model,
FILE *out);

/* Try to locate a material by name */

material_t *material_getbyname(
model_t *model,
char    *name);

void material_getamb(
object_t   *obj,
material_t *mat,
drgb_t    dest);

void material_getdiff(
object_t   *obj,
material_t *mat,
drgb_t    dest);

void material_getspec(
object_t   *obj,
material_t *mat,
drgb_t    dest);

/* == raytrace.c == */

/* This function traces a single ray and returns the composite */
/* intensity of the light it encounters                        */

void ray_trace(
model_t  *model,
vec_t     base,        /* location of viewer or previous hit */
vec_t     dir,         /* unit vector in direction of object */
drgb_t    pix,         /* pixel     return location          */
double   total_dist,   /* distance ray has traveled so far   */
object_t *last_hit);

/* == plane.c == */

void plane_print(
object_t *obj,
FILE *out);

/* Determine if a vector projected from location *base  */
/* in direction *dir hits the plane.. If so the return */
/* value is the distance from the base to the point of  */
/* contact.                                             */

double  plane_hits(
object_t *obj,
vec_t     base,      /* ray base              */
vec_t     dir);      /* unit direction vector */

/* Create a new plane object and initialize it */

void plane_init(
FILE *in,
model_t *model,
int  attrmax);

/* == object.c == */

/* Find the closest object intersection on the ray based */
/* at "base" and having direction "dir"                  */

object_t *find_closest_object(
list_t   *list,        /* Object list       */
vec_t     base,        /* Base of ray       */
vec_t     dir,         /* direction of ray  */
object_t *last_hit,    /* object last hit   */
double   *retdist);

/* Create a new object description */

void       object_init(
FILE       *in,
model_t    *model);

void object_list_print(
model_t *model,
FILE *out);

void object_print(
object_t *obj,
FILE *out);

/* == light.c == */

void light_getloc(
light_t *lt,
vec_t    loc);

void light_getemiss(
light_t *lt,
drgb_t   pix);

int  light_getvis(
light_t *lt,
vec_t    ir);

/* Create a new light description */
light_t *light_init(
FILE          *in,
model_t       *model,
int            attrmax);

/* Produce a formatted dump of the light list */

void light_list_print(
model_t *model,
FILE *out);

/* == image.c == */

/* This function is the driver for the raytracing procedure */

void image_create(
model_t  *model);

/* == illum.c == */

void rand_vec(
vec_t   in,
vec_t   out);

void illuminate(
model_t  *model,            /* object list                    */
object_t *hitobj,           /* object that was hit by the ray */
drgb_t    pixel);

/* == tplane.c == */


void tp_amb(
object_t *obj,
drgb_t  value);

void tp_diff(
object_t *obj,
drgb_t  value);

void tp_spec(
object_t *obj,
drgb_t  value);

/* The tiled plane is derived from the generic plane   */
/* Additional input includes the material name of the  */
/* alternate or background tile, the x-y dimension of  */
/* the tiling, and a vector that when projected into   */
/* the plane provides the x-direction of the tiling.   */

object_t *tplane_init(
FILE     *in,
model_t  *model);

object_t *triangle_init(
FILE     *in,
model_t  *model,
int      attrmax);

/* == sphere.c == */

void sphere_print(
object_t *obj,
FILE *out);

/* Create a new sphere object and initialize it */

void      sphere_init(
FILE *in,
model_t *model,
int  attrmax);

/* Determine if a vector projected from location *base  */
/* in direction *dir hits the sphere.. If so the return */
/* value is the distance from the base to the point of  */
/* contact.                                             */

double  sphere_hits(
object_t   *obj,
vec_t      base,
vec_t      dir);   /* MUST be unit vector */

/* == parser.c == */

/* Generalized attribute parser */
/* It returns a bit mask in which each possible attribute */
/* is represented by a bit on exit the attributes that    */
/* have been found will have their bit = 1                */

int parser(
FILE    *in,
pparm_t *pct,         /* parser control table                */
int      numattrs,    /* number of legal attributes          */
int      attrmax);

/* == ellipse.c == */

void ellipse_print(
object_t *obj,
FILE *out);

/* Create a new ellipse object and initialize it */

object_t *ellipse_init(
FILE *in,
model_t *model,
int  attrmax);

/* == pplane.c == */

void pplane_print(
object_t *obj,
FILE *out);

void      pplane_init(
FILE    *in,
model_t *model,
int  attrmax);
