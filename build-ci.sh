#!/bin/sh

# MSYSTEM is defined when cross-compilig with MinGW/MSYS
if [ "x$MSYSTEM" != "x" ] ; then
  echo Updating MinGW32/cross version.
  WXURUSBUILD="--build=i686-w64-mingw32"
  WXURUSHOST="--host=i686-w64-mingw32"
  WXURUSTARGET="--target=i686-w64-mingw32"
  CFLAGS+=-Wno-unused-local-typedefs
  CXXFLAGS+=-Wno-unused-local-typedefs
  CXXFLAGS+=-fpermissive
  WXURUSCONF="--with-msw --enable-monolithic --enable-shared LDFLAGS=-Wl,--allow-multiple-definition"
  URUSSTUDIOPLAT="--with-platform=win32"
else
  uname_str=$(uname)
  if [ "$uname_str" = "Darwin" ] ; then
    echo Updating Mac / Darwin version.
    WXURUSBUILD=""
    WXURUSHOST=""
    WXURUSTARGET=""
    WXURUSCONF="--with-mac --enable-monolithic"
    URUSSTUDIOPLAT="--with-platform=macosx"
  else
    echo Updating Linux version.
    WXURUSBUILD=""
    WXURUSHOST=""
    WXURUSTARGET=""
    export CXXFLAGS="-Wno-unused-local-typedefs -Wno-narrowing -Wno-literal-suffix"
    export CFLAGS="-Wno-unused-local-typedefs -Wno-narrowing"
    WXURUSCONF="--with-gtk=2 --enable-monolithic --enable-shared --with-libpng=builtin --with-regex=builtin --with-libjpeg=builtin --with-libtiff=builtin --with-expat=builtin"
    URUSSTUDIOPLAT="--with-platform=gtk2"
  fi
fi

export URUSINSTALLDIR=/system/urus
export URUSSTDTOPDIR=$(pwd)

cd modules/wxWidgets

export WXURUSTOPDIR=$(pwd)
mkdir -p buildwx
cd buildwx

../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --prefix=${URUSINSTALLDIR} --enable-unicode --with-flavour=urus --enable-vendor=urus $WXURUSCONF
make -j2
make install

#Only for Unix Like, on Windows we don't make it.
if [ "x$NO_BUILD_ALL" = "x" ] ; then
    if [ "x$MSYSTEM" = "x" ] ; then
        export PATH=${URUSINSTALLDIR}/bin:$PATH
        export ACLOCAL_FLAGS="-I `wx-config --prefix`/share/aclocal"

        cd ${URUSSTDTOPDIR}
        ./bootstrap
        mkdir -p buildustd
        cd buildustd

        ../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --with-contrib-plugins="BrowseTracker,Cscope,EditorConfig,EditorTweaks,envvars,hexeditor,incsearch,ProjectOptionsManipulator,regex,ReopenEditor,smartindent,ThreadSearch,wxcontrib,wxsmith,wxsmithcontrib,wxsmithaui" --prefix=${URUSINSTALLDIR} $URUSSTUDIOPLAT

        if [ "x$NO_URUSSTUDIO_MAKE_CMD" = "x" ] ; then
            make -j2
            make install
        fi
        cd ${URUSSTDTOPDIR}
    fi
fi

echo BUILD OK!
exit 0
