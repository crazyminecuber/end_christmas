.DELETE_ON_ERROR:# Deletes target file if recipie fails

TARGET_EXEC = play
BUILD_DIR = .build
SRC_DIRS = src

CCC=g++
RM=rm
#Linker flags
LDFLAGS = -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system
# MMD Generate .d files as part of compilation.
# MP Generate phony targets for all dependencys. Solves som problems if files are delted
# MT Target name for the make-rule,
# MF Filename for the to-be generated dependency file
DEPFLAGS=-MMD -MP -MT $@
# Allows for multiple src directorys
SRCS = $(shell find $(SRC_DIRS) -name *.cc)
SRCS := $(filter-out %test_main.cc, $(SRCS))
SRCS := $(filter-out %tests.cc, $(SRCS))
# will result in uggly .cc.o extension?
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Adds the multiple src directorys to the compiler options
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# std=c++17 use C++17 standard
# -g, generate information to be used in for example valgrind
# -Wall, inlcude all warnings
# -pedantic, gives more warnings
CFLAGS= $(INC_FLAGS) -std=c++17 -g -Wall -Wextra -pedantic -fmax-errors=5
#.PHONY targets, declares that target is not associated with file and will always
# be run if it is a dependency
.PHONY: clean, test, p


# Compiles main target from all .o files.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CCC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

p: play

	./play

all: $(OBJS)
	@echo "objects $(OBJS)"

test: all test_main.o tests.cc
	$(CCC) $(CFLAGS) -o test tests.cc $(OBJS) $(LDFLAGS)
	./test

test_main.o: test_main.cc
	$(CCC) $(CFLAGS) -c test_main.cc

# Creates o-files from cc-files. $* becomes what % is in the pattern. Make will
# automatically add all dependencys from in here from the -dfiles in the include
# statement. The .d files are regenerated with this command as well so that the
# dependency files always reflect the last compiled version. And since the
# comilation process only was dependent on the files listed in the .d file, it
# should be impossible to modify files in any way and have it not be correctly
# recompiled when any of the dependent files change.
$(BUILD_DIR)/%.cc.o: %.cc | $(BUILD_DIR)/src
	$(CCC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Makes directory
$(BUILD_DIR)/src:
	mkdir -p $@


# This is here to do nothing if the .d file does not exist.
$(DEPS):

dox:
	doxygen doxyconf

clean:
	$(RM) -r $(BUILD_DIR)

debug:
	@echo "$(SRCS)"

# Appends dependencys to all existing rules. Will be the dependencys at the last
# compilation time, but will be utdated immediatetlly after compilation is done.
# This is not a problem since it does only looks at the dependency files to
# figure out if enough has changed inorder to require recompilation of a certain
# file.
include $(DEPS)





