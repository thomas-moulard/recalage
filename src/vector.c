/*
** vector.c for Recalage in /goinfre/recalage/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Sat Dec 10 15:44:15 2005 thomas moulard
** Last update Fri Dec 23 01:51:03 2005 thomas moulard
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "recalage.h"

/**
** d = a + b
*/
void			addvector(struct s_vector *d,
				  struct s_vector *a,
				  struct s_vector *b)
{
  d->x = a->x + b->x;
  d->y = a->y + b->y;
  d->z = a->z + b->z;
}

/**
** d = a - b
*/
void			subvector(struct s_vector *d,
				  struct s_vector *a,
				  struct s_vector *b)
{
  d->x = a->x - b->x;
  d->y = a->y - b->y;
  d->z = a->z - b->z;
}

/**
** d = a * b
** d: matrix
*/
void			multvectors(struct s_matrice	*d,
				    struct s_vector	*a,
				    struct s_vector	*b)
{
  init_matrice(d, 3, 3);
  d->data[0] = a->x * b->x;
  d->data[1] = a->x * b->y;
  d->data[2] = a->x * b->z;
  d->data[3] = a->y * b->x;
  d->data[4] = a->y * b->y;
  d->data[5] = a->y * b->z;
  d->data[6] = a->z * b->x;
  d->data[7] = a->z * b->y;
  d->data[8] = a->z * b->z;
}


/**
** Transform a vector into a quaternion
*/
void	vector2quaternion(struct s_quaternion *q, struct s_vector *v)
{
  q->s = 0.0;
  q->vec.x = v->x;
  q->vec.y = v->y;
  q->vec.z = v->z;
}


/**
** Computes the norm of a vector.
*/
double	vnorme(struct s_vector *v)
{
  return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}
