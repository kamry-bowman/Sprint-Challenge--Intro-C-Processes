#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

/**
 * Main
 */
int handle_level(char *path, char **output, int rem_depth)
{

  // Open directory
  DIR *dir;
  dir = opendir(path);
  if (!dir)
  {
    perror("Failed to open directory");
    exit(1);
  }

  // Repeatedly read and print entries
  // lines keeps track of number of lines added to output, and gets returned
  int lines = 0;
  struct dirent *current = readdir(dir);
  while (current)
  {
    struct stat buf;

    char full_path[512];
    snprintf(full_path, 512, "%s/%s", path, current->d_name);
    stat(full_path, &buf);

    char *line;
    line = output[lines];

    if ((buf.st_mode & S_IFMT) == S_IFDIR)
    {
      snprintf(line, 512, "%10s   %s\n", "<DIR>", current->d_name);

      if (rem_depth != 0)
      {
        lines++;
        line = output[lines];

        snprintf(line, 512, "I would go deeper here\n");
      }
    }
    else
    {
      snprintf(line, 512, "%10ld   %s\n", buf.st_size, current->d_name);
    }
    lines++;
    current = readdir(dir);
  }

  closedir(dir);
  return lines;
}

int main(int argc, char **argv)
{
  // Parse command line
  // check if more than two arguments, if so error
  if (argc > 2)
  {
    perror("The signature for the command is lsls [-path]");
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

  char *output[100];
  for (int i = 0; i < 100; i++)
  {
    output[i] = malloc(512);
  }

  int levels = handle_level(target, output, 1);
  for (int i = 0; i < levels; i++)
  {
    printf("%s", output[i]);
  }
  printf("\n");

  for (int i = 0; i < 100; i++)
  {
    free(output[i]);
  }

  return 0;
}