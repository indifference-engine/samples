#ifndef SAMPLE_FULLY_LOOPING_H

#define SAMPLE_FULLY_LOOPING_H

/**
 * Samples a sound effect which loops its ending segment.  Nearest neighbor
 * interpolation is used.
 * @param sound_effect_length The length of the sound effect to sample, in
 *                            samples.  Behavior is undefined if less than 1.
 * @param sound_effect_loop_from The index of the sample from which the loop
 *                               starts.  Behavior is undefined if less than 1
 *                               or greater than or equal to the sound effect's
 *                               length minus 1.
 * @param sound_effect_samples The samples within the sound effect, from sooner
 *                             to later.  Behavior is undefined if any are NaN,
 *                             infinity or negative infinity.
 * @param from_sound_effect_sample The index of the sample to play at the start
 *                                 of the output.  Behavior is undefined if NaN,
 *                                 infinity, negative infinity or unable to be
 *                                 cast to int.
 * @param from_left_gain The gain to apply to the sound effect in the left
 *                       channel at the start of the output, where 0 is silent
 *                       and 1 is unity.  Behavior is undefined if NaN, infinity
 *                       or negative infinity.
 * @param from_right_gain The gain to apply to the sound effect in the right
 *                        channel at the start of the output, where 0 is silent
 *                        and 1 is unity.  Behavior is undefined if NaN,
 *                        infinity or negative infinity.
 * @param to_sound_effect_sample The index of the sample to play at the end of
 *                               the output.  Behavior is undefined if NaN,
 *                               infinity, negative infinity or unable to be
 *                               cast to int.
 * @param to_left_gain The gain to apply to the sound effect in the left channel
 *                     at the end of the output, where 0 is silent and 1 is
 *                     unity.  Behavior is undefined if NaN, infinity or
 *                     negative infinity.
 * @param to_right_gain The gain to apply to the sound effect in the right
 *                      channel at the end of the output, where 0 is silent and
 *                      1 is unity.  Behavior is undefined if NaN, infinity or
 *                      negative infinity.
 * @param output_length The length of the output to add the sampled sound effect
 *                      to, in samples.  Behavior is undefined if less than 1.
 * @param left_output_samples The left channel of the samples to add the sampled
 *                            sound effect to, from sooner to later.  Behavior
 *                            is undefined if any are NaN, infinity or negative
 *                            infinity.
 * @param right_output_samples The right channel of the samples to add the
 *                             sampled sound effect to, from sooner to later.
 *                             Behavior is undefined if any are NaN, infinity or
 *                             negative infinity.
 */
void sample_fully_looping(
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
    float *const right_output_samples);

#endif
