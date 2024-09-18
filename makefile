ifeq ($(OS),Windows_NT)
	CC = x86_64-w64-mingw32-gcc
else
	CC = clang
endif

CFLAGS = -Wall -Wextra -Werror -std=c99 -nostdlib -ffreestanding -O3 -pedantic

# Unfortunately, I have found that make quite often selects the wrong shell
# (e.g. PowerShell), so commands like "find" won't work unless we explicitly
# specify bash.  You also can't use a variable for this (e.g. $(SHELL)) as make
# inexplicably tries to read something from the PATH and fails.  So hardcoding a
# reference to bash seems to be the only way to get a working build.
C_FILES = $(shell bash -c "find src -type f -iname ""*.c""") $(shell bash -c "find tests/helpers -type f -iname ""*.c""")
H_FILES = $(shell bash -c "find src -type f -iname ""*.h""") $(shell bash -c "find tests/helpers -type f -iname ""*.h""")
O_FILES = $(patsubst %.c,obj/%.o,$(C_FILES))
TOTAL_REBUILD_FILES = makefile $(H_FILES)

TESTS = $(patsubst tests/cases/%, %, $(shell bash -c "find tests/cases -mindepth 1 -maxdepth 1 -type d"))

test: $(addprefix tests/pass_markers/, $(TESTS))

dist/%: tests/cases/%/main.c $(O_FILES)
	mkdir -p $(dir $@)
	$(CC) $(CLAGS) -flto $^ -o $@

obj/%.o: %.c $(TOTAL_REBUILD_FILES)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

tests/cases/%/outputs/actual/output_samples/left.raw: \
	dist/% \
	tests/cases/%/inputs/output_samples/left.raw \
	tests/cases/%/inputs/output_samples/right.raw \
	tests/cases/%/inputs/sound_effect.raw
	mkdir -p $(dir $@)
	cd tests/cases/$* && ../../../dist/$*

tests/cases/%/outputs/actual/output_samples/right.raw: tests/cases/%/outputs/actual/output_samples/left.raw
	echo

tests/cases/%/outputs/actual/sound_effect.raw: tests/cases/%/outputs/actual/output_samples/left.raw
	echo

tests/cases/%.hex: tests/cases/%.raw
	xxd $< > $@

tests/pass_markers/%: \
		tests/cases/%/outputs/expected/output_samples/opacities.hex \
		tests/cases/%/outputs/expected/output_samples/reds.hex \
		tests/cases/%/outputs/expected/sound_effect.hex \
		tests/cases/%/outputs/actual/output_samples/opacities.hex \
		tests/cases/%/outputs/actual/output_samples/reds.hex \
		tests/cases/%/outputs/actual/sound_effect.hex
	diff tests/cases/$*/outputs/expected/output_samples/left.hex tests/cases/$*/outputs/actual/output_samples/left.hex
	diff tests/cases/$*/outputs/expected/output_samples/right.hex tests/cases/$*/outputs/actual/output_samples/right.hex
	diff tests/cases/$*/outputs/expected/sound_effect.hex tests/cases/$*/outputs/actual/sound_effect.hex
	mkdir -p $(dir $@)
	touch $@

clean:
	rm -rf obj dist $(patsubst %, tests/cases/%/outputs/actual, $(TESTS)) tests/pass_markers
