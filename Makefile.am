SUBDIRS = src

ACLOCAL_AMFLAGS = -I m4


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = urusstudio.pc

# Add some files needed only when making a bundle
if DARWIN
osxbundledir = $(pkgdatadir)/osx_bundle
dist_osxbundle_DATA = bundle.sh \
					urusstudio.plist

osxbundle_iconsdir = $(osxbundledir)/icons
dist_osxbundle_icons_DATA = $(top_srcdir)/src/src/resources/icons/*.icns
endif

EXTRA_DIST = bootstrap \
		urusstudio.spec \
		urusstudio.spec.fedora \
		urusstudio.plist \
		BUGS \
		BUILD \
		COMPILERS \
		$(srcdir)/update* \
		ChangeLog.xsl \
		urusstudio.appdata.xml \
		urusstudio-contrib.metainfo.xml \
		debian

clean-zipfiles:
	find . -name "*.zip" | xargs rm -f

clean-bin:
	find . -name "*.la" | xargs rm -f
	rm -f src/src/urusstudio

appdatadir = $(datarootdir)/appdata
dist_appdata_DATA = $(top_srcdir)/urusstudio.appdata.xml
