/*
** projection.c for Recalage in /goinfre/recalage/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Wed Dec 14 01:23:13 2005 thomas moulard
** Last update Fri Dec 23 01:50:23 2005 thomas moulard
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "recalage.h"

/*
** This function calculates the integers'coordonnees whom are in the file .pgm
*/
void			coord_pgm(struct s_recal *r, struct s_vector *coord)
{
  int			pos = 0;

  for (pos = 0; pos < r->nb_int; pos++)
    {
      coord[pos].x = pos % r->length_pgm;
      coord[pos].y = pos / r->length_pgm;
      coord[pos].z = r->image[pos];
    }
}

/*
** This function fills an array with norms of each vector which is the result
** of x - P_i
*/
void			tab_normes(struct s_recal	*r,
				   struct s_vector	*coord,
				   double		*d,
				   int			i)
{
  int			pos;
  struct s_vector	res;

  for (pos = 0; pos < r->nb_int; pos++)
    {
      res.x = coord[pos].x - r->nuage[i].x;
      res.y = coord[pos].y - r->nuage[i].y;
      res.z = coord[pos].z - r->nuage[i].z;
      d[pos] = res.x * res.x + res.y * res.y + res.z * res.z;
    }
}

/*
** This function returns the X_i 's array
*/

void			vector_min(struct s_recal *r)
{
  double		*d;
  int		        i;
  int			j;
  double		min;
  int			k = 0;
  struct s_vector	*coord = NULL;

  if (!(d = malloc(r->nb_int * sizeof (double))))
    exit(1);
  if (!(coord = malloc(r->nb_int * sizeof (struct s_vector))))
    exit(1);
  coord_pgm(r, coord);
  for (i = 0; i < r->nb_pts; i++)
    {
      tab_normes(r, coord, d, i);
      for (min = d[0], j = 0; j < r->nb_int; j++)
	if (d[j] < min)
	  min = d[k = j];
      r->x[i].x = k % r->length_pgm;
      r->x[i].y = k / r->length_pgm;
      r->x[i].z = r->image[k];
    }
  free(d);
  free(coord);
}
