/*
** matrice.c for Recalage in /goinfre/recalage/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Sat Dec 10 15:04:20 2005 thomas moulard
** Last update Fri Dec 23 01:52:48 2005 thomas moulard
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "recalage.h"

/**
** Initialize a matrix.
*/
void		init_matrice(struct s_matrice *m, unsigned w, unsigned h)
{
  m->w = w;
  m->h = h;
  m->data = calloc(w * h, sizeof (double));
}

/**
** Desallocate a matrix.
*/
void		free_matrice(struct s_matrice *m)
{
  if (m && m->data)
    free(m->data);
}

/**
** The identify matrix
**
** (1,0,0)
** (0,1,0)
** (0,0,1)
*/
void		identite3(struct s_matrice *m)
{
  init_matrice(m, 3, 3);
  m->data[0] = m->data[4] = m->data[8] = 1;
}

/**
** Copy a matrix
*/
void		copy_mat(struct s_matrice *m, struct s_matrice *m2)
{
  init_matrice(m, m2->w, m2->h);
  memcpy(m->data, m2->data, m->w * m->h * sizeof (double));
}


/**
** Print the matrix on the standard output.
*/
void			aff_matrice(struct s_matrice *m, char *str)
{
  unsigned		i = 0;
  unsigned		j = 0;

  fprintf(stderr, "-----\n%s\n", str);
  for (j = 0; j < m->h; j++)
    {
      fprintf(stderr, "|");
      for (i = 0; i < m->w; i++)
	fprintf(stderr, " %f ", m->data[i + j * m->w]);
      fprintf(stderr, "|\n");
    }
  fprintf(stderr, "-----\n");
}
