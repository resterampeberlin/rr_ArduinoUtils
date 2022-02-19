#
# @file packageLib.py
# @author M. Nickels
# @brief package the library into a .tar.gz file
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

import gitVersion
import json
import os

# compile the library package if necessary


def package(source, target, env):
    template = os.path.join(env["PROJECT_DIR"], "library-template.json")

    # check for valid template file
    if os.path.isfile(template):
        f = open(template)
        data = json.load(f)

        if "name" in data:
            print("Create library.json ...")

            # create library.json with correct version tag
            env.Execute(
                "sed s/GIT_VERSION/"+gitVersion.short()+"/ "+template+" > lib/library.json")

            # package library in tar.gz file
            print("Packaging library ...")

            env.Execute(
                "pio package pack lib --output "+data["name"]+".tar.gz")
        else:
            print("Package name not defined in "+template)
    else:
        print(template+" not found")
