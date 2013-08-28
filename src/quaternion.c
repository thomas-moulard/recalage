/*
** quaternion.c for Recalage in /goinfre/recalage/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Wed Dec 14 21:11:02 2005 thomas moulard
** Last update Fri Dec 23 01:52:57 2005 thomas moulard
*/
#include <stdio.h>
#include <assert.h>
#include "recalage.h"

/**
** Initialize a quaternion.
*/
void			init_quaternion(struct s_quaternion	*q)
{
  q->s = q->vec.x = q->vec.y = q->vec.z = 0.0;
}

/**
** q = q2 * q3
*/
void			mult_quaternion(struct s_quaternion	*q,
					struct s_quaternion	*q2,
					struct s_quaternion	*q3)
{
  q->s = ((q2->s * q3->s) - (q2->vec.x * q3->vec.x) - (q2->vec.y * q3->vec.y) -
	  (q2->vec.z * q3->vec.z));
  q->vec.x = ((q2->vec.x * q3->s) + (q2->s * q3->vec.x) + (q2->vec.y *
							  q3->vec.z) -
	      (q2->vec.z * q3->vec.y));
  q->vec.y = ((q2->vec.y * q3->s) + (q2->s * q3->vec.y) + (q2->vec.z *
							  q3->vec.x) -
	      (q2->vec.x * q3->vec.z));
  q->vec.z = ((q2->vec.z * q3->s) + (q2->s * q3->vec.z) +
	      (q2->vec.x * q3->vec.y) - (q2->vec.y * q3->vec.x));
}

/**
** Computes the opposite of a quaternion
*/
void			opp_quaternion(struct s_quaternion	*q,
				       struct s_quaternion	*q2)
{
  q->s = q2->s;
  q->vec.x = -q2->vec.x;
  q->vec.y = -q2->vec.y;
  q->vec.z = -q2->vec.z;
}

/**
** Convert a 4x1 matrix to a quaternion
*/
void	matrice2quaternion(struct s_quaternion *q, struct s_matrice *m)
{
  assert((m->w == 1) && (m->h == 4));

  q->s = m->data[0];
  q->vec.x = m->data[1];
  q->vec.y = m->data[2];
  q->vec.z = m->data[3];
}


/**
** Print the quaternion on the standard output.
*/
void			aff_quaternion(struct s_quaternion *q, char *str)
{
  fprintf(stderr, "-----\n%s\n", str);
  fprintf(stderr, "w: %f\n", q->s);
  fprintf(stderr, "x: %f\n", q->vec.x);
  fprintf(stderr, "y: %f\n", q->vec.y);
  fprintf(stderr, "z: %f\n", q->vec.z);
  fprintf(stderr, "-----\n");
}
