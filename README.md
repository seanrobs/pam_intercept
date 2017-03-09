# pam_intercept

PAM module to intercept and log plaintext passwords from PAM enabled services.

The idea is to place this module after a module that accepts a password in
the pam chain and log the plaintext password, username and remote host 
(if available) to a logfile... Exactly how you configure this is dependent
on the service and the existant configuration. READ THE MAN PAGES!!!

