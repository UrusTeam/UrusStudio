SUBDIRS = resources

AM_CPPFLAGS = $(WX_CXXFLAGS) \
		$(CB_SQUIRREL_CFLAGS) \
		-I$(top_srcdir)/src/include \
		-I$(top_srcdir)/src/sdk/wxpropgrid/include \
		-I$(top_srcdir)/src/sdk/wxscintilla/include \
		-I$(top_srcdir)/src/include/scripting/sqplus \
		-I$(top_srcdir)/src/plugins/urusstudiosettings

pluginlibdir = $(pkglibdir)/plugins

pluginlib_LTLIBRARIES = liburusstudiosettings.la

liburusstudiosettings_la_LDFLAGS = @MODULE_SHARED_LDFLAGS@ -version-info 0:1:0 -no-undefined -avoid-version

liburusstudiosettings_la_LIBADD = ../../sdk/libcodeblocks.la \
				$(WX_LIBS)

liburusstudiosettings_la_SOURCES = urusstudiosettings.cpp \
			FMainSettings.cpp

noinst_HEADERS = urusstudiosettings.h \
			FMainSettings.h

EXTRA_DIST = $(srcdir)/*.usp \
		wxsmith

