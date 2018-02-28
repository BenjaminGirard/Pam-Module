# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <pwd.h>
# include <stdio.h>
# include <shadow.h>

# include "file_handler.h"
# include "pamela.h"
# include "tools.h"
# include "logger.h"
# include "cmd_handler.h"

int			generate_key(pam_handle_t *pamh)
{
  char		*path;
  const char  	*user;
  FILE		*file;
  struct spwd	*pw;

  if ((user = pam_get_user_string(pamh)) == NULL ||
      (pw = getspnam(user)) == NULL)
    return (EXIT_FAILURE);
  if ((path = concat(pam_get_pwnam_r_passwd(pamh)->pw_dir, DIR_NAME)) == NULL ||
      (path = concat(path, KEYFILE_PATH)) == NULL)
    return (EXIT_FAILURE);
  if ((file = fopen(path, "a+")) == NULL)
    return (EXIT_FAILURE);
  fputs(pw->sp_pwdp, file);
  fclose(file);
  return (EXIT_SUCCESS);
}

int		init_user_container(pam_handle_t *pamh)
{
  if (exec_fallocate(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (exec_mkdir(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (generate_key(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (exec_cryptsetup_luksFormat(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		open_user_container(pam_handle_t *pamh, int isFirstCall)
{
  if (exec_cryptsetup_luksOpen(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (isFirstCall == EXIT_FAILURE && exec_mkfs() == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (exec_mount(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (give_user_rights(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		close_user_container(pam_handle_t *pamh)
{
  if (exec_umount(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (give_user_rights(pamh) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (exec_cryptsetup_luksClose() == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
