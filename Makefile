#------------------------------------------------------------
# File: Makefile
#
# Purpose:
#   Main Makefile for the cFE core build and application.
# 	Builds and cleans the project.
# Requires:
#		The environment variables: BUILD_CPU and BUILD_OUTPUT
#		are required to be set and initialized prior to running
#		this Makefile.
#------------------------------------------------------------

all ::
	bash -c "source ./setvars.sh; \
	$(MAKE) -C build/$(BUILD_CPU) config; \
	$(MAKE) -C build/$(BUILD_CPU); \
	mv build/$(BUILD_CPU) $(BUILD_OUTPUT)"

clean ::
	$(MAKE) -C build clean
