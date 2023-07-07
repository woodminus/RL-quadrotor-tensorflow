#!/bin/bash

BASEDIR=`pwd`
INSTALLDIR=${BASEDIR}/installdir
BUILDDIR=${BASEDIR}/builddir
PATH=${PATH}:${INSTALLDIR}/bin
#mkdir ${INSTALLDIR}
#mkdir ${BUILDDIR}

export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${INSTALLDIR}/lib"
export PATH="${PATH}:${INSTALLDIR}/bin"

#echo "installing Box2D"
#git c