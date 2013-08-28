/*
** initialisation.c for src in /u/a1/monner_m/rendu/moular_t-recalage/src
**
** Made by melanie monnereau
** Login   <monner_m@epita.fr>
**
** Started on  Thu Dec  8 01:36:50 2005 melanie monnereau
** Last update Thu Dec 22 16:40:55 2005 thomas moulard
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "recalage.h"

/**
** This function looks if the file .txt can be opened
*/
static int	error_txt(struct s_recal *r, FILE **f)
{
  if (!(*f = fopen(r->name_txt, "r")))
    {
      write(STDERR_FILENO, "Impossible d'ouvrir le fichier ", 31);
      write(STDERR_FILENO, r->name_txt, strlen(r->name_txt));
      write(STDERR_FILENO, "\n", 1);
      return 0;
    }
  return 1;
}

/**
** This function fills an array with cloud's points
*/
void	init_nuage(struct s_recal *r)
{
  int	nb_pts = 0;
  char	*scoord;
  char	str[1024];
  FILE	*f = NULL;
  char	*last = NULL;
  int	i;

  if (!(error_txt(r, &f)))
    return;
  while (fgets(str, 1024, f))
    nb_pts++;
  if (!(r->nuage = malloc((nb_pts + 1) * sizeof (struct s_vector))))
    return;
  r->nb_pts = nb_pts;
  fseek(f, 0, SEEK_SET);
  for (i = 0; fgets(str, 1024, f); i++)
    {
      scoord = strtok_r(str, " ", &last);
      r->nuage[i].x = strtod(scoord, NULL);
      scoord = strtok_r(NULL, " ", &last);
      r->nuage[i].y = strtod(scoord, NULL);
      scoord = strtok_r(NULL, "\n", &last);
      r->nuage[i].z = strtod(scoord, NULL);
    }
}

/**
** This function looks if the file .pgm can be opened
*/
static int	error_pgm(struct s_recal *r, FILE **f)
{
  if (!(*f = fopen(r->name_pgm, "rb")))
    {
      write(STDERR_FILENO, "Impossible d'ouvrir le fichier ", 31);
      write(STDERR_FILENO, r->name_pgm, strlen(r->name_pgm));
      write(STDERR_FILENO, "\n", 1);
      return 0;
    }
  return 1;
}


static void		init_image_raw(struct s_recal	*r,
				       FILE		*f,
				       unsigned		w,
				       unsigned		h)
{
  unsigned		k = 0;

  for (k = 0; k < w * h; k++)
    {
      r->image[k] = 255;
      fread(r->image + k, 1, sizeof (unsigned char), f);
    }
}

static void		init_image_txt(struct s_recal	*r,
				       FILE		*f,
				       int		i,
				       int		j)
{
  int			k = 0;
  char			str[1024];
  char			*last = NULL;

  while (fgets(str, 1024, f))
    {
      r->image[k++] = atoi(strtok_r(str, " ", &last));
      for (j = 1; j < i - 1; k++, j++)
	r->image[k] = atoi(strtok_r(NULL, " ", &last));
      r->image[k++] = atoi(strtok_r(NULL, "\n", &last));
    }
}

/**
** This function is called in init_image
*/

int	call_image(struct s_recal *r, char *str, FILE *f, enum e_pgmtype type)
{
  int	i;
  int	j;
  char	*last = NULL;

  if (str[0] == '#')
    fgets(str, 1024, f);
  i = atoi(strtok_r(str, " ", &last));
  j = atoi(strtok_r(NULL, "\n", &last));
  r->nb_int = i * j;
  r->length_pgm = i;
  if (!(r->image = malloc(i * j * sizeof (int))))
    return 0;
  fgets(str, 1024, f);

  if (type == P_TXT)
    init_image_txt(r, f, i, j);
  else
    init_image_raw(r, f, i, j);
  return 1;
}

/**
** This function fills an array with the integers representing the file
** .pmg
*/
void			init_image(struct s_recal *r)
{
  char			str[1024];
  FILE			*f = NULL;
  enum e_pgmtype	type;

  if (!(error_pgm(r, &f)))
    return;
  fgets(str, 1024, f);
  if (!strncmp("P2", str, 2))
    type = P_TXT;
  else if (!strncmp("P5", str, 2))
    type = P_BIN;
  else
    {
      fprintf(stderr, "Invalid PGM file.\n");
      exit(1);
    }
  fgets(str, 1024, f);
  if (!(call_image(r, str, f, type)))
    return;
  fclose(f);
}
