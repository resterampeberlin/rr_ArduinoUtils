#! /bin/bash
# repository for the PlatformIO libary (not the current code repository!)
# used by lib_deps=
REMOTE_LIB_GIT=https://github.com/resterampeberlin/RRArduinoUtilities.git

# only accept version like 1.2.3
VERSION=$(echo $1 | grep -Eo "^[[:digit:]]+\.[[:digit:]]+\.[[:digit:]]+$") 

# create new tagged version
if [ -n "$VERSION" ]
then
    if [ -n "$(git status --porcelain)" ]; then 
        echo "Commit changes before deploying"
        exit 0
    fi

    echo "Creating new version $1"

    # create version tag
    git tag $VERSION

    # this will create a lib/library.json with a new version number
    pio run -t package

    git add --all
    git commit -m "Deployed version $VERSION"

    # push source code 
    git push
    git push --tags

    # push subtree to PIO library
    git subtree push --prefix=lib $REMOTE_LIB_GIT master

    echo "New version $1 deployed"
else
    echo "No version number specified or wrong format. Will only update documentation"
fi

# create documentation
pio run -t doc
pushd docs

# look for branch gh-pages in current directory/repo and 
# push all files to repo
if [[ $(git branch --no-color --show-current) = 'gh-pages' ]]; then
    git add --all
    git commit -m "Documentation updated"
    git push origin gh-pages

    echo "Documentation updated"
else
    echo "No gh-pages branch found"
fi

popd

exit 1
