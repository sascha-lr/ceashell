#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getString(const char *prompt);

int getSpaceIndex(const char *commmand);

int main(void) {
  setbuf(stdout, NULL);

  for (char *command; 1; free(command)) {
    if ((command = getString("$ ")) == NULL) {
      return 1;
    }

    int spaceIndex = getSpaceIndex(command);

    if (spaceIndex > -1 && (strncmp(command, "echo", spaceIndex)) == 0) {
      printf("%s\n", command + (spaceIndex + 1));
    } else if (strcmp(command, "exit") == 0) {
      free(command);
      break;
    } else {
      printf("%s: command not found\n", command);
    }
  }

  return 0;
}

int getSpaceIndex(const char *command) {
  int spaceIndex = -1;

  for (int i = 0; command[i] != '\0'; i++) {
    if (command[i] == ' ' && i != 0) {
      spaceIndex = i;
      break;
    }
  }
  return spaceIndex;
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
