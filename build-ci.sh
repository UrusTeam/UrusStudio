#!/bin/sh

if [ "x$CROSS" != "x" ] ; then
    export CROSSTAIL="$CROSS-"
fi

# MSYSTEM is defined when cross-compilig with MinGW/MSYS
if [ "x$MSYSTEM" != "x" ] ; then
  echo Updating MinGW32/cross version.
  WXURUSBUILD=""
  WXURUSHOST="--host=$CROSS"
  WXURUSTARGET="--target=$CROSS"
  export HOSTTARGET="${CROSSTAIL}gcc -dumpmachine"
  export LIBS=" -lwindowscodecs"
  export LDFLAGS="-Wl,--gc-sections -Wl,--allow-multiple-definition"
  export CFLAGS="-Wno-unused-local-typedefs -ffunction-sections -fdata-sections"
  export CXXFLAGS='-Wno-unused-local-typedefs -fpermissive -ffunction-sections -fdata-sections'
  WXURUSCONF="--with-msw --enable-monolithic --enable-shared --with-opengl --enable-graphics_ctx --enable-cmdline --enable-threads --disable-debug_flag --disable-precomp-headers --disable-debug --with-libpng=builtin --with-regex=builtin --with-libjpeg=builtin --with-libtiff=builtin --with-expat=builtin LDFLAGS=-Wl,--allow-multiple-definition"
  URUSSTUDIOPLAT="--with-platform=win32 --disable-debug --disable-pch --disable-fortran"
else
  uname_str=$(uname)
  if [ "$uname_str" = "Darwin" ] ; then
    echo Updating Mac / Darwin version.
    WXURUSBUILD=""
    WXURUSHOST=""
    WXURUSTARGET=""
    export HOSTTARGET="${CROSSTAIL}gcc -dumpmachine"
    export CC=clang
    export CXX=clang++
    WXURUSCONF="--with-mac --with-macosx-version-min=10.10 --enable-monolithic --enable-shared --with-opengl --enable-threads --disable-debug_flag --disable-debug --disable-precomp-headers --with-libpng=builtin --with-regex=builtin --with-libjpeg=builtin --with-libtiff=builtin --with-expat=builtin"
    URUSSTUDIOPLAT="--with-platform=macosx"
  else
    echo Updating Linux version.
    WXURUSBUILD=""
    WXURUSHOST="--host=$CROSS"
    WXURUSTARGET="--target=$CROSS"
    export HOSTTARGET="${CROSSTAIL}gcc -dumpmachine"
    export CXXFLAGS="-Wno-unused-local-typedefs -Wno-narrowing -Wno-literal-suffix -fpermissive -DGTK_VERSION=2 -O2 $CXXFLAGS"
    export CFLAGS="-Wno-unused-local-typedefs -Wno-narrowing -O2 $CFLAGS"
    export WXURUSCONF="--with-gtk=2 --enable-cmdline --enable-graphics_ctx --enable-monolithic --enable-shared --with-opengl --enable-threads --disable-debug_flag --disable-precomp-headers --disable-debug --with-libpng=builtin --with-regex=builtin --with-libjpeg=builtin --with-libtiff=builtin --with-expat=builtin"
    export OPENGL_LIBS="$(pkg-config gl --libs)"
    export LDFLAGS="$(pkg-config gl glew glu --libs) $LDFLAGS"
    export URUSSTUDIOPLAT="--with-platform=gtk2 --disable-debug --disable-pch --disable-fortran"
  fi
fi

export URUSBASEDIR=/system/urus
export URUSINSTALLDIR=$URUSBASEDIR/$XURUSSDK
export URUSSTDTOPDIR=$(pwd)

if [ "x$ENABLEGIT" != "x" ] ; then
    if [ "x$USERCIURUS" != "x" ] ; then
        git config --global user.email $(printf "%s" $(git --no-pager log -1 -s --format="%ae"))
        git config --global user.name "$(git --no-pager log -1 -s --format='%an')"
    else
        git config --global user.email $(printf "%s@%s" ${USER} $(uname -n))
        git config --global user.name ${USER}
    fi
fi

cd modules/wxWidgets
export WXURUSTOPDIR=$(pwd)

cd $URUSINSTALLDIR

if [ -e $URUSINSTALLDIR/.git ] ; then
  echo "git ok"
else
  if [ "x$ENABLEGIT" != "x" ] ; then
    echo "git init"
    git init $URUSINSTALLDIR
  fi
fi

echo $SECONDS > .empty
if [ "x$ENABLEGIT" != "x" ] ; then
  git add .
  git commit -m "added backup."
fi

cd $WXURUSTOPDIR
mkdir -p buildwx
cd buildwx

../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --prefix=${URUSINSTALLDIR} --enable-unicode --with-flavour=urus --enable-vendor=urus $WXURUSCONF
make -j6
make install

PUSHD=$(pwd)
cd $URUSINSTALLDIR
echo $SECONDS > .empty
if [ "x$ENABLEGIT" != "x" ] ; then
  git add .
  git commit -m "added wxWidgets urus."
fi
cd $PUSHD

export PATH=${URUSINSTALLDIR}/bin:$PATH

WXVERSION=$(wx-config --version)
WXTOOLKIT=$(wx-config --query-toolkit)
WXVERSIONFULL=""

do_git()
{
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
    WXVERSIONFULL=$(printf "wx-%s-%s" $WXVERSION $WXTOOLKIT)
    PUSHDGIT=$(pwd)
    if [ "x$MSYSTEM" = "x" ] ; then
        tar -cJf $URUSBASEDIR/toolchain/host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz *
        cd $URUSBASEDIR/toolchain/
        md5sum host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz > host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz.md5
    fi
    cd $PUSHDGIT
    git checkout -q master-wx || git checkout -q -b master-wx
    git reset --hard HEAD~3 2>/dev/null
    tar -cJf $URUSBASEDIR/toolchain/host-$($HOSTTARGET)-${WXVERSIONFULL}-urus.tar.xz *
    git checkout master
    git reset --hard
    cd $URUSBASEDIR/toolchain/
    md5sum host-$($HOSTTARGET)-${WXVERSIONFULL}-urus.tar.xz > host-$($HOSTTARGET)-${WXVERSIONFULL}-urus.tar.xz.md5
}

usps="
src/UrusStudio_wx31.usp;All
src/tools/cb_share_config/cb_share_config_wx31.usp;All
src/tools/CBLauncher/StartUrustudio_wx31.usp;All
src/tools/cbp2make/cbp2make_wx31.usp;All
src/plugins/contrib/wxContribItems/wxContribItems_wx31.usp;All
src/plugins/contrib/wxSmith/wxSmith_wx31.usp;All
src/plugins/contrib/wxSmithContribItems/wxSmithContribItems_wx31.usp;All
src/plugins/contrib/wxSmithAui/wxSmithAui_wx31.usp;Windows
src/plugins/contrib/BrowseTracker/BrowseTracker_wx31.usp;All
src/plugins/contrib/Cscope/Cscope_wx31.usp;All
src/plugins/contrib/EditorConfig/EditorConfig_wx31.usp;All
src/plugins/contrib/EditorTweaks/EditorTweaks_wx31.usp;All
src/plugins/contrib/envvars/envvars_wx31.usp;All
src/plugins/contrib/headerfixup/headerfixup_wx31.usp;All
src/plugins/contrib/HexEditor/HexEditor_wx31.usp;All
src/plugins/contrib/IncrementalSearch/IncrementalSearch_wx31.usp;All
src/plugins/contrib/lib_finder/lib_finder_wx31.usp;All
src/plugins/contrib/SmartIndent/SmartIndent_wx31.usp;All
src/plugins/contrib/symtab/symtab_wx31.usp;All
src/plugins/contrib/ThreadSearch/ThreadSearch_wx31.usp;All
src/plugins/contrib/ToolsPlus/ToolsPlus_wx31.usp;All
src/plugins/UrusStudioSettings/UrusStudioSettings_wx31.usp;win
"

rm -f $URUSSTDTOPDIR/buildci.log

pint_dots()
{
    printf "\n"
    for i in `seq $1 $max`
    do
        printf "*"
    done
    printf "\n"
}

build_usp()
{
    printf "Building UrusStudio MSW projects...\n"
    sleep 2

    cnt=0
    for usp in $usps
    do
        cnt=$((cnt+1))
        printf "%02d: %s\n" $cnt $(basename $(printf $usp | cut -d\; -f 1))
        sleep 2
        urusstudio --user-data-dir=appdata/msw/urusstudio/ --build $(printf $usp | cut -d\; -f 1) --target=$(printf $usp | cut -d\; -f 2) 1>>$URUSSTDTOPDIR/buildci.log
    done
}

copy_urusstudio_includes()
{
    cd $URUSSTDTOPDIR/src
    mkdir -p devel31/include/urusstudio/wxscintilla
    cp -rf include/* devel31/include/urusstudio/
    cp -rf sdk/wxscintilla/include devel31/include/urusstudio/wxscintilla
    cd plugins/contrib
    find wxContribItems -name '*.h' -exec cp --parents \{\} ../../devel31/include/urusstudio/ \;
    find wxSmith -name '*.h' -exec cp --parents \{\} ../../devel31/include/ \;
    cd $URUSSTDTOPDIR/src
}

#Only for Unix Like, on Windows we don't make it.
if [ "x$NO_BUILD_ALL" = "x" ] ; then
    if [ "x$MSYSTEM" = "x" ] ; then
        export ACLOCAL_FLAGS="-I `wx-config --prefix`/share/aclocal"

        cd ${URUSSTDTOPDIR}
        pint_dots 40
        ./bootstrap
        mkdir -p buildustd
        cd buildustd

        pint_dots 40
        ../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --with-contrib-plugins="Cscope,EditorConfig,EditorTweaks,envvars,headerfixup,libfinder,BrowseTracker,hexeditor,incsearch,smartindent,symtab,ThreadSearch,ToolsPlus,wxcontrib,wxsmith,wxsmithcontrib,wxsmithaui" --prefix=${URUSINSTALLDIR} $URUSSTUDIOPLAT
        make -j2
        make install

        PUSHD=$(pwd)
        cd $URUSINSTALLDIR
        mkdir -p $URUSBASEDIR/toolchain
        echo $SECONDS > .empty
        pint_dots 40
        if [ "x$ENABLEGIT" != "x" ] ; then
            do_git >> $URUSSTDTOPDIR/buildci.log
        fi
        pint_dots 40
        cd $PUSHD
        ../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --with-contrib-plugins="Cscope,EditorConfig,EditorTweaks,envvars,headerfixup,libfinder,BrowseTracker,hexeditor,incsearch,smartindent,symtab,ThreadSearch,ToolsPlus,wxcontrib,wxsmith,wxsmithcontrib,wxsmithaui" --prefix=${URUSINSTALLDIR} $URUSSTUDIOPLAT

        if [ "x$NO_URUSSTUDIO_MAKE_CMD" = "x" ] ; then
            make -j6
            make install
        fi
    else
        cd $URUSSTDTOPDIR
        pint_dots 40
        build_usp
        PUSHD=$(pwd)
        cd $URUSINSTALLDIR
        mkdir -p $URUSBASEDIR/toolchain
        echo $SECONDS > .empty
        pint_dots 40
        if [ "x$ENABLEGIT" != "x" ] ; then
            do_git >> $URUSSTDTOPDIR/buildci.log
        fi
        pint_dots 40
        cd $URUSSTDTOPDIR/src/
        ./update31
        cd $URUSSTDTOPDIR/src/output31
        pint_dots 40
        printf "Compressing Urus Studio dist...\n"
        tar -cJf $URUSBASEDIR/toolchain/host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz *
        cd $URUSBASEDIR/toolchain/
        md5sum host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz > host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz.md5
    fi
    copy_urusstudio_includes
    cd $URUSSTDTOPDIR
    pint_dots 40
    printf "Display logs...\n"
    touch $URUSSTDTOPDIR/buildci.log
    cat $URUSSTDTOPDIR/buildci.log
    pint_dots 40
fi

echo BUILD OK!
exit 0
