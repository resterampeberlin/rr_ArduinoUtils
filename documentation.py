#
# @author M. Nickels
# @brief Generate doxygen documentation for the current project
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
import json


# generate documentation


def generate(source, target, env):
    if os.path.isfile(os.path.join(env['PROJECT_DIR'], "Doxyfile")):
        template = "library-template.json"

        projectBrief = ""
        projectName = ""
        projectNumber = gitVersion.short()

        # extract information from libary-template.json
        if os.path.isfile(template):
            with open(template, 'r') as f:
                data = json.load(f)

            if "name" in data:
                projectName = data["name"]

            if "description" in data:
                projectBrief = data["description"]

        # feed values into doxygen
        command = "(cat Doxyfile; "
        command = command + "echo \"PROJECT_NUMBER=" + projectNumber + "\";"

        if projectBrief:
            command = command + "echo \"PROJECT_BRIEF=" + projectBrief + "\";"

        if projectName:
            command = command + "echo \"PROJECT_NAME=" + projectName + "\";"

        command = command + " ) | doxygen -"

        print("Creating documentation ...")

        env.Execute(command)
    else:
        print("No Doxyfile found")
