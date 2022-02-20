# Purpose

This library is a collection of useful utilities for Arduino development, especially with PlatformIO. It 
contains the following components:

- **rr_DebugUtils** provides an interface for debug output to terminal. The code is only included in debug builds and 
does not consume program space in the release build. 
Additionally it provides an interface to show to git version and build of a program.

- **rr_Intervall** provied an interface for task which should be executed periodically in a programm. Additionally it provides
statistical functions to analyse program behauviour.

- **documentation** provides a build target to produce source code documentation with doxgen. 
It is invoked with `pio run - t doc`

- **library packaging** provides a build target to package a PlatformIO library. 
It is invoked with `pio run - t package`

# Installation

# Generate Doxygen source code documentation

In order to document your source code you need 3 components:

1. doxygen installed (e.g. on Mac OS X `brew install doxygen`)
2. A doxygen configation file `Doxyfile` in the project directory. Create it from scratch with `doxygen -g`
3. Documented source code (see [doxygen documentation](https://www.doxygen.nl/)for details)

When ypu invoke `pio run - t doc` the documentation will be produced. 

The following settings in the 'Doxyfile' will be automatically set with this command:
- **PROJECT_NUMBER** will be replaced by 'git tag'
- **PROJECT_BRIEF** will be replaced by library description in `library-template.json`
- **PROJECT_NAME** will be replaced by library name in `library-template.json`

The last two points are only applicable if you build a library. 
For a normal programm you should set those values in `Doxyfile`

# Create a PlatformIO library and package it

# Documentation

For source code documentation see this [page](https://resterampeberlin.github.io/rr_ArduinoUtils/).

# License:

[![License: CC BY-SA 4.0](https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-sa/4.0/)

This open source code project is has been proudfully producted in Berlin (and other places around the globe) by

![Logo](Logo180x180.png)



