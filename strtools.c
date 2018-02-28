# include <stdlib.h>
# include <string.h>

char		*concat(const char * const str1,
			const char * const str2)
{
  char		*res;

  if ((res = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1))) == NULL ||
      (res = strcpy(res, str1)) == NULL ||
      (res = strcat(res, str2)) == NULL)
    return NULL;
  res[strlen(str1) + strlen(str2)] = '\0';
  return res;
}

char		*generate_formated_redirect_keys(const char * const key)
{
  char		*res;

  if ((res = malloc(sizeof(char) * (strlen(key) * 2 + 3))) == NULL ||
      memset(res, 0, sizeof(char) * (strlen(key) * 2 + 3)) == NULL)
    return (NULL);

  if ((res = strcpy(res, key)) == NULL)
    return (NULL);
  res[strlen(key)] = '\n';
  if ((res = strcat(res, key)) == NULL)
    return (NULL);
  res[strlen(key) + strlen(key) + 1] = '\n';
  res[strlen(key) + strlen(key) + 2] = '\0';
  return (res);
}
