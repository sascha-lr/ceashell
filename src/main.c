#include <stdio.h>
#include <stdlib.h>

char *getString(const char *prompt);

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);

  char *command = getString("$ ");
  if (command == NULL) {
    return 1;
  }
  printf("%s: command not found\n", command);

  free(command);

  return 0;
}

char *getString(const char *prompt) {

  int c;
  unsigned short offset = 0;
  unsigned short bufsize = 4;
  char *buf = malloc(bufsize);
  if (buf == NULL) {
    return NULL;
  }

  printf("%s", prompt);

  while (((c = fgetc(stdin)) != '\r' && c != EOF && c != '\n')) {

    if (offset == bufsize - 1) {
      bufsize *= 2;
      char *tmp = realloc(buf, bufsize);
      if (tmp == NULL) {
        free(buf);
        return NULL;
      }
      buf = tmp;
    }
    buf[offset++] = c;
  }

  if (c == EOF && offset == 0) {
    free(buf);
    return NULL;
  }

  if (offset < bufsize - 1) {
    bufsize = offset + 1;
    char *tmp = realloc(buf, bufsize);
    if (tmp != NULL) {
      buf = tmp;
    }
  }
  buf[offset] = '\0';
  return buf;
}
