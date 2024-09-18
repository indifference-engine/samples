#include "sample_partially_looping.h"

void sample_partially_looping(
    const int sound_effect_length,
    const int sound_effect_loop_from,
    const float *const sound_effect_samples,
    const float from_sound_effect_sample,
    const float from_left_gain,
    const float from_right_gain,
    const float to_sound_effect_sample,
    const float to_left_gain,
    const float to_right_gain,
    const int output_length,
    float *const left_output_samples,
    float *const right_output_samples)
{
  const float output_length_float = output_length;

  const float from[3] = {
      from_sound_effect_sample,
      from_left_gain,
      from_right_gain};

  const float to[3] = {
      to_sound_effect_sample,
      to_left_gain,
      to_right_gain};

  const int sound_effect_loop_length = sound_effect_length - sound_effect_loop_from;

  for (int output_index = 0; output_index < output_length; output_index++)
  {
    const float from_coefficient = (output_length - output_index) / output_length_float;
    const float to_coefficient = output_index / output_length_float;

    const float interpolations[3] = {
        from[0] * from_coefficient + to[0] * to_coefficient,
        from[1] * from_coefficient + to[1] * to_coefficient,
        from[2] * from_coefficient + to[2] * to_coefficient,
    };

    if (interpolations[0] >= 0)
    {
      int sound_effect_index = interpolations[0];

      if (sound_effect_index >= sound_effect_loop_from)
      {
        sound_effect_index -= sound_effect_loop_from;
        sound_effect_index %= sound_effect_loop_length;
        sound_effect_index += sound_effect_loop_from;
      }

      const float sound_effect_sample = sound_effect_samples[sound_effect_index];

      left_output_samples[output_index] += interpolations[1] * sound_effect_sample;
      right_output_samples[output_index] += interpolations[2] * sound_effect_sample;
    }
  }
}
