import subprocess

Import("env")

print(env)


# retrieve current git tag

def git_version():
    print("Retrieve GIT version:")
    ret = subprocess.run(["git", "describe", "--dirty"],
                         stdout=subprocess.PIPE, text=True)
    version = ret.stdout.strip()

    print("GIT Version: " + version)

    return (version)


env.Append(
    CPPDEFINES=[("GIT_VERSION", "\\\""+git_version()+"\\\"")]
)
