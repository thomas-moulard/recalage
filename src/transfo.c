/*
** transfo.c for Recalage in /goinfre/recalage/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Sat Dec 10 15:05:09 2005 thomas moulard
** Last update Fri Dec 23 01:50:54 2005 thomas moulard
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "recalage.h"

/**
 ** This function calculates the matrix of Covarience
 */

static void		covariance(struct s_matrice	*c,
				   struct s_vector	*x,
				   struct s_recal	*r)
{
  struct s_vector	v1;
  struct s_vector	v2;
  struct s_matrice	c2;
  struct s_matrice	res;
  struct s_vector	*u_x;
  struct s_vector	*u_p;
  int			i = 0;
  unsigned		j = 0;

  u_x = masse_x(x, r);
  u_p = masse_txt(r);
  init_matrice(&res, 3, 3);
  c2.data = NULL;
  for (i = 0; i < r->nb_pts; i++)
    {
      subvector(&v1, r->nuage + i, u_p);
      subvector(&v2, x + i, u_x);
      multvectors(&c2, &v1, &v2);
      for (j = 0; j < 9; j++)
	res.data[j] += c2.data[j];
      free_matrice(&c2);
    }
  divmat(c, r->nb_pts, &res);
  free(u_p);
  free(u_x);
}

/**
** This function calculates the matrice A
*/

void			matrice_a(struct s_matrice *a, struct s_matrice *c)
{
  struct s_matrice	t_c;

  transposee(c, &t_c);
  sub(a, c, &t_c);
  free_matrice(&t_c);
}

/**
** This function initializes the matrice Q
*/

static void	init_matrice_q(struct s_matrice      *q,
			       struct s_matrice      *c,
			       struct s_matrice      *a)
{
  q->data[0] = trace(c);
  q->data[1] = a->data[(2 - 1) * a->w + (3 - 1)];
  q->data[2] = a->data[(3 - 1) * a->w + (1 - 1)];
  q->data[3] = a->data[(1 - 1) * a->w + (2 - 1)];
  q->data[1 * q->w] = a->data[(2 - 1) * a->w + (3 - 1)];
  q->data[2 * q->w] = a->data[(3 - 1) * a->w + (1 - 1)];
  q->data[3 * q->w] = a->data[(1 - 1) * a->w + (2 - 1)];
}

/**
** This function calculates the matrice Q
*/

void			matrice_q(struct s_matrice	*q,
				  struct s_matrice	*c,
				  struct s_matrice	*a)
{
  struct s_matrice	c2;
  struct s_matrice	c4;
  struct s_matrice	i3;
  struct s_matrice	res;
  struct s_matrice	t_c;
  unsigned		i;
  unsigned		j;

  init_matrice(q, 4, 4);
  init_matrice_q(q, c, a);
  identite3(&i3);
  transposee(c, &t_c);
  add(&c2, c, &t_c);
  mult(&c4, q->data[0], &i3);
  sub(&res, &c2, &c4);
  free_matrice(&t_c);
  free_matrice(&c2);
  free_matrice(&c4);
  free_matrice(&i3);
  for (i = 0; i < a->w; i++)
    for (j = 0; j < a->h; j++)
      q->data[i + 1 + (j + 1) * q->w] = res.data[i + j * a->w];
  free_matrice(&res);
}

/**
** This function computes the quaternion of translation
*/

void			calcul_qt(struct s_quaternion	*q_t,
				  struct s_quaternion	*q_r,
				  struct s_vector	*x,
				  struct s_recal	*r)
{
  struct s_vector	*u_p = NULL;
  struct s_quaternion	q_up;
  struct s_quaternion	tmp;
  struct s_quaternion	opp_qr;
  struct s_quaternion	r_up;
  struct s_vector	*u_x = NULL;

  u_x = masse_x(x, r);
  u_p = masse_txt(r);
  q_up.s = 0.0;
  q_up.vec = *u_p;
  opp_quaternion(&opp_qr, q_r);
  mult_quaternion(&tmp, q_r, &q_up);
  mult_quaternion(&r_up, &tmp, &opp_qr);
  q_t->s = 0.0 - r_up.s;
  q_t->vec.x = u_x->x - r_up.vec.x;
  q_t->vec.y = u_x->y - r_up.vec.y;
  q_t->vec.z = u_x->z - r_up.vec.z;
  free(u_x);
  free(u_p);
}

/**
 ** This function calculates the quaternion of rotation
 */

void			calcul_qr(struct s_quaternion	*q_r,
				  struct s_vector	*x,
				  struct s_recal	*r)
{
  struct s_matrice	vp;
  struct s_matrice	c;
  struct s_matrice	q;
  struct s_matrice	a;

  covariance(&c, x, r);
  matrice_a(&a, &c);
  matrice_q(&q, &c, &a);
  init_matrice(&vp, 1, 4);
  calcul_vec(&q, 4, &vp);
  matrice2quaternion(q_r, &vp);
  free_matrice(&vp);
  free_matrice(&c);
  free_matrice(&q);
  free_matrice(&a);
}

static void		call_transfo(struct s_quaternion	*res_t,
				     struct s_quaternion	*res_r,
				     struct s_quaternion        *q_t)

{
  res_t->s = res_r->s + q_t->s;
  res_t->vec.x = res_r->vec.x + q_t->vec.x;
  res_t->vec.y = res_r->vec.y + q_t->vec.y;
  res_t->vec.z = res_r->vec.z + q_t->vec.z;
}

static void		call_transfo2(struct s_recal	*r,
				      struct s_vector	*x,
				      int		*i,
				      double		*err)
{
  struct s_vector       v_err;

  subvector(&v_err, x + *i, r->nuage + *i);
  *err = v_err.x * v_err.x + v_err.y * v_err.y + v_err.z * v_err.z;
}

static void		init_transfo(struct s_vector		**x,
				     double			*err,
				     struct s_quaternion	*pt,
				     struct s_recal		*r)
{
  vector_min(r);
  *x = r->x;
  *err = 0.0;
  pt->s = 0.0;
}

/**
** This function calculates the new points'cloud
*/
void			transfo(struct s_recal *r, double *err)
{
  struct s_quaternion	q_t;
  struct s_quaternion	q_r;
  struct s_quaternion	opp_qr;
  struct s_quaternion	pt;
  struct s_quaternion	tmp;
  struct s_quaternion	res_t;
  struct s_quaternion	res_r;
  int			i = 0;
  struct s_vector	*x = NULL;

  init_transfo(&x, err, &pt, r);
  calcul_qr(&q_r, x, r);
  opp_quaternion(&opp_qr, &q_r);
  calcul_qt(&q_t, &q_r, x, r);
  for (i = 0; i < r->nb_pts; i++)
    {
      pt.vec = r->nuage[i];
      mult_quaternion(&tmp, &q_r, &pt);
      mult_quaternion(&res_r, &tmp, &opp_qr);
      call_transfo(&res_t, &res_r, &q_t);
      r->nuage[i] = res_t.vec;
      call_transfo2(r, x, &i, err);
    }
  *err /= r->nb_pts;
}
