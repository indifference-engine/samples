#include "../../../src/sample_fully_looping.h"
#include "../../helpers/main.h"

int main(int argc, char **argv)
{
  (void)(argc);
  (void)(argv);

  float *const sound_effect_samples = read_file("inputs/sound_effect.raw", 100);
  float *const left_output_samples = read_file("inputs/output_samples/left.raw", 500);
  float *const right_output_samples = read_file("inputs/output_samples/right.raw", 500);

  sample_fully_looping(
      100, sound_effect_samples,
      -50.3f, 0.2f, 0.7f,
      321.7f, 0.8f, 0.6f,
      500, left_output_samples, right_output_samples);

  write_file(sound_effect_samples, "outputs/actual/sound_effect.raw", 100);
  write_file(left_output_samples, "outputs/actual/output_samples/left.raw", 500);
  write_file(right_output_samples, "outputs/actual/output_samples/right.raw", 500);

  return 0;
}
