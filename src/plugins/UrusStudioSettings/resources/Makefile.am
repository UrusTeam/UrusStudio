pkgdata_DATA = urusstudiosettings.zip
CLEANFILES = $(pkgdata_DATA)

EXTRA_DIST = urussettings_toolbar.xrc \
	urussettings_toolbar_16x16.xrc \
	manifest.xml \
	images/compile.png \
	images/16x16/compile.png

urusstudiosettings.zip: $(EXTRA_DIST)
	PWD=`pwd` cd $(srcdir) && zip $(PWD)/urusstudiosettings.zip manifest.xml *.xrc images/*.png images/16x16/*.png > /dev/null

