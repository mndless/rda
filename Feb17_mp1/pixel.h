/* pixel.h */

/* Two pixel value structures are used                   */
/* Computations are done in the double precision domain  */
/* where 0.0 means black and 1.0 means maximum intensity */
/* The raytracing algorithm can DEFINITELY produce       */
/* pixel values that exceed 1.0 scale and then clamp     */
/* them before assigning them to irgb_types              */

#define R 0
#define G 1
#define B 2

typedef double drgb_t[3];

/* The .ppm file requires the usual r-g-b values in the  */
/* range 0-255.  This structure maps one of them.        */

typedef unsigned char irgb_t[3];

/* Computer p2 = s * p1 where s is a scalar */

static inline void pix_scale(
double  s,
drgb_t  p1,
drgb_t  p2)
{
   p2[R] = s * p1[R];
   p2[G] = s * p1[G];
   p2[B] = s * p1[B];
}

/* Compute componentwise product of two rgb values */

static inline void pix_prod(
drgb_t  p1,
drgb_t  p2,
drgb_t  p3)
{
   p3[R] = p1[R] * p2[R];
   p3[G] = p1[G] * p2[G];
   p3[B] = p1[B] * p2[B];
}

/* Compute componentwise sum of two rgb values */

static inline void pix_sum(
drgb_t  p1,
drgb_t  p2,
drgb_t  p3)
{
   p3[R] = p1[R] + p2[R];
   p3[G] = p1[G] + p2[G];
   p3[B] = p1[B] + p2[B];
}

/* Compute componentwise sum of two rgb values */

static inline void pix_copy(
drgb_t  p1,
drgb_t  p2)
{
   p2[R] = p1[R];
   p2[G] = p1[G];
   p2[B] = p1[B];
}



