/*
** main.c for src in /u/a1/monner_m/rendu/moular_t-recalage/src
**
** Made by melanie monnereau
** Login   <monner_m@epita.fr>
**
** Started on  Thu Dec  8 01:15:55 2005 melanie monnereau
** Last update Fri Dec 23 02:16:33 2005 thomas moulard
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include "recalage.h"

void	init(struct s_recal *r, int argc, char **argv)
{
  if (!(strcmp(argv[1], "-n")) || !(strcmp(argv[2], "-n")))
    {
      printf("./recalage X.pgm P.txt [-n iterations count]\n");
      exit(1);
    }
  if ((argv[3] && !argv[4]) || (argv[3] && argv[4] && (argv[4][0] < '0' ||
						       argv[4][0] > '9')))
    {
      printf("./recalage X.pgm P.txt [-n iterations count]\n");
      exit(1);
    }
  if (argc == 5)
    r->n = atoi(argv[4]);
  else
    r->n = INT_MAX;
  r->nb_int = r->nb_pts = r->length_pgm = 0;
  r->name_pgm = argv[1];
  r->name_txt = argv[2];
  r->image = NULL;
  r->nuage = NULL;
  init_nuage(r);
  init_image(r);
  if (!(r->x = malloc((r->nb_pts) * sizeof (struct s_vector))))
    return;
}

int			main(int argc, char **argv)
{
  struct s_recal	r;
  int			i = 0;
  int			k = 0;
  double		err = 0.1;

  if (argc < 3)
    write(STDERR_FILENO, "Pas assez d'arguments\n", 22);
  else
    {
      init(&r, argc, argv);
      for (k = 0; (k < r.n) && (err > 0.000001); k++)
	transfo(&r, &err);
      for (i = 0; i < r.nb_pts; i++)
	printf("%f %f %f\n", r.nuage[i].x, r.nuage[i].y, r.nuage[i].z);
    }
  free(r.image);
  free(r.nuage);
  free(r.x);
  return 0;
}
