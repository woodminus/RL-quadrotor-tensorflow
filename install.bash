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
#git clone https://github.com/erincatto/Box2D.git Box2D
#BOX2DDIR=${BUILDDIR}/build-box2d
#mkdir ${BOX2DDIR}
#cd ${BOX2DDIR}
#cmake -DBOX2D_INSTALL=ON -DBOX2D_BUILD_SHARED=ON -DCMAKE_INSTALL_PREFIX=${INSTALLDIR} ${BASEDIR}/Box2D/Box2D
#make
#make install
#cd ${BASEDIR}

#echo "installing tensorflow"
#BAZELDIR=${BUILDDIR}/bazel
#git clone https://github.com/bazelbuild/bazel.git ${BAZELDIR}
#cd ${BAZELDIR}
#./compile.sh
#cp output/bazel ${INSTALLDIR}/bin
#cd ${BASEDIR}


#git clone https://github.com/tensorflow/tensorflow Tensorflow
#git checkout tags/v0.10.0

#tensorflow
#cd ${BASEDIR}
#git clone --recurse-submodules https://github.com/tensorflow/tensorflow Tensorflow
#cd Tensorflow
#./configure
#bazel build -c opt //tensorflow/tools/pip_package:build_pip_package
#bazel-bin/tensorflow/tools/pip_package/build_pip_package /tmp/tensorflow_pkg
#sudo pip 