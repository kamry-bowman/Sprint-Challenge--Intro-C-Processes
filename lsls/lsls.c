#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

/**
 * Main
 */
void handle_level(char *path, int rem_depth, int current_depth)
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
  struct dirent *current = readdir(dir);
  while (current)
  {
    struct stat buf;

    char full_path[512];
    snprintf(full_path, 512, "%s/%s", path, current->d_name);
    stat(full_path, &buf);

    // pad left whitespace for current depth
    for (int i = 0; i < current_depth; i++)
    {
      printf("          ");
    }

    if ((buf.st_mode & S_IFMT) == S_IFDIR)
    {
      printf("%10s   %s\n", "<DIR>", current->d_name);

      // careful, this is base case and initialization for recursion
      if (rem_depth != 0)
      {
        // pad left whitespace for current depth
        for (int i = 0; i < current_depth; i++)
        {
          printf("          ");
        }
        printf("           ---->\n");

        // recur
        handle_level(full_path, rem_depth - 1, current_depth + 1);

        // pad left whitespace for current depth
        for (int i = 0; i < current_depth; i++)
        {
          printf("          ");
        }
        printf("           <----\n");
      }
    }
    else
    {
      printf("%10ld   %s\n", buf.st_size, current->d_name);
    }

    current = readdir(dir);
  }

  closedir(dir);
}

int main(int argc, char **argv)
{
  // Parse command line
  // check if more than three arguments, if so error
  if (argc > 3)
  {
    perror("The signature for the command is lsls [-path] [-depth]");
    exit(1);
  }
  // set hiearchy depth from third argument if it exists, else 1
  int depth;
  if (argc == 3)
  {
    depth = atoi(argv[2]);
  }
  else
  {
    depth = 1;
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

  handle_level(target, depth, 0);

  return 0;
}