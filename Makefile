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

#
# Build Process:
# 	1. Sets variables
# 	2. Backs up the build/cpuX and build/mission_inc directories
#		3. Makes config and makes (build)
#		4. Moves the binary output to the bin directory
#		5. Deletes the build/cpuX and build/mission_inc directories
#		6. Restores the original build/cpuX and build/mission_inc directories
#
all ::
	bash -c "source ./setvars.sh; \
	rm -rf bin/*; \
	cp -av build/$(BUILD_CPU) build/$(BUILD_CPU)~; \
	cp -av build/mission_inc build/mission_inc~; \
	$(MAKE) -C build/$(BUILD_CPU) config; \
	$(MAKE) -C build/$(BUILD_CPU); \
	rm -vrf bin; mv -v build/$(BUILD_CPU)/exe bin; \
	rm -vrf build/$(BUILD_CPU) build/mission_inc; \
	mv -v build/$(BUILD_CPU)~ build/$(BUILD_CPU); \
	mv -v build/mission_inc~ build/mission_inc;"


clean ::
	$(MAKE) -C build clean
