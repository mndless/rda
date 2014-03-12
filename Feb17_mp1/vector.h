/* Ashleigh Austin
	lab1 
	102 
		*/

/* vector.h */

/* This header file contains vector definitions and */
/* inline functions for 3 - D vector and matrix     */
/* operations                                       */

/* Three dimensional coordinate structures */

#define X 0
#define Y 1
#define Z 2

typedef double vec_t [3];

typedef double mtx_t[3][3];


/**/
/* Compute the vector sum  v3 = v2 + v1 */

static inline void vec_sum(
vec_t  v1,        /* Left input vector  */
vec_t  v2,        /* Right input vector */
vec_t  v3)        /* Output vector      */
{
   v3[X] = v1[X] + v2[X];
   v3[Y] = v1[Y] + v2[Y];
   v3[Z] = v1[Z] + v2[Z];
}

/**/
/* Compute the component wise product   */
/* v3 = v2 * v1                         */

static inline void vec_mult(
vec_t  v1,        /* Left input vector  */
vec_t  v2,        /* Right input vector */
vec_t  v3)        /* Output vector      */
{
  v3[X] = v2[X] * v1[X];
  v3[Y] = v2[Y] * v1[Y];
  v3[Z] = v2[Z] * v1[Z];


}


/**/
/* Compute the vector difference  v3 = v2 - v1 */

static inline void vec_diff(
vec_t   v1,        /* Left input vector  */
vec_t   v2,        /* Right input vector */
vec_t   v3)        /* Output vector      */
{

  v3[X] = v2[X] - v1[X];
  v3[Y] = v2[Y] - v1[Y];
  v3[Z] = v2[Z] - v1[Z];

}

/**/
/* Compute the inner (dot) product:  prod = v1 dot v2 */

static inline double vec_dot(
vec_t v1,
vec_t v2)
{
  double prod;
  prod = (v1[X] * v2[X]) + (v1[Y] * v2[Y]) + (v1[Z] * v2[Z]); 

  return prod;
}

/**/
/* Compute the length of the vector v1         */

static inline double vec_len(
vec_t   v1)        /* Input vector  */
{
  double len;
  len = sqrt(vec_dot(v1, v1));

  return len;

}

/* Computer v2 = s * v1 where s is a scalar */

static inline void vec_scale(
double s,
vec_t   v1,
vec_t   v2)
{

  v2[X] = s * v1[X];
  v2[Y] = s * v1[Y];
  v2[Z] = s * v1[Z];

}

/**/
/* Compute v2, a unit vector in the direction of v1 */

static inline void vec_unit(
vec_t v1,
vec_t v2)
{

  double scale = 1.0 / vec_len(v1);
  vec_scale(scale, v1, v2);

/*
double len = vec_len(v1);
v2[X] = v1[X] / len;
v2[Y] = v1[Y] / len;
v2[Z] = v1[Z] / len;
*/
}

/* Copy vector v1 to vector v2 */

static inline void vec_copy(
vec_t v1,
vec_t v2)
{
  v2[X] = v1[X];
  v2[Y] = v1[Y];
  v2[Z] = v1[Z];

}

/* Read values into vector v1 and return */
/* the number of values read             */

static inline int vec_read(
FILE  *in,
vec_t v1)
{

  fscanf(in, "%lf %lf %lf", &v1[X], &v1[Y], &v1[Z]);  

  return 0;
}

/**/
/* Print the contents of a vector using  %8.3lf format */
/* Print a newline after the last element.  Output     */
/* should appear as it does in the lab assignment      */

static inline void vec_print(
FILE  *out,
char  *label,
vec_t vec)
{	
	
	fprintf(out, "%s %8.3lf %8.3lf %8.3lf\n", label, vec[X], vec[Y], vec[Z]);
}

static inline void vec_cross(
vec_t v1, /* Left input vector */
vec_t v2, /* Right input vector */
vec_t v3) /* Output vector */
{
   vec_t temp;

  temp[X] = ((v1[Y] * v2[Z]) - (v1[Z] * v2[Y]));
  temp[Y] = ((v1[Z] * v2[X]) - (v1[X] * v2[Z]));
  temp[Z] = ((v1[X] * v2[Y]) - (v1[Y] * v2[X]));

   vec_copy(temp, v3);

}

static inline void vec_project(
vec_t n, /* plane normal */
vec_t v, /* input vector */
vec_t p) /* projected vector */
{

   double ndotv = vec_dot(n, v);

   vec_t temp;
   vec_scale(ndotv, n, temp);
   vec_diff(temp, v, p);
}

static inline void vec_reflect(
vec_t n, /* surface normal */
vec_t w, /* incoming ray vector */
vec_t v) /* reflected vector */
{

  vec_t u, two_times_n, v_multiplication;
  vec_scale(-1.0, w, u);
  double udotn = vec_dot(u, n);
  vec_scale(2.0, n, two_times_n);
  vec_scale(udotn, two_times_n, v_multiplication);
  vec_diff(u, v_multiplication, v);

}

static inline void vec_xform(
mtx_t m,
vec_t v1,
vec_t v2)
{

  vec_t work;

   

   work[0] = vec_dot(m[0], v1);
   work[1] = vec_dot(m[1], v1);
   work[2] = vec_dot(m[2], v1);

  vec_copy(work, v2);

}

static inline void mtx_transpose(
mtx_t m1,
mtx_t m2)
{

mtx_t mwork;

mwork[0][0] = m1[0][0];
mwork[0][1] = m1[1][0];
mwork[0][2] = m1[2][0];
mwork[1][0] = m1[0][1];
mwork[1][1] = m1[1][1];
mwork[1][2] = m1[2][1];
mwork[2][0] = m1[0][2];
mwork[2][1] = m1[1][2];
mwork[2][2] = m1[2][2];

vec_copy(mwork[0], m2[0]);
vec_copy(mwork[1], m2[1]);
vec_copy(mwork[2], m2[2]);


}




