#!/bin/sh

export URUSSTDTOPDIR=$(pwd)

#git submodule init
#git submodule update

cd modules/wxWidgets

export WXURUSTOPDIR=$(pwd)
mkdir -p buildwx
cd buildwx

../configure --with-gtk --prefix=${URUSSTDTOPDIR}/install --enable-unicode --with-flavour=urus --enable-vendor=urus --enable-monolithic
make -j2
make install

export PATH=${URUSSTDTOPDIR}/install/bin:$PATH
export ACLOCAL_FLAGS="-I `wx-config --prefix`/share/aclocal"

cd ${URUSSTDTOPDIR}
./bootstrap
mkdir -p buildustd
cd buildustd
../configure --with-contrib-plugins="AutoVersioning, BrowseTracker, Cccc, CppCheck, cbkoders, codesnippets,codestat, copystrings, Cscope, dragscroll, EditorConfig, EditorTweaks, envvars,FileManager, headerfixup, hexeditor, incsearch, keybinder, libfinder, MouseSap, ProjectOptionsManipulator, profiler, regex, ReopenEditor,smartindent,symtab, ThreadSearch, ToolsPlus, Valgrind, wxcontrib, wxsmith, wxsmithcontrib, wxsmithaui" --prefix=${URUSSTDTOPDIR}/install --with-platform=gtk
make -j2
make install

echo BUILD OK!
exit 0
