/*
** moulinette.c for Recalage in /u/a1/moular_t/rendu/recalage/tests
** 
** Made by thomas moulard
** Login   <moular_t@epita.fr>
** 
** Started on  Tue Dec 20 03:06:21 2005 thomas moulard
** Last update Tue Dec 20 03:27:59 2005 thomas moulard
*/
#include <stdio.h>

int		main(int argc, char **argv)
{
  FILE		*f = NULL, *fref = NULL;
  double	x, y, z, refx, refy, refz, err;
  if (argc != 3)
    {
      printf("Mauvaise nombre d'arguments\n");
      exit(1);
    }

  f = fopen(argv[1], "r");
  fref = fopen(argv[2], "r");
  if (!f || !fref)
    {
      printf("Fichier introuvable.\n");
      exit(1);
    }
  err = 0.0;
  while (!feof(f) || ! feof(fref))
    {
      x = y = z = refx = refy = refz = 0.0;
      fscanf(f, "%lf %lf %lf\n", &x, &y, &z);
      fscanf(fref, "%lf %lf %lf\n", &refx, &refy, &refz);
      printf("%lf %lf %lf\n", fabsf(x - refx), fabsf(y - refy),
	     fabsf(z - refz));
      err += fabsf(x - refx) + fabsf(y - refy) + fabsf(z - refz);
    }
  printf("----------\n");
  printf("-> ERREUR: %lf\n", err);
  return 0;
}
