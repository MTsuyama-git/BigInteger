#!/bin/sh
CWD=$(dirname $(dirname $(cd $(dirname $0) && pwd)))
cd ${CWD}
if [ "$1" = "Debug" ];then
        DEST=build.dbg
        BuildType=Debug
    else
        DEST=build
        BuildType=Release
    fi
if [ ${OS} == Windows_NT ]; then
    DEST=build    
    cmake -S . -B ${DEST}
    cmake --build ${DEST} --config ${BuildType}
else    
    cmake -S . -G Ninja -B ${DEST} -DCMAKE_BUILD_TYPE=${BuildType}
    cmake --build ${DEST}
fi


