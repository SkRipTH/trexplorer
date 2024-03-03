#include "trexplorer.h"

static int printfile(state* s, int fileid) {
  mode_t filemode = (s->dirbuf)[fileid].statistics.st_mode;
  char *type;
  if (S_ISDIR(filemode)) {
    type = "dir";
  } else if (S_ISREG(filemode)) {
    type = "file";
  } else {
    type = "-";
  }
  char *name = (s->dirbuf)[fileid].direntity->d_name;

  return printw("[%5s] %.25s\n", type, name);
}

void render(state* s) {
  int row, col;
  getmaxyx(stdscr, row, col);
  box(stdscr, 0, 0);
  int curr = s->current_element;
  int element_height = 2;
  int elements_on_screen = (row - 2) / element_height;
  int center = elements_on_screen / 2;
  // center
  move((center + 1) * element_height, 2);

  printw(">");
  printfile(s, s->current_element);


  int max_added = (elements_on_screen - 1) / 2;

  // before
  for (int i = curr - 1; (i >= 0) && (curr - i <= max_added); i--) {
    int pos =
        (center + 1) * element_height - 1 - (curr - 1 - i) * element_height;
    move(pos, 3);
    hline('-', col - 4);
    move(pos - 1, 3);
    printfile(s, i);
  }
  // after

  for (int i = curr + 1; (i < s->element_count) && (i - curr <= max_added);
       i++) {
    int pos =
        (center + 1) * element_height + 1 + (i - curr - 1) * element_height;
    move(pos, 3);
    hline('-', col - 4);
    move(pos + 1, 3);
    printfile(s, i);
  }
}
