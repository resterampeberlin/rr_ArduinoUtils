#
# @file documentation.py
# @author M. Nickels
# @brief Generate doxygen documentation for the current project
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

import gitVersion as gitVersion
import os

# generate documentation


def generate(source, target, env):
    if os.path.isfile(os.path.join(env['PROJECT_DIR'], "Doxyfile")):
        command = "(cat Doxyfile; echo \"PROJECT_NUMBER=" + \
            gitVersion.short() + "\" ) | doxygen -"

        print("Creating documentation ...")

        env.Execute(command)
    else:
        print("No Doxyfile found")
