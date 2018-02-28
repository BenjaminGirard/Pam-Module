# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <security/pam_appl.h>
# include <security/pam_modules.h>

# include "tools.h"

int		isDirCreated(pam_handle_t *pamh)
{
  char		*dirname = get_dir_path(pamh);

  if (dirname == NULL)
    return -1;
  DIR		*dir = opendir(dirname);

  if (dir)
    closedir(dir);
  else if (ENOENT == errno)
    return (EXIT_SUCCESS);
  else
    return (-1);
  return EXIT_FAILURE;
}
