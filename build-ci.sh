#!/bin/sh

# MSYSTEM is defined when cross-compilig with MinGW/MSYS
if [ "x$MSYSTEM" != "x" ] ; then
  echo Updating MinGW32/cross version.
  WXURUSBUILD="--build=i686-w64-mingw32"
  WXURUSHOST="--host=i686-w64-mingw32"
  WXURUSTARGET="--target=i686-w64-mingw32"
  WXURUSCONF="--with-msw --enable-monolithic --enable-shared CFLAGS=-Wno-unused-local-typedefs CXXFLAGS=-Wno-unused-local-typedefs LDFLAGS=-Wl,--allow-multiple-definition"
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
    WXURUSCONF="--with-gtk --enable-monolithic --enable-shared"
    URUSSTUDIOPLAT="--with-platform=gtk"
  fi
fi

export URUSINSTALLDIR=/system/urus
export URUSSTDTOPDIR=$(pwd)

cd modules/wxWidgets

export WXURUSTOPDIR=$(pwd)
mkdir -p buildwx
cd buildwx

../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --prefix=${URUSINSTALLDIR} --enable-unicode --with-flavour=urus --enable-vendor=urus $WXURUSCONF
make
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

        ../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --with-contrib-plugins="AutoVersioning, BrowseTracker, Cccc, CppCheck, cbkoders, codesnippets,codestat, copystrings, Cscope, dragscroll, EditorConfig, EditorTweaks, envvars,FileManager, headerfixup, hexeditor, incsearch, keybinder, libfinder, MouseSap, ProjectOptionsManipulator, profiler, regex, ReopenEditor,smartindent,symtab, ThreadSearch, wxcontrib, wxsmith, wxsmithcontrib, wxsmithaui" --prefix=${URUSINSTALLDIR} $URUSSTUDIOPLAT
        make
        make install
    fi
fi

echo BUILD OK!
exit 0
