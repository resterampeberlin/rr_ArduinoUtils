#
# @file rr_ArduinoUtils.py
# @author M. Nickels
# @brief install build callbacks
# @version 0.1
# @date 2021-12-20
#
# @copyright Copyright (c) 2021
#
# This work is licensed under the
#
#      Creative Commons Attribution-NonCommercial 4.0 International License.
#
# To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/
# or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
#

import pioLib
import documentation

Import("env")

# Add custom targets 'doc' and 'package'

env.AddCustomTarget(
    "doc",
    "$BUILD_DIR/${PROGNAME}.elf",
    documentation.generate)

env.AddCustomTarget(
    "package",
    "$BUILD_DIR/${PROGNAME}.elf",
    pioLib.package)
