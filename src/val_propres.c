/*
** val_propres.c for src in /u/a1/monner_m/rendu/moular_t-recalage/src
**
** Made by melanie monnereau
** Login   <monner_m@epita.fr>
**
** Started on  Sat Dec 10 16:41:21 2005 melanie monnereau
** Last update Fri Dec 23 02:22:15 2005 thomas moulard
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "recalage.h"


/**
** Computes the norme of a matrix
*/
double		norme(struct s_matrice *v, int dim)
{
  double	s = 0.0;
  int		i = 0;

  for (i = 0; i < dim; i++)
    s += v->data[i] * v->data[i];
  return sqrt(s);
}


/**
** Randomize a vector
*/
static void	rnd_vec(struct s_matrice *up, int dim)
{
  int		i = 0;

  init_matrice(up, 1, dim);
  for (i = 0; i < dim; i++)
    up->data[i] = random();
}

/**
** Copy matrix data.
*/
static void	cp_mat(struct s_matrice *v, int dim, struct s_matrice *up)
{
  int		i = 0;

  for (i = 0; i < dim; i++)
    v->data[i] = up->data[i];
}

/*
** Computes the eigenvector
*/
static void		calcul_vec1(struct s_matrice	*a,
				    struct s_matrice	*u,
				    struct s_matrice	*up,
				    double     		*t)
{
  int			i = 0;
  int			j = 0;
  int			dim = 4;

  for (i = 0; i < dim; i++)
    {
      *t = 0.0;
      for (j = 0; j < dim; j++)
	*t = *t + a->data[i + j * a->w] * u->data[j];
      up->data[i] = *t;
    }
}

void			calcul_vec(struct s_matrice	*a,
				   int			dim,
				   struct s_matrice	*v)
{
  int			i;
  int			k = 1;
  struct s_matrice	u;
  struct s_matrice	up;
  double		n;
  double	       	t;

  rnd_vec(&up, dim);
  do
    {
      copy_mat(&u, &up);
      calcul_vec1(a, &u, &up, &t);
      n = norme(&up, dim);
      if (up.data[0] < 0)
	n = -n;
      t = 0.0;
      for (i = 0; i < dim; i++)
	{
	  up.data[i] /= n;
	  t += fabsf(up.data[i] - u.data[i]);
	}
      k++;
    }
  while (k < 1000 && t > 0.0000000001);
  cp_mat(v, dim, &up);
}

/**
** Computes the eigenvalue.
*/
double		valeur_propre(struct s_matrice	*a,
			      int		dim,
			      struct s_matrice	*v)
{
  int		i;
  int		j;
  double	n = 0.0;
  double	d = 0.0;

  for (i = 0; i < dim; i++)
    {
      d = d + v->data[i] * v->data[i];
      for (j = 0; j < dim; j++)
	n = n + v->data[i] * a->data[i + j * a->w] * v->data[j];
    }
  return n / d;
}

/**
** Delete a eigenvector from the matrix.
*/
void			deflation(struct s_matrice	*a,
				  double		val,
				  int			dim,
				  struct s_matrice	*v)
{
  int			i = 0;
  int			j = 0;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      a->data[i + j * a->w] = (a->data[i + j * a->w] -
			       val * v->data[i] * v->data[j]);
}
