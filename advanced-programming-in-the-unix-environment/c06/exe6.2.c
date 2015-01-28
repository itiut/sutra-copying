/* Figure C.5, C.6 */
#include "apue.h"

#ifdef __linux
#include <shadow.h>
#else
/* OS X */
#include <pwd.h>
#endif

int main(int argc, char *argv[]) {
    if (argc != 2) {
        err_quit("usage: %s <logingname>", argv[0]);
    }

#ifdef __linux
    struct spwd *ptr;
    if ((ptr = getspnam(argv[1])) == NULL) {
        err_sys("getspnam error");
    }
    printf("sp_pwdp = %s\n",
           (ptr->sp_pwdp == NULL || ptr->sp_pwdp[0] == 0) ? "(null)" : ptr->sp_pwdp);
#else
    /* OS X */
    struct passwd *ptr;
    if ((ptr = getpwnam(argv[1])) == NULL) {
        err_sys("getpwnam error");
    }
    printf("pw_passwd = %s\n",
           (ptr->pw_passwd == NULL || ptr->pw_passwd[0] == 0) ? "(null)" : ptr->pw_passwd);
#endif
    return 0;
}
