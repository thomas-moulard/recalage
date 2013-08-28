/*
** matrice_op.c for Recalage in /goinfre/recalage/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Wed Dec 14 21:14:08 2005 thomas moulard
** Last update Fri Dec 23 01:49:56 2005 thomas moulard
*/
#include <assert.h>
#include "recalage.h"

/**
** d = a + b
*/
void		add(struct s_matrice *d,
		    struct s_matrice *a,
		    struct s_matrice *b)
{
  unsigned 	i = 0;
  unsigned	j = 0;

  assert(a->w == b->w);
  assert(a->h == b->h);
  init_matrice(d, a->w, a->h);
  for (i = 0; i < a->w; i++)
    for (j = 0; j < a->h; j++)
      d->data[i + j * a->w] = a->data[i + j * a->w] + b->data[i + j * a->w];
}

/**
** d = a - b
*/
void		sub(struct s_matrice *d,
		    struct s_matrice *a,
		    struct s_matrice *b)
{
  unsigned	i = 0;
  unsigned	j = 0;

  assert(a->w == b->w);
  assert(a->h == b->h);
  init_matrice(d, a->w, a->h);
  for (i = 0; i < a->w; i++)
    for (j = 0; j < a->h; j++)
      d->data[i + j * a->w] = a->data[i + j * a->w] - b->data[i + j * a->w];
}

/**
** d = s * m
** s: scalar
*/
void			mult(struct s_matrice	*d,
			     double		s,
			     struct s_matrice	*m)
{
  unsigned		i = 0;
  unsigned		j = 0;

  init_matrice(d, m->w, m->h);
  for (i = 0; i < m->w; i++)
    for (j = 0; j < m->h; j++)
      d->data[i + j * m->w] = s * m->data[i + j * m->w];
}

/**
** Computes the trace
*/
double		trace(struct s_matrice *m)
{
  int		i = 0;
  int		n = 0;
  double	res = 0.0;

  if (m->w < m->h)
    n = m->w;
  else
    n = m->h;
  for (i = 0; i < n; i++)
    res += m->data[i + i * m->w];
  return res;
}


/**
** Computes the transpose
*/
void		transposee(struct s_matrice *src, struct s_matrice *dest)
{
  unsigned int	i;
  unsigned int	j;

  init_matrice(dest, src->h, src->w);
  for (i = 0; i < src->w; i++)
    for (j = 0; j < src->h; j++)
      dest->data[j * dest->w + i] = src->data[i * src->w + j];
}
