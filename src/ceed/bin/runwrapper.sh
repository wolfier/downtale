#!/bin/bash

# Sure the linker gurus wouldn't approve, but I use this to avoid having to mess
# with RPATH or having to install everything when I rebuild

# Obviously doesn't work on Windows ;-) But works OK on Linux and MacOSX

# parent dir of this script
PARENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# when we are at it, add ceed-gui, ceed-mic and ceed-migrate to $PATH
export PATH=$PARENT_DIR:$PATH

# relative to where you run the script from or absolute (probably a more robust solution)
CEGUI_BUILD_PATH="/lusr/opt/cegui-0.8.ceed"
# directory where the "ceed" package is located
CEED_PACKAGE_PATH="$PARENT_DIR/../"

# Not needed with the new RPATH stuff in 0.8
export LD_LIBRARY_PATH="$CEGUI_BUILD_PATH/lib:$LD_LIBRARY_PATH"

export PYTHONPATH="$CEGUI_BUILD_PATH/lib/python2.7/dist-packages/cegui-0.8:$CEED_PACKAGE_PATH:$PYTHONPATH"

if [ "x$RUNWRAPPER_NO_FORK" != "x1" ]; then
    # fork a new shell to avoid polluting the environment
    bash
fi


