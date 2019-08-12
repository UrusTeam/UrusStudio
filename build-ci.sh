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
    export CXXFLAGS="-Wno-unused-local-typedefs -Wno-narrowing -Wno-literal-suffix -fpermissive"
    export CFLAGS="-Wno-unused-local-typedefs -Wno-narrowing"
    export WXURUSCONF="--with-gtk=2 --enable-monolithic --enable-shared --enable-std_string --enable-threads --disable-debug_flag --disable-precomp-headers --with-libpng=builtin --with-regex=builtin --with-libjpeg=builtin --with-libtiff=builtin --with-expat=builtin --enable-threads"
    #export OPENGL_LIBS="-L/usr/lib/$MACHTYPE/libGL.so"
    #export LDFLAGS="-lGL -lGLU -lGLEW"
    export URUSSTUDIOPLAT="--with-platform=gtk2 --disable-debug --disable-pch --disable-fortran"
  fi
fi

export URUSINSTALLDIR=/system/urus
export URUSSTDTOPDIR=$(pwd)

cd modules/wxWidgets
export WXURUSTOPDIR=$(pwd)

cd $URUSINSTALLDIR

if [ -e $URUSINSTALLDIR/.git ] ; then
  echo "git ok"
else
  echo "git init"
  git init $URUSINSTALLDIR
  git config --global user.email $(printf "%s@%s" ${USER} $(uname -n))
  git config --global user.name ${USER}
fi

echo $SECONDS > .empty
git add .
git commit -m "added backup."

cd $WXURUSTOPDIR
mkdir -p buildwx
cd buildwx

../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --prefix=${URUSINSTALLDIR} --enable-unicode --with-flavour=urus --enable-vendor=urus $WXURUSCONF
make -j2
make -j2 install

PUSHD=$(pwd)
cd $URUSINSTALLDIR
echo $SECONDS > .empty
git add .
git commit -m "added wxWidgets urus."
cd $PUSHD

#Only for Unix Like, on Windows we don't make it.
if [ "x$NO_BUILD_ALL" = "x" ] ; then
    if [ "x$MSYSTEM" = "x" ] ; then
        export PATH=${URUSINSTALLDIR}/bin:$PATH
        export ACLOCAL_FLAGS="-I `wx-config --prefix`/share/aclocal"

        cd ${URUSSTDTOPDIR}
        ./bootstrap
        mkdir -p buildustd
        cd buildustd

        ../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --with-contrib-plugins="BrowseTracker,Cccc,CppCheck,codesnippets,headerfixup,hexeditor,incsearch,ProjectOptionsManipulator,regex,ReopenEditor,smartindent,symtab,ThreadSearch,ToolsPlus,wxcontrib,wxsmith,wxsmithcontrib,wxsmithaui" --prefix=${URUSINSTALLDIR} $URUSSTUDIOPLAT
        make -j2
        make -j2 install

        PUSHD=$(pwd)
        cd $URUSINSTALLDIR
        mkdir -p $HOME/.tempurus
        WXVERSION=$(wx-config --version)
        echo $SECONDS > .empty
        git add .
        git commit -m "added urusstudio."
        git checkout master-urusstudio || git checkout -b master-urusstudio
        git clean -fdx
        git reset --hard
        git rm -rf *
        git commit -m "removed all."
        git cherry-pick HEAD~1
        ARCHOS=$(printf "%s-%s" $(uname -s) $(uname -m))
        ARCHOS=$(echo $ARCHOS | tr A-Z a-z)
        tar -cvzf $HOME/.tempurus/host-${ARCHOS}-wx${WXVERSION}-gtk2-urusstudio.tar.gz *
        git checkout master-wx || git checkout -b master-wx
        git reset --hard HEAD~3
        tar -cvzf $HOME/.tempurus/host-${ARCHOS}-wx-${WXVERSION}-urus-gtk2.tar.gz *
        git checkout master
        git reset --hard
        cd $PUSHD
    fi
fi

echo BUILD OK!
exit 0
