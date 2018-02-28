# ifndef CMD_HANDLER_H_
# define CMD_HANDLER_H_

# include <security/pam_appl.h>
# include <security/pam_modules.h>

int			exec_fallocate(pam_handle_t *pamh);
int			exec_cryptsetup_luksFormat(pam_handle_t *pamh);
int		       exec_mkdir(pam_handle_t *pamh);

int			give_user_rights(pam_handle_t *pamh);

int			exec_cryptsetup_luksOpen(pam_handle_t *pamh);
int			exec_mkfs(void);
int			exec_mount(pam_handle_t *pamh);

int			exec_umount(pam_handle_t *pamh);
int			exec_cryptsetup_luksClose(void);

# endif
