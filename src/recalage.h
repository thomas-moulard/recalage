/*
** recalage.h for src in /u/a1/monner_m/rendu/moular_t-recalage/src
**
** Made by melanie monnereau
** Login   <monner_m@epita.fr>
**
** Started on  Thu Dec  8 01:41:27 2005 melanie monnereau
** Last update Fri Dec 23 02:20:09 2005 thomas moulard
*/
#ifndef RECALAGE_H_
# define RECALAGE_H_

enum			e_pgmtype
  {
    P_TXT,
    P_BIN
  };

struct			s_vector
{
  double		x;
  double		y;
  double		z;
};

struct			s_recal
{
  char			*name_pgm;
  char			*name_txt;
  int			*image;
  struct s_vector	*nuage;
  struct s_vector	*x;
  int			nb_pts;
  int			nb_int;
  int			length_pgm;
  int			n;
};

struct			s_quaternion
{
  double		s;
  struct s_vector	vec;
};

struct			s_matrice
{
  unsigned int		w;
  unsigned int		h;
  double		*data;
};

void		init_nuage(struct s_recal *r);
void		init_image(struct s_recal *r);
struct s_vector	*masse_txt(struct s_recal *r);
struct s_vector	*masse_x(struct s_vector *x, struct s_recal *r);

void		coord_pgm(struct s_recal *r, struct s_vector *coord);
void		tab_normes(struct s_recal	*r,
			   struct s_vector	*coord,
			   double		*d,
			   int			i);
void		vector_min(struct s_recal *r);

void		transfo(struct s_recal *r, double *err);
void		init_matrice(struct s_matrice *m, unsigned w, unsigned h);
void		free_matrice(struct s_matrice *m);
void		transposee(struct s_matrice *src, struct s_matrice *dest);
void		identite3(struct s_matrice *m);
void		add(struct s_matrice *d,
		    struct s_matrice *a,
		    struct s_matrice *b);
void		sub(struct s_matrice *d,
		    struct s_matrice *a,
		    struct s_matrice *b);
double		trace(struct s_matrice *m);
void		mult(struct s_matrice *d, double s, struct s_matrice *m);
void		divmat(struct s_matrice	*d, double s, struct s_matrice *m);
void		copy_mat(struct s_matrice *m, struct s_matrice *m2);
void		matrice2quaternion(struct s_quaternion *, struct s_matrice *);
void		addvector(struct s_vector *d,
			  struct s_vector *a,
			  struct s_vector *b);
void		subvector(struct s_vector *d,
			  struct s_vector *a,
			  struct s_vector *b);
void		multvectors(struct s_matrice	*d,
			    struct s_vector	*a,
			    struct s_vector	*b);
double		vnorme(struct s_vector *v);
void		aff_vector(struct s_vector *vec, char *str);
void		vector2quaternion(struct s_quaternion *q, struct s_vector *v);
void		init_quaternion(struct s_quaternion	*q);
void		mult_quaternion(struct s_quaternion	*q,
				struct s_quaternion	*q2,
				struct s_quaternion	*q3);
void		opp_quaternion(struct s_quaternion	*q,
			       struct s_quaternion	*q2);
void		aff_matrice(struct s_matrice *m, char *str);
void		aff_quaternion(struct s_quaternion *q, char *str);
double		norme(struct s_matrice *v, int dim);
void		calcul_vec(struct s_matrice     *a,
			   int                  dim,
			   struct s_matrice     *v);
double		valeur_propre(struct s_matrice  *a,
                              int               dim,
                              struct s_matrice  *v);
void		deflation(struct s_matrice      *a,
			  double                val,
			  int                   dim,
			  struct s_matrice      *v);

#endif /* !RECALAGE_H_ */
