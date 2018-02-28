# include <security/pam_appl.h>
# include <security/pam_modules.h>
# include <stdlib.h>
# include <string.h>
# include <pwd.h>
# include <stdio.h>

# include "pamela.h"
# include "tools.h"

char		*get_decrypted_path_file(void)
{
  char		*path;

  path = malloc(sizeof(char) * (strlen("/dev/mapper/") + strlen(DECRYPTED_NAME) + 1));
  if (path == NULL)
    return (NULL);
  sprintf(path, "/dev/mapper/%s", DECRYPTED_NAME);
  return (path);
}

char		*get_container_path(pam_handle_t *pamh)
{
  char		*path;
  const struct passwd *pw = pam_get_pwnam_r_passwd(pamh);

  if (pw == NULL)
    return (NULL);
  if ((path = concat(pw->pw_dir, CONTAINER_PATH)) == NULL)
    return NULL;
  return path;
}

char		*get_keyfile_path(pam_handle_t *pamh)
{
  char		*path;

  if ((path = concat(pam_get_pwnam_r_passwd(pamh)->pw_dir, DIR_NAME)) == NULL ||
      (path = concat(path, KEYFILE_PATH)) == NULL)
    return (NULL);
  return path;
}

char		*get_dir_path(pam_handle_t *pamh)
{
  char		*path;

  if ((path = concat(pam_get_pwnam_r_passwd(pamh)->pw_dir, DIR_NAME)) == NULL)
    return NULL;
  return (path);
}
