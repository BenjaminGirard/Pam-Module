#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void		*log_errors(const char *err)
{
  fprintf(stderr, "%s : %s\n", err, strerror(errno));
  return (NULL);
}

int		log_errors_i(const char *err)
{
  fprintf(stderr, "%s : %s\n", err, strerror(errno));
  return (EXIT_FAILURE);
}

void		log_action(const char * const msg)
{
  printf("[+] %s\n", msg);
}
