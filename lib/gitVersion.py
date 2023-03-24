#
# @author M. Nickels
# @brief retrieve the git version tag for the current project
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

import subprocess

# get short version from git tag ("x.x.x")


def short():
    ret = subprocess.run(["git", "describe", "--abbrev=0","--tags"],
                         stdout=subprocess.PIPE, text=True)
    version = ret.stdout.strip()

    # set version to default if no tag is set
    if not version:
        version = "0.0.0"

    return version

# get long version from git tag ("x.x.x-tag-dirty")


def long():
    ret = subprocess.run(["git", "describe", "--dirty","--tags"],
                         stdout=subprocess.PIPE, text=True)
    version = ret.stdout.strip()

    # set version to default if no tag is set
    if not version:
        version = "0.0.0-no-tag"

    return version


# get the build flag for the version string


def cppDefine():
    print("-DGIT_VERSION=\\\""+long()+"\\\"")
