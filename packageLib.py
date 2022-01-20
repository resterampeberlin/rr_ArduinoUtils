import os
from SCons.Script import COMMAND_LINE_TARGETS
Import("env", "projenv")

#
# Dump build environment (for debug purpose)
# print(env.Dump())
#

#
# (Optional) Do not run extra script when IDE fetches C/C++ project metadata
#

if "idedata" in COMMAND_LINE_TARGETS:
    env.Exit(0)


def createLibraryDescription(source, target, env):
    print("Create library.json")

    version = os.popen("git describe --abbrev=0").read().rstrip()

    print("Current version is " + version)

    env.Append(GIT_VERSION=version)

    # create library.json with correct version tag
    env.Execute(
        "sed s/GIT_VERSION/$GIT_VERSION/ library-template.json > lib/library.json")


def packageLibrary(source, target, env):
    print("Packaging library")

    env.Execute(
        "pio package pack lib --output RRArduinoUtilities.tar.gz")


env.AddPreAction("buildprog", createLibraryDescription)
env.AddPreAction("buildprog", Delete("RRArduinoUtilities.tar.gz"))
env.AddPostAction("buildprog", packageLibrary)
