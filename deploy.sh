#! /bin/bash
# repository for the PlatformIO libary (not the current code repository!)
# used by lib_deps=
REMOTE_LIB_GIT=https://github.com/resterampeberlin/RRArduinoUtilities.git

# only accept version like 1.2.3
VERSION=$(echo $1 | grep -Eo "^[[:digit:]]+\.[[:digit:]]+\.[[:digit:]]+$") 

# check if tools installed
if ! [ -x "$(command -v pio)" ]; then
  tput setaf 1; echo 'Error: pio is not installed.' ; tput setaf 7
  exit 1
fi

# create new tagged version
if [ -n "$VERSION" ]
then
    if [ -n "$(git status --porcelain)" ]; then 
        tput setaf 1; echo "Commit changes before deploying"; tput setaf 7
        exit 1
    fi

    if [ -n "$(git tag | grep $VERSION)" ]; then 
        tput setaf 1; echo "Version tag $VERSION exists. Use a unique version tag!"; tput setaf 7
        exit 1
    fi

    echo "Creating new version $1"

    # create version tag
    git tag $VERSION

    # this will create a lib/library.json with a new version number
    pio run --silent --target package

    git add --all
    git commit --message "Deployed version $VERSION"

    # push source code 
    git push
    git push --tags

    # push subtree to PIO library
    git subtree push --prefix=lib $REMOTE_LIB_GIT master

    tput setaf 2; echo "New version $1 deployed"; tput setaf 7
else
    echo "No version number specified or wrong format. Will only update documentation"
fi

# create documentation
pio run --silent --target doc
cd docs

# look for branch gh-pages in current directory/repo and 
# push all files to repo
if [[ $(git branch --no-color --show-current) = 'gh-pages' ]]; then
    git add --all
    git commit --message "Documentation updated"
    git push origin gh-pages

    tput setaf 2; echo "Documentation updated"; tput setaf 7 
else
    tput setaf 1; echo "No gh-pages branch found"; tput setaf 7 
fi

cd .. 

exit 0
