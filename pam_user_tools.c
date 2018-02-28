#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

#include "logger.h"
# include "tools.h"

const char	*pam_get_user_string(pam_handle_t * const pamh)
{
  const char	*user;
  int		pgu_ret = pam_get_user(pamh, &user, NULL);

  if (pgu_ret != PAM_SUCCESS || user == NULL)
    return (log_errors("Error in pam_get_user()"));
  return (user);
}

const struct passwd *pam_get_pwnam_r_passwd(pam_handle_t * const pamh)
{
  const char	*user = pam_get_user_string(pamh);
  struct passwd	*pw = NULL;
  struct passwd	pw_s;
  char		buffer[1024];
  int		gpn_ret;

  if (user == NULL)
    return (NULL);
  gpn_ret = getpwnam_r(user, &pw_s, buffer, sizeof(buffer), &pw);
  if (gpn_ret != 0 || pw == NULL || pw->pw_dir == NULL || pw->pw_dir[0] != '/')
    return (log_errors("Error in getpwnam_r()"));
  return pw;
}

int			isUserContainerCreated(pam_handle_t * const pamh,
					       const char * const container_name)
{
  const struct passwd	*pw = pam_get_pwnam_r_passwd(pamh);
  int			fd;
  int			ret = EXIT_SUCCESS;
  char			*path;


  if (pw == NULL || (path = concat(pw->pw_dir, container_name)) == NULL)
    return -1;
  if ((fd = open(path, O_RDONLY)) < 0)
    ret = EXIT_FAILURE;
  else
    close(fd);
  free(path);
  return (ret);
}
