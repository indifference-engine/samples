#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

float *read_file(const char *const name, const size_t quantity)
{
  float *const output = malloc(sizeof(float) * quantity);

  if (output == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for a buffer copy.\n");
    exit(1);
  }

  FILE *file = fopen(name, "rb");

  if (file == NULL)
  {
    fprintf(stderr, "Failed to open file \"%s\".\n", name);
    exit(1);
  }

  if (fread(output, sizeof(float), quantity, file) != quantity)
  {
    fprintf(stderr, "Failed to read file \"%s\".\n", name);
    exit(1);
  }

  if (fclose(file) != 0)
  {
    fprintf(stderr, "Failed to close file \"%s\".\n", name);
    exit(1);
  }

  return output;
}

void write_file(const float *const buffer, const char *const name, const size_t quantity)
{
  FILE *file = fopen(name, "wb");

  if (file == NULL)
  {
    fprintf(stderr, "Failed to open file \"%s\".\n", name);
    exit(1);
  }

  for (size_t index = 0; index < quantity; index++)
  {
    const float rounded = (int)(buffer[index] * 1000000.0f) / 1000000.0f;

    if (fwrite(&rounded, sizeof(float), 1, file) != 1)
    {
      fprintf(stderr, "Failed to write file \"%s\".\n", name);
      exit(1);
    }
  }

  if (fclose(file) != 0)
  {
    fprintf(stderr, "Failed to close file \"%s\".\n", name);
    exit(1);
  }
}
