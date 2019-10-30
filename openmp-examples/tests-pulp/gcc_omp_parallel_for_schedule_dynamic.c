#include <omp.h>
#include <stdlib.h>
#include <string.h>

int gcc_omp_parallel_for_schedule_dynamic (void)
{
  int buf[64], *p;
  int i;
  memset (buf, '\0', sizeof (buf));
#pragma omp parallel for schedule (dynamic, 3)
  for (i = 10; i < 54; i++)
    buf[i] = 5;
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54)){
      printf("error 1 at gcc schedule dynamic\n");
      abort ();
    }
  printf("yeah\n");

#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[10]; p < &buf[54]; p++)
    printf("p=%p\n", p);
    *p = 5;
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54)){
      printf("error 1 at gcc schedule dynamic\n");
      abort ();
    }
  memset (buf, '\0', sizeof (buf));
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[3]; p <= &buf[63]; p += 2)
    p[-2] = 6;
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61)){
      printf("error 2 at gcc schedule dynamic\n");
      abort ();
    }
  memset (buf, '\0', sizeof (buf));
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[16]; p < &buf[51]; p = 4 + p)
    p[2] = 7;
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53)){
      printf("error 3 at gcc schedule dynamic\n");
      abort ();
    }
  memset (buf, '\0', sizeof (buf));
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[16]; p <= &buf[40]; p = p + 4ULL)
    p[2] = -7;
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42)){
      printf("error 4 at gcc schedule dynamic\n");
      abort ();
    }
  memset (buf, '\0', sizeof (buf));
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[53]; p > &buf[9]; --p)
    *p = 5;
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54)){
      printf("error 5 at gcc schedule dynamic\n");
      abort ();
    }
  memset (buf, '\0', sizeof (buf));
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[63]; p >= &buf[3]; p -= 2)
    p[-2] = 6;
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61)){
      printf("error 6 at gcc schedule dynamic\n");
      abort ();
    }
  memset (buf, '\0', sizeof (buf));
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[48]; p > &buf[15]; p = -4 + p)
    p[2] = 7;
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53)){
      printf("error 7 at gcc schedule dynamic\n");
      abort ();
    }
  memset (buf, '\0', sizeof (buf));
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[40]; p >= &buf[16]; p = p - 4ULL)
    p[2] = -7;
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42)){
      printf("error 8 at gcc schedule dynamic\n");
      abort ();
    }
  return 0;
}
