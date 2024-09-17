# Samples

C library to sample audio.

## Usage

### Project Level

Your application's build pipeline will need to be configured to compile each C
file in the [src](./src) directory and recompile every C file should any H files
change.  Then, include each H file in the same directory to make its
corresponding function available.

### Assumptions

- The compilation environment supports C99.
- The audio being sampled:
  - Uses 32-bit floats for each sample.
  - Is monaural.
  - Runs sooner to later.
- The output:
  - Uses 32-bit floats for each sample.
  - Is stereo.
  - Runs sooner to later.
  - Is planar (not interleaved).
- No float arguments:
  - Are NaN.
  - Are infinity.
  - Are negative infinity.
  - Cannot be cast to `int` without undefined behavior (for example, very large
    values).

### Functions

| Name                       | Description                                                                         |
| -------------------------- | ----------------------------------------------------------------------------------- |
| `sample_non_looping`       | Plays a sound effect once.  Only silence follows.                                   |
| `sample_fully_looping`     | Repeats a sound effect indefinitely.                                                |
| `sample_partially_looping` | Plays the start of a sound effect once, then loops the ending segment indefinitely. |

## Tests

Execute `make` to run the test suite.

### Dependencies

- Make.
- MinGW-GCC for Windows, Clang for all other platforms.
- Bash.
