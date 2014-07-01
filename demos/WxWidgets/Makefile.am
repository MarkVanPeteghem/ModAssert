## Process this file with automake to produce Makefile.in

# The debug flag is necessary to demonstrate the redirection of
# wx assertions to ModAssert, otherwise they would be compiled out.

noinst_PROGRAMS = wxdemo

wxdemo_SOURCES = DemoWxApp.cpp DemoWxDlg.cpp notext.cpp
LDADD = -lrichbool-wx  -lmodassert-wxgui -lmodassert-wx -lpthread
AM_CPPFLAGS = -DRICHBOOL_USE_WX `wx-config --cxxflags`
AM_CXXFLAGS = -O2 -ansi -Wshadow -Wwrite-strings
AM_LDFLAGS = `wx-config --libs`
