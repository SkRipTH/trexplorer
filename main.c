#include "trexplorer.h"

void onEnter(state* s) {
  filedesc* chosen = &((s->dirbuf)[s->current_element]);
  char* name = chosen->direntity->d_name;
  mode_t mode = chosen->statistics.st_mode;

  if (S_ISDIR(mode)) {
    if (chdir(name) != 0) {
      exit(1);
    }
    if (readcurrentdir(s) != 0) {
      exit(1);
    }
  } else if (S_ISREG(mode)) {
    pid_t id = fork();
    if (id == 0) {
      char* args[3] = {"nano", name, 0};
      execvp("nano", args);
      perror("nano");
    } else {
      int options = WUNTRACED;
      if (waitpid(id, NULL, options) == -1) {
        perror("waitpid");
        exit(1);
      }
    }
  }
}

void input(state* s) {
  s->last_button = getch();
  char* filename;
  switch (s->last_button) {
    case 'q':
    case 'Q':
      s->exit = TRUE;
      break;
    case KEY_UP:
      if (s->current_element > 0) {
        s->current_element--;
      }
      break;
    case KEY_DOWN:
      if (s->current_element < s->element_count - 1) {
        s->current_element++;
      }
      break;
    case '\n':
      onEnter(s);
      break;
  }
}

int main() {
  setlocale(LC_ALL, "");

  state s;
  s.exit = FALSE;
  s.element_count = 100;
  s.current_element = 55;

  initscr();
  keypad(stdscr, TRUE);
  noecho();

  if (readcurrentdir(&s) != 0) {
    exit(1);
  }
  while (!s.exit) {
    render(&s);
    refresh();
    input(&s);
    clear();
  }
}