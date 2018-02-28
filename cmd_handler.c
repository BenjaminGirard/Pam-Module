# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <pwd.h>
# include <shadow.h>
# include <stdio.h>
# include <string.h>

# include "pamela.h"
# include "tools.h"
# include "logger.h"

static char		*generate_cryptsetup_luksformat_cmd(pam_handle_t *pamh,
							    char *cmd)
{
  char			*res;
  char			*container_path = get_container_path(pamh);
  char			*keyfile_path = get_keyfile_path(pamh);

  if (container_path == NULL || keyfile_path == NULL ||
      (res =
       malloc(sizeof(char) *
	      (strlen(cmd) + 1 + strlen(container_path) + 1 + strlen(keyfile_path) + 1))) == NULL)
    return (NULL);
  memset(res, 0, (strlen(cmd) + strlen(container_path) + 1 + strlen(keyfile_path) + 1));
  sprintf(res, "%s %s %s", cmd, container_path, keyfile_path);
  return res;
}

int			exec_cryptsetup_luksFormat(pam_handle_t *pamh)
{
  char	        *cmd;

  if ((cmd =
       generate_cryptsetup_luksformat_cmd(pamh, "cryptsetup -q luksFormat")) == NULL)
    return (EXIT_FAILURE);
  log_action("Configuring cryptsetup, formatting container...");
  system(cmd);
  /* free(cmd); */
  /* free(formated_keys); */
  /* free((char *)user); */
  return (EXIT_SUCCESS);
}

int			exec_cryptsetup_luksOpen(pam_handle_t *pamh)
{
  char			*res;
  char			*container_path = get_container_path(pamh);
  char			*keyfile_path = get_keyfile_path(pamh);
  if (container_path == NULL || keyfile_path == NULL)
    return EXIT_FAILURE;
  int			size_res = (strlen("cryptsetup luksOpen ") +
				    strlen(container_path) + 1 +
				    strlen(DECRYPTED_NAME) + 1 +
				    strlen("--key-file ") + 1 +
				    strlen(keyfile_path) + 1);
  if ((res = malloc(sizeof(char) * size_res)) == NULL)
    return (EXIT_FAILURE);
  memset(res, 0, size_res);
  sprintf(res, "cryptsetup luksOpen %s %s --key-file %s",
	  container_path, DECRYPTED_NAME, keyfile_path);
  log_action("Opening container...");
  system(res);
  return (EXIT_SUCCESS);
}

int			exec_fallocate(pam_handle_t *pamh)
{
  char		*path;
  char		*cmd;

  if ((path = get_container_path(pamh)) == NULL ||
      (cmd = concat("dd if=/dev/zero bs=1 count=0 seek=1G of=", path)) == NULL)
     return EXIT_FAILURE;
  log_action("Allocating memory to init conatainer...");
  system(cmd);
  /* free(path); */
  /* free(cmd); */
  return (EXIT_SUCCESS);
}

int			give_user_rights(pam_handle_t *pamh)
{
  char			*usr = (char *)pam_get_user_string(pamh);
  char			*path = get_dir_path(pamh);
  char			*cmd;

  if (usr == NULL || path == NULL)
    return EXIT_FAILURE;
  if ((cmd =
       malloc(sizeof(char) * (strlen("chown ") + strlen(usr) + 2 + strlen(path) + 1))) == NULL)
    return (EXIT_FAILURE);
  memset(cmd, 0, (strlen("chown ") + strlen(usr) + 2 + strlen(path) + 1));
  sprintf(cmd, "chown %s: %s", usr, path);
  system(cmd);
  log_action("Giving user rights on directory...");
  system(concat("chmod 700 ", path));
  return (EXIT_SUCCESS);
}

int		       exec_mkdir(pam_handle_t *pamh)
{
  char		*path;

  if ((path = get_dir_path(pamh)) == NULL)
    return EXIT_FAILURE;
  log_action("creating directory...");
  mkdir(path, S_IRUSR | S_IWUSR);
  return (EXIT_SUCCESS);
}

int			exec_mkfs(void)
{
  char			*decrypted_path = get_decrypted_path_file();
  char			*cmd;

  if (decrypted_path == NULL ||
      (cmd = concat("mkfs.ext4 ", decrypted_path)) == NULL)
    return (EXIT_FAILURE);
  log_action("Setting container to ext format...");
  system(cmd);
  return (EXIT_SUCCESS);
}

int			exec_mount(pam_handle_t *pamh)
{
  char			*decrypted_path = get_decrypted_path_file();
  char			*dir_path = get_dir_path(pamh);
  char			*cmd;
  if (decrypted_path == NULL || dir_path == NULL)
    return EXIT_FAILURE;
  int			size_cmd = strlen("mount ") +
    strlen(decrypted_path) + 1 + strlen(dir_path) + 1;

  if ((cmd = malloc(sizeof(char) * size_cmd)) == NULL)
    return (EXIT_FAILURE);
  memset(cmd, 0, size_cmd);
  sprintf(cmd, "mount %s %s", decrypted_path, dir_path);
  log_action("Mounting container on security directory...");
  system(cmd);
  return (EXIT_SUCCESS);

}

int			exec_umount(pam_handle_t *pamh)
{
  char			*dir_path = get_dir_path(pamh);
  char			*cmd;
  int			size_cmd;

  if (dir_path == NULL)
    return (EXIT_FAILURE);
  size_cmd = strlen("umount ") + strlen(dir_path) + 1;
  if ((cmd = malloc(sizeof(char) * size_cmd)) == NULL)
    return (EXIT_FAILURE);
  sprintf(cmd, "umount %s", dir_path);
  log_action("Umounting container directory...");
  system(cmd);
  return (EXIT_SUCCESS);
}

int			exec_cryptsetup_luksClose()
{
  char			*dir_path = get_decrypted_path_file();
  char			*cmd;
  int			size_cmd;

  if (dir_path == NULL)
    return (EXIT_FAILURE);
  size_cmd = strlen("cryptsetup luksClose ") + strlen(dir_path) + 1;
  if ((cmd = malloc(sizeof(char) * size_cmd)) == NULL)
    return (EXIT_FAILURE);
  sprintf(cmd, "cryptsetup luksClose %s", dir_path);
  log_action("Locking container...");
  system(cmd);
  return (EXIT_SUCCESS);
}
