AM_CPPFLAGS = $(WX_CXXFLAGS) \
		-I$(srcdir)/include

wxcontribitemsdir=$(libdir)/urusstudio/wxContribItems

wxcontribitems_LTLIBRARIES = libwximagepanel.la

libwximagepanel_la_LDFLAGS = -version-info 0:1:0

libwximagepanel_la_LIBADD = $(WX_LIBS)

libwximagepanel_la_SOURCES = \
./src/wxImagePanel.cpp

sdkdir=$(includedir)/urusstudio/wxContribItems/wxImagePanel/include/wx

sdk_HEADERS = \
./include/wx/wxImagePanel.h

