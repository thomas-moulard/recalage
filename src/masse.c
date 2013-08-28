/*
** masse.c for src in /u/a1/monner_m/rendu/moular_t-recalage/src
**
** Made by melanie monnereau
** Login   <monner_m@epita.fr>
**
** Started on  Fri Dec  9 04:40:10 2005 melanie monnereau
** Last update Fri Dec 23 01:44:32 2005 thomas moulard
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "recalage.h"

/**
** This function calculates the mass'center from the file .txt's picture
*/
struct s_vector		*masse_txt(struct s_recal *r)
{
  struct s_vector	*vec = NULL;
  long double		res_x = 0.0;
  long double		res_y = 0.0;
  long double		res_z = 0.0;
  int			i = 0;

  if (!(vec = malloc(sizeof (struct s_vector))))
    return NULL;
  for (i = 0; i < r->nb_pts; i++)
    {
      res_x += r->nuage[i].x;
      res_y += r->nuage[i].y;
      res_z += r->nuage[i].z;
    }
  vec->x = res_x / r->nb_pts;
  vec->y = res_y / r->nb_pts;
  vec->z = res_z / r->nb_pts;
  return vec;
}

/**
** This function calculates the mass'center of the projected point.
*/
struct s_vector		*masse_x(struct s_vector *x, struct s_recal *r)
{
  struct s_vector	*vec = NULL;
  long double		res_x = 0;
  long double		res_y = 0;
  long double		res_z = 0;
  int			i = 0;

  if (!(vec = malloc(sizeof (struct s_vector))))
    return NULL;
  while (i < r->nb_pts)
    {
      res_x = res_x + x[i].x;
      res_y = res_y + x[i].y;
      res_z = res_z + x[i].z;
      i++;
    }

  vec->x = res_x / r->nb_pts;
  vec->y = res_y / r->nb_pts;
  vec->z = res_z / r->nb_pts;
  return vec;
}
