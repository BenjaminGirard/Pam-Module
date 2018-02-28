# ifndef CONTAINER_HANDLER_H_
# define CONTAINER_HANDLER_H_

# include <security/pam_appl.h>
# include <security/pam_modules.h>

int		init_user_container(pam_handle_t *pamh);
int		open_user_container(pam_handle_t *pamh, int isFirstCall);
int		close_user_container(pam_handle_t *pamh);

# endif
