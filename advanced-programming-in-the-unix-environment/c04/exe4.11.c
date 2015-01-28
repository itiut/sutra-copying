/* Exercise 4.11 */
#include "apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(const char *filename, Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        err_quit("usage: ftw <starting-pathname>");
    }

    int ret = myftw(argv[1], myfunc);

    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0) {
        ntot = 1;
    }
    printf("regular files  = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
    printf("directories    = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
    printf("block special  = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
    printf("char special   = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
    printf("FIFOs          = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
    printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);
    return ret;
}

#define FTW_F   1               /* file other than directory*/
#define FTW_D   2               /* directory */
#define FTW_DNR 3               /* directory that cannot be read */
#define FTW_NS  4               /* file that we cannot stat */

static int myftw(char *pathname, Myfunc *func) {
    return dopath(pathname, func);
}

static int dopath(const char *filename, Myfunc *func) {
    struct stat statbuf;
    if (lstat(filename, &statbuf) == -1) {
        return func(filename, &statbuf, FTW_NS);
    }
    if (S_ISDIR(statbuf.st_mode) == 0) {
        return func(filename, &statbuf, FTW_F);
    }

    int ret;
    if ((ret = func(filename, &statbuf, FTW_D)) != 0) {
        return ret;
    }

    /* Directory */
    if (chdir(filename) == -1) {
        err_quit("chdir to %s failed", filename);
    }

    DIR *dp;
    if ((dp = opendir(".")) == NULL) {
        return func(".", &statbuf, FTW_DNR);
    }

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
            continue;
        }
        if ((ret = dopath(dirp->d_name, func)) != 0) {
            break;
        }
    }

    if (closedir(dp) == -1) {
        err_ret("cannot close directory %s", filename);
    }
    if (chdir("..") == -1) {
        err_quit("chdir to up failed: %s", filename);
    }
    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type) {
    switch (type) {
    case FTW_F:
        switch(statptr->st_mode & S_IFMT) {
        case S_IFREG:  nreg++;   break;
        case S_IFBLK:  nblk++;   break;
        case S_IFCHR:  nchr++;   break;
        case S_IFIFO:  nfifo++;  break;
        case S_IFLNK:  nslink++; break;
        case S_IFSOCK: nsock++;  break;
        case S_IFDIR:
            err_dump("for S_IFDIR for %s", pathname);
        }
        break;
    case FTW_D:
        ndir++;
        break;
    case FTW_DNR:
        err_ret("cannot read directory %s", pathname);
        break;
    case FTW_NS:
        err_ret("stat error for %s", pathname);
        break;
    default:
        err_dump("unknown type %d for pathname %s", type, pathname);
    }
    return 0;
}
