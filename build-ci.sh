#!/bin/sh
export PATH=/d/hiro/codeblocks_dev/i686-w64-mingw32/bin:$PATH
# MSYSTEM is defined when cross-compilig with MinGW/MSYS
if [ "x$MSYSTEM" != "x" ] ; then
  echo Updating MinGW32/cross version.
  WXURUSBUILD="--build=i686-w64-mingw32"
  WXURUSHOST="--host=i686-w64-mingw32"
  WXURUSTARGET="--target=i686-w64-mingw32"
  WXURUSCONF="--with-msw --enable-monolithic --enable-shared CFLAGS=-Wno-unused-local-typedefs CXXFLAGS=-Wno-unused-local-typedefs LDFLAGS=-Wl,--no-undefined"
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
    WXURUSCONF="--with-gtk --enable-monolithic"
    URUSSTUDIOPLAT="--with-platform=gtk"
  fi
fi

export URUSSTDTOPDIR=$(pwd)

cd modules/wxWidgets

export WXURUSTOPDIR=$(pwd)
mkdir -p buildwx
cd buildwx

../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --prefix=${URUSSTDTOPDIR}/install --enable-unicode --with-flavour=urus --enable-vendor=urus $WXURUSCONF
make
make install

#Only for Unix Like, on Windows we don't make it.
if [ "x$MSYSTEM" = "x" ] ; then
    export PATH=${URUSSTDTOPDIR}/install/bin:$PATH
    export ACLOCAL_FLAGS="-I `wx-config --prefix`/share/aclocal"

    cd ${URUSSTDTOPDIR}
    ./bootstrap
    mkdir -p buildustd
    cd buildustd

    ../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --with-contrib-plugins="AutoVersioning, BrowseTracker, Cccc, CppCheck, cbkoders, codesnippets,codestat, copystrings, Cscope, dragscroll, EditorConfig, EditorTweaks, envvars,FileManager, headerfixup, hexeditor, incsearch, keybinder, libfinder, MouseSap, ProjectOptionsManipulator, profiler, regex, ReopenEditor,smartindent,symtab, ThreadSearch, wxcontrib, wxsmith, wxsmithcontrib, wxsmithaui" --prefix=${URUSSTDTOPDIR}/install $URUSSTUDIOPLAT
    make
    make install
fi

echo BUILD OK!
exit 0
