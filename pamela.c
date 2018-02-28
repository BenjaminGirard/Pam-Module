# include <security/pam_appl.h>
# include <security/pam_modules.h>
# include <stdio.h>
# include <stdlib.h>
# include <shadow.h>

# include "logger.h"
# include "pamela.h"
# include "tools.h"
# include "file_handler.h"
# include "container_handler.h"

int		pam_sm_open_session(pam_handle_t *pamh, int flags, int ac,
				    const char **av)
{
  int		isUCC = isUserContainerCreated(pamh, CONTAINER_PATH);

  UNUSED(flags);
  UNUSED(ac);
  UNUSED(av);
  log_action("Starting Pam secure luks module...");
  if (isUCC == -1)
    return PAM_BUF_ERR;
  if (isUCC == EXIT_FAILURE && init_user_container(pamh) == EXIT_FAILURE)
    return (PAM_BUF_ERR);
  if (open_user_container(pamh, isUCC) == EXIT_FAILURE)
    return (PAM_BUF_ERR);
  return (PAM_SUCCESS);
}

int		pam_sm_close_session(pam_handle_t *pamh, int flags, int ac,
				     const char **av)
{
  UNUSED(flags);
  UNUSED(ac);
  UNUSED(av);
  log_action("Starting closing proceed...");
  if (close_user_container(pamh) == EXIT_FAILURE)
    return (PAM_BUF_ERR);
  return (PAM_SUCCESS);
}
