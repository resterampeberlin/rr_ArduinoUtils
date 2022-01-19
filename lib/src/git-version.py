import subprocess

Import ("env")

def git_version_build_flag():
    ret = subprocess.run(["git", "describe", "--dirty"], stdout=subprocess.PIPE, text=True) 
    build_version = ret.stdout.strip()
    build_flag = "-D GIT_VERSION=\\\"" + build_version + "\\\""
    print ("GIT Version: " + build_version)
    return (build_flag)

env.Append(
    BUILD_FLAGS=[git_version_build_flag()]
)