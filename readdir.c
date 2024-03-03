#include "trexplorer.h"

int readcurrentdir(state* s) {
  struct dirent* file;

  DIR* dir = opendir(".");
  if (dir == NULL) {
    perror("Cannot open dir '.'");
    return 1;
  }

  int i = 0;
  errno = 0;
  while ((file = readdir(dir)) != NULL && i < FILELIMIT) {
    if (stat(file->d_name, &((s->dirbuf)[i].statistics)) != 0) {
      perror("Cannot read file");
    } else {
      (s->dirbuf)[i].direntity = file;
      i++;
    }
  }
  if (errno != 0) {
    perror("Cannot read dir");
    return 1;
  }

  if (closedir(dir) != 0) {
    perror("Cannot close dir");
    return 1;
  }

  if (i == FILELIMIT) {
    printf("FILE LIMIT EXCEEDED");
  }

  s->element_count = i;
  s->current_element = 0;

  return 0;
}
