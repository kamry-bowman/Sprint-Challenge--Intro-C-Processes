#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  // Parse command line
  // check if more than two arguments, if so error
  if (argc > 2)
  {
    perror("The signature for the command is lsls [,path]");
    exit(1);
  }
  char *target;
  // set target to second argument if it exists
  if (argc == 2)
  {
    target = argv[1];
  }
  // else check if its only one line, then set target to "."
  else
  {
    target = ".";
  }

  // Open directory
  DIR *dir;
  dir = opendir(target);
  if (!dir)
  {
    perror("Failed to open directory");
    exit(1);
  }

  // Repeatly read and print entries
  struct dirent *current = readdir(dir);
  while (current)
  {
    struct stat buf;

    char full_path[512];
    snprintf(full_path, 512, "%s/%s", target, current->d_name);
    stat(full_path, &buf);

    printf("%10ld   %s\n", buf.st_size, current->d_name);
    current = readdir(dir);
  }

  closedir(dir);

  return 0;
}