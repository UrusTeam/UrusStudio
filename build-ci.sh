#!/bin/sh

if [ "x$CROSS" != "x" ] ; then
    export CROSSTAIL="$CROSS-"
fi

if [ "x$CFLAGS" = "x" ] ; then
    export CFLAGS="-O2"
fi

if [ "x$CXXFLAGS" = "x" ] ; then
    export CXXFLAGS="-O2"
fi

export URUSBASEDIR=/system/urus
export URUSINSTALLDIR=$URUSBASEDIR/$XURUSSDK
export URUSSTDTOPDIR=$(pwd)

mkdir -p $URUSINSTALLDIR

# MSYSTEM is defined when cross-compilig with MinGW/MSYS
if [ "x$MSYSTEM" != "x" ] ; then
  echo Updating MinGW32/cross version.
  WXURUSBUILD=""
  WXURUSHOST="--host=$CROSS"
  WXURUSTARGET="--target=$CROSS"
  export HOSTTARGET="${CROSSTAIL}gcc -dumpmachine"
  export LIBS=" -lwindowscodecs"
  export LDFLAGS="-Wl,--gc-sections -Wl,--allow-multiple-definition"
  export CFLAGS="-Wno-unused-local-typedefs -ffunction-sections -fdata-sections $CFLAGS"
  export CXXFLAGS="-Wno-unused-local-typedefs -fpermissive -ffunction-sections -fdata-sections $CXXFLAGS"
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
    export CXXFLAGS="-Wno-unused-local-typedefs -Wno-narrowing -Wno-literal-suffix -fpermissive -DGTK_VERSION=2 -Wl,-rpath,/system/urus/lib:/system/urus/lib/urusstudio/wxContribItems $CXXFLAGS"
    export CFLAGS="-Wno-unused-local-typedefs -Wno-narrowing -Wl,-rpath,$URUSBASEDIR/lib:$URUSBASEDIR/lib/urusstudio/wxContribItems $CFLAGS"
    export WXURUSCONF="--with-gtk=2 --enable-cmdline --enable-graphics_ctx --enable-monolithic --enable-shared --with-opengl --enable-threads --disable-debug_flag --disable-precomp-headers --disable-debug --with-libpng=builtin --with-regex=builtin --with-libjpeg=builtin --with-libtiff=builtin --with-expat=builtin"
    export OPENGL_LIBS="$(pkg-config gl --libs)"
    export LDFLAGS="$(pkg-config gl glew glu --libs) $LDFLAGS"
    export URUSSTUDIOPLAT="--with-platform=gtk2 --disable-debug --disable-pch --disable-fortran"
  fi
fi

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

date > .empty

if [ "x$ENABLEGIT" != "x" ] ; then
    git add .
    git commit -m "added master backup."
    git checkout -q master
    git rm -r *
    git add .
    git commit -m "cleaned master branch."
fi

cd $WXURUSTOPDIR
mkdir -p buildwx
cd buildwx

../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --prefix=${URUSINSTALLDIR} --enable-unicode --with-flavour=urus --enable-vendor=urus $WXURUSCONF
make -j6
make install

export PATH=${URUSINSTALLDIR}/bin:$PATH

WXCONFIGURUS=$URUSINSTALLDIR/bin/wx-config

WXSELCONF=$($WXCONFIGURUS --selected-config)
WXRELEASE=$($WXCONFIGURUS --release)
WXVERSION=$($WXCONFIGURUS --version)
WXCHARTYPE=$($WXCONFIGURUS --query-chartype)
WXTOOLKIT=$($WXCONFIGURUS --query-toolkit)
ARCHOS=$(printf "%s-%s" $(uname -s) $(uname -m))
ARCHOS=$(echo $ARCHOS | tr A-Z a-z)
WXVERSIONFULL=$(printf "wx-%s-%s" $WXVERSION $WXTOOLKIT)
WXCONFIGFULL=$(printf "%s-%s-%s-urus" $WXTOOLKIT $WXCHARTYPE $WXRELEASE)

rename_dlls()
{
    libsdlls=$(find * -name '*.dll.a')

    for libdll in $libsdlls
    do
        echo $libdll | sed -r -e 's:(.dll)::;' | xargs -I {} mv -f $libdll {}
    done
}

PUSHD=$(pwd)

cd $URUSINSTALLDIR/lib
rename_dlls

cd $URUSINSTALLDIR
date > .empty

if [ "x$MSYSTEM" != "x" ] ; then
    mkdir -p $URUSINSTALLDIR/include/wx-${WXRELEASE}-urus/wx/msw/private
    cp -f $WXURUSTOPDIR/include/wx/msw/private/graphicsd2d.h $URUSINSTALLDIR/include/wx-${WXRELEASE}-urus/wx/msw/private/
    cp -f $WXURUSTOPDIR/include/wx/msw/private/comptr.h $URUSINSTALLDIR/include/wx-${WXRELEASE}-urus/wx/msw/private/
fi

if [ "x$ENABLEGIT" != "x" ] ; then
    git add .
    git commit -m "added wxWidgets urus."
    git checkout -q master-wx 2>/dev/null || git checkout -q -b master-wx
    git reset -q HEAD~1
    git clean -q -fdx
    git cherry-pick master~0 --strategy-option theirs
    git checkout -q master
fi
cd $PUSHD

sed_trim_xurussdk_path()
{
    if [ "x$XURUSSDK" != "x" ] ; then
        grep -rilI . -e "$XURUSSDK" | xargs -I {} sed -i -r -e "s:(/$XURUSSDK)::g;" {}
    fi
}

do_git_rm()
{
    git add .
    git commit -m "added urusstudio."
    git checkout -q master-urusstudio 2>/dev/null || git checkout -b master-urusstudio
    #git clean -fdx
    #git reset --hard
    git rm -rf *
    git commit -m "removed all."
    git cherry-pick master~0 --strategy-option theirs
    #git cherry-pick HEAD~1
    sed_trim_xurussdk_path
    date > .empty
    git add .
    git commit -m "urusstudio trimmed xurussdk tmp."
}

do_tar_urusstudio()
{
    PUSHDGIT=$(pwd)
    if [ "x$MSYSTEM" = "x" ] ; then
        tar -cJf $URUSBASEDIR/toolchain/host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz *
        cd $URUSBASEDIR/toolchain/
        md5sum host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz > host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz.md5
    fi
    cd $PUSHDGIT
}

do_git_tar_wx()
{
    git checkout -q master-wx 2>/dev/null || git checkout -q -b master-wx
    if [ $1 -gt 0 ] ; then
        git reset --hard HEAD~$1 2>/dev/null
    fi
    sed_trim_xurussdk_path
    cd $URUSINSTALLDIR/bin
    rm -f wx-config
    ln -s ../lib/wx/config/$WXCONFIGFULL wx-config
    cd $URUSINSTALLDIR
    date > .empty
    git add .
    git commit -m "wx trimmed xurussdk tmp."
    tar -cJf $URUSBASEDIR/toolchain/host-$($HOSTTARGET)-${WXVERSIONFULL}-urus.tar.xz *
    git checkout -q master
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
        sleep 1
        urusstudio --user-data-dir=appdata/msw/urusstudio/ --build $(printf $usp | cut -d\; -f 1) --target=$(printf $usp | cut -d\; -f 2) 1>>${URUSSTDTOPDIR}/buildci.log
    done
}

copy_urusstudio_includes()
{
    cd $URUSSTDTOPDIR/src
    mkdir -p devel31/include/urusstudio/wxscintilla
    mkdir -p devel31/include/wxsmith
    cp -rf include/* devel31/include/urusstudio/
    cp -rf sdk/wxscintilla/include devel31/include/urusstudio/wxscintilla
    cd plugins/contrib
    find wxContribItems -name '*.h' -exec cp --parents \{\} ../../devel31/include/urusstudio/ \;
    cd wxSmith
    find * -name '*.h' -exec cp --parents \{\} ../../../devel31/include/wxsmith \;
    cd $URUSSTDTOPDIR/src
}

#Only for Unix Like, on Windows we don't make it.
if [ "x$NO_BUILD_ALL" = "x" ] ; then
    if [ "x$MSYSTEM" = "x" ] ; then
        export ACLOCAL_FLAGS="-I `$WXCONFIGURUS --prefix`/share/aclocal"

        cd $URUSSTDTOPDIR
        pint_dots 40
        ./bootstrap
        mkdir -p buildustd
        cd buildustd

        pint_dots 40
        ../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --with-contrib-plugins="Cscope,EditorConfig,EditorTweaks,envvars,headerfixup,libfinder,BrowseTracker,hexeditor,incsearch,smartindent,symtab,ThreadSearch,ToolsPlus,wxcontrib,wxsmith,wxsmithcontrib,wxsmithaui" --prefix=${URUSINSTALLDIR} $URUSSTUDIOPLAT
        make -j6
        make -j6 install

        PUSHD=$(pwd)

        cd $URUSSTDTOPDIR/src/tools/cbp2make
        make -j6 -f cbp2make.cbp.mak.unix
        cp -f bin/Release/cbp2make $URUSINSTALLDIR/bin

        cd $URUSINSTALLDIR
        mkdir -p $URUSBASEDIR/toolchain
        date > .empty
        pint_dots 40
        if [ "x$ENABLEGIT" != "x" ] ; then
            do_git_rm >> $URUSSTDTOPDIR/buildci.log
            printf "Compressing Urus Studio dist...\n"
            do_tar_urusstudio >> $URUSSTDTOPDIR/buildci.log
            printf "Compressing wxUrus dist...\n"
            do_git_tar_wx 0 >> $URUSSTDTOPDIR/buildci.log
        fi
        pint_dots 40
        cd $PUSHD
        #../configure $WXURUSBUILD $WXURUSHOST $WXURUSTARGET --with-contrib-plugins="Cscope,EditorConfig,EditorTweaks,envvars,headerfixup,libfinder,BrowseTracker,hexeditor,incsearch,smartindent,symtab,ThreadSearch,ToolsPlus,wxcontrib,wxsmith,wxsmithcontrib,wxsmithaui" --prefix=${URUSINSTALLDIR} $URUSSTUDIOPLAT

        #if [ "x$NO_URUSSTUDIO_MAKE_CMD" = "x" ] ; then
            #make -j6
            #make install
        #fi
    else
        cd $URUSSTDTOPDIR
        pint_dots 40
        build_usp
        PUSHD=$(pwd)
        cd $URUSINSTALLDIR
        mkdir -p $URUSBASEDIR/toolchain
        date > .empty
        pint_dots 40
        if [ "x$ENABLEGIT" != "x" ] ; then
            #do_git_rm >> $URUSSTDTOPDIR/buildci.log
            printf "Compressing wxUrus dist...\n"
            do_git_tar_wx 0 >> $URUSSTDTOPDIR/buildci.log
        fi
        pint_dots 40
        cd $URUSSTDTOPDIR/src/
        ./update31
        cd $URUSSTDTOPDIR/src/output31
        pint_dots 40
        if [ "x$ENABLEGIT" != "x" ] ; then
            printf "Compressing Urus Studio dist...\n"
            tar -cJf $URUSBASEDIR/toolchain/host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz *
            cd $URUSBASEDIR/toolchain/
            md5sum host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz > host-$($HOSTTARGET)-${WXVERSIONFULL}-urusstudio.tar.xz.md5
        fi
        copy_urusstudio_includes
    fi
    cd $URUSSTDTOPDIR
    pint_dots 40
    printf "Display logs...\n"
    touch $URUSSTDTOPDIR/buildci.log
    cat $URUSSTDTOPDIR/buildci.log
    pint_dots 40
fi

echo BUILD OK!
exit 0
