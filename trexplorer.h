
#include <dirent.h>
#include <errno.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct filedesc {
  struct stat statistics;
  struct dirent* direntity;
} filedesc;

#define FILELIMIT 255

typedef struct state {
  int last_button;
  bool exit;
  int element_count;
  int current_element;
  filedesc dirbuf[FILELIMIT];
} state;

void render(state* s);
int readcurrentdir(state* s);
