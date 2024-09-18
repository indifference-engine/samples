#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

float *read_file(const char *const name, const size_t quantity)
{
  union
  {
    uint8_t u8[4];
    uint32_t u32;
    float f32;
  } *const output = malloc(sizeof(float) * quantity);

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

  for (size_t index = 0; index < quantity; index++)
  {
    output[index].u32 = output[index].u8[0] | (output[index].u8[1] << 8) | (output[index].u8[2] << 16) | (output[index].u8[3] << 24);
  }

  return (float *)output;
}

void write_file(const float *const buffer, const char *const name, const size_t quantity)
{
  union
  {
    uint8_t u8[4];
  } *const temp = malloc(sizeof(float) * quantity);

  if (temp == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for a buffer copy.\n");
    exit(1);
  }

  for (size_t index = 0; index < quantity; index++)
  {
    union
    {
      uint32_t u32;
      float f32;
    } convert;

    convert.f32 = buffer[index];

    temp[index].u8[0] = convert.u32 & 255;
    temp[index].u8[1] = (convert.u32 >> 8) & 255;
    temp[index].u8[2] = (convert.u32 >> 16) & 255;
    temp[index].u8[3] = (convert.u32 >> 24) & 255;
  }

  FILE *file = fopen(name, "wb");

  if (file == NULL)
  {
    fprintf(stderr, "Failed to open file \"%s\".\n", name);
    exit(1);
  }

  if (fwrite(temp, sizeof(float), quantity, file) != quantity)
  {
    fprintf(stderr, "Failed to write file \"%s\".\n", name);
    exit(1);
  }

  if (fclose(file) != 0)
  {
    fprintf(stderr, "Failed to close file \"%s\".\n", name);
    exit(1);
  }

  free(temp);
}
