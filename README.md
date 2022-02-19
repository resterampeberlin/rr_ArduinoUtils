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

# Documentation

For source code documentation see this [page](doc/html/index.html).

# License:

[![License: CC BY-SA 4.0](https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-sa/4.0/)



