#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {

  DIR *dir;
  struct dirent *ent;

  dir = opendir("../");

  if (dir == NULL) {
    printf("ERROR: Unable to open directory.\n");
    return -1;
  }

  while ( (ent = readdir(dir)) != NULL ) {
    if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
      continue;
    }
    printf("%s\n", ent->d_name);
  }

  closedir(dir);

  return 0;
}
