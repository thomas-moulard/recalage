/*
** matrice_op2.c for Recalage in /goinfre/recalage/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Mon Dec 19 19:26:45 2005 thomas moulard
** Last update Fri Dec 23 01:50:08 2005 thomas moulard
*/
#include "recalage.h"

/**
** d = m / s
** s: scalar
*/
void			divmat(struct s_matrice	*d,
			       double		s,
			       struct s_matrice	*m)
{
  unsigned		i = 0;
  unsigned		j = 0;

  init_matrice(d, m->w, m->h);
  for (i = 0; i < m->w; i++)
    for (j = 0; j < m->h; j++)
      d->data[i + j * m->w] = m->data[i + j * m->w] / s;
}
