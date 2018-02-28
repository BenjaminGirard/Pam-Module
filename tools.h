#ifndef TOOLS_H_
# define TOOLS_H_

# include <security/pam_appl.h>
# include <security/pam_modules.h>

const char		*pam_get_user_string(pam_handle_t * const pamh);
const struct passwd	*pam_get_pwnam_r_passwd(pam_handle_t * const pamh);

int			isUserContainerCreated(pam_handle_t * const pamhm,
					       const char * const ContainerName);
char		*concat(const char * const str1,
			const char * const str2);

char		*generate_formated_redirect_keys(const char * const key);


char		*get_decrypted_path_file(void);
char		*get_container_path(pam_handle_t *pamh);
char		*get_keyfile_path(pam_handle_t *pamh);
char		*get_dir_path(pam_handle_t *pamh);

#endif /* TOOLS_H_ */
