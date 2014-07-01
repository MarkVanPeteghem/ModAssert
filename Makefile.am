## Process this file with automake to produce Makefile.in

SUBDIRS = . include

##########################################
# ModAssert library
##########################################
SOURCES = src/context.cpp src/handler.cpp src/parmlist.cpp src/strmlog.cpp src/ifsuccess.cpp src/threads.cpp src/levels.cpp src/info.cpp src/timeinfo.cpp src/filters.cpp src/categories.cpp src/logger.cpp src/infouser.cpp src/appinfo.cpp src/infostore.cpp src/use_bool.cpp src/terminate_message.cpp src/warning_message.cpp src/responder_switcher.cpp

# suppose the header files are not yet installed, so add the include directory:
AM_CPPFLAGS = -DMODASSERT_USE_PTHREADS -I./include

if WXWIDGETS

AM_CXXFLAGS = -O2 -ansi -Wall -W -Wshadow -Wwrite-strings
lib_LIBRARIES = libmodassert-wx.a
libmodassert_wx_a_SOURCES = $(SOURCES)
libmodassert_wx_a_CPPFLAGS = -DRICHBOOL_USE_WX -DMODASSERT_USE_PTHREADS -I./include `wx-config --cxxflags`

else

AM_CXXFLAGS = -O2 -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
lib_LIBRARIES = libmodassert.a
libmodassert_a_SOURCES = $(SOURCES)

endif



##########################################
# ModAssert console library
##########################################

CONSOLE_SOURCES = console/src/consoledisplayer.cpp console/src/consolehandler.cpp console/src/consoleterminate.cpp console/src/consolewarning.cpp


# suppose the header files are not yet installed, so add the include directory:

if WXWIDGETS

libmodassert_console_wx_a_CXXFLAGS = -O2 -ansi -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
lib_LIBRARIES += libmodassert-console-wx.a
libmodassert_console_wx_a_CPPFLAGS = -DRICHBOOL_USE_WX -I./include -Iconsole `wx-config --cxxflags`
libmodassert_console_wx_a_SOURCES = $(CONSOLE_SOURCES)

else

libmodassert_console_a_CPPFLAGS = -I./include -Iconsole
libmodassert_console_a_CXXFLAGS = -O2 -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings

lib_LIBRARIES += libmodassert-console.a
libmodassert_console_a_SOURCES = $(CONSOLE_SOURCES)

endif



##########################################
# ModAssertWxGui library
##########################################

if WXWIDGETS

lib_LIBRARIES += libmodassert-wxgui.a

libmodassert_wxgui_a_SOURCES = wxgui/wxdisplayer.cpp wxgui/wxdlg.cpp wxgui/wxthreadid.cpp wxgui/wxhandler.cpp wxgui/wxlog.cpp wxgui/wxprocessid.cpp wxgui/wxcurrentdirectory.cpp wxgui/wxfreememory.cpp wxgui/wxosversion.cpp wxgui/wxsyserror.cpp wxgui/wxwarningmessage.cpp wxgui/wxterminatemessage.cpp

# suppose the header files are not yet installed, so add the include directory:
libmodassert_wxgui_a_CPPFLAGS = -I./include -Iwxgui -DRICHBOOL_USE_WX `wx-config --cxxflags`
libmodassert_wxgui_a_CXXFLAGS = -O2

endif



##########################################
# tests
##########################################

MODASSERT_TESTS = test/main/test test/nomodassert/test

TESTS = $(MODASSERT_TESTS)

check_PROGRAMS = $(MODASSERT_TESTS)

frameworkSOURCES = test/common/main.cpp test/common/ModAssertTest.cpp

test_main_test_SOURCES = \
	test/main/TestAllowResponses.cpp \
	test/main/TestAssert.cpp \
	test/main/TestAssert1DefaultParam.cpp \
        test/main/TestAssert2DefaultParams.cpp \
	test/main/TestAssertDontReportFile.cpp \
        test/main/TestAssertInIf.cpp \
	test/main/TestAssertLevel1.cpp \
	test/main/TestAssertLevel3.cpp \
        test/main/TestAssertLogger.cpp \
	test/main/TestAssertOffCheckOff.cpp \
	test/main/TestAssertOffCheckOn.cpp \
        test/main/TestAssertOnCheckOff.cpp \
	test/main/TestAssertOnCheckOn.cpp \
	test/main/TestAssertReportFile.cpp \
        test/main/TestResponderSwitcher.cpp \
	test/main/TestCheck.cpp \
	test/main/TestCheck1DefaultParam.cpp \
        test/main/TestCheck2DefaultParams.cpp \
	test/main/TestCheckDontReportFile.cpp \
	test/main/TestCheckLevel1.cpp \
        test/main/TestCheckLevel3.cpp \
	test/main/TestCheckReportFile.cpp \
	test/main/TestCombinedTypes.cpp \
        test/main/TestContext.cpp \
	test/main/TestDefaultGroup.cpp \
	test/main/TestDisabled.cpp \
        test/main/TestEnabled.cpp \
	test/main/TestExpressions.cpp \
	test/main/TestFilters.cpp \
        test/main/TestGetLevel.cpp \
	test/main/TestGroups.cpp \
	test/main/TestHook.cpp \
        test/main/TestIfSuccess.cpp \
	test/main/TestIgnore.cpp \
	test/main/TestLevelToString.cpp \
        test/main/TestLoggerInfo.cpp \
	test/main/TestOptionalAction.cpp \
	test/main/TestOutput.cpp \
        test/main/TestSetOptionalAction.cpp \
	test/main/TestSideEffects.cpp \
	test/main/TestStreamLogger.cpp \
        test/main/TestThreadSafety.cpp \
	test/main/TestNoText.cpp \
	test/main/TestLoggerId.cpp \
        test/main/TestSetOptionalLogger.cpp \
	test/main/TestDefaultOptionalAction.cpp \
        test/main/TestAssertD.cpp \
	test/main/TestWxAssert.cpp \
	test/main/TestVerifyV.cpp \
        test/main/TestAssertLevel3Check.cpp \
	test/main/TestCheckLevel3Assert.cpp \
        test/main/TestParamListWithCommas.cpp \
	test/main/TestUseBool.cpp \
	test/main/TestVersion.cpp \
        $(frameworkSOURCES)


if WXWIDGETS

# We need the --debug flag to test whether wx assertions macros can be rerouted to ModAssert.
# In release mode wx assertions macros are disabled.
# Make sure you have the debug version of WxWidgets, otherwise you get compile errors. 

test_main_test_CXXFLAGS = -O2 -ansi -Wshadow -Wwrite-strings
test_main_test_LDADD = -lrichbool-wx -lmodassert-console-wx -lmodassert-wx
test_main_test_LDFLAGS = `wx-config --libs --debug`
test_main_test_CPPFLAGS = -Itest/common -DRICHBOOL_USE_WX -DMODASSERT_USE_PTHREADS -DTESTS_RUN_IN_TOPDIR `wx-config --cxxflags --debug`

else

test_main_test_CXXFLAGS = -O2 -ansi -pedantic -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
test_main_test_LDADD = -lrichbool -lmodassert -lmodassert-console -lpthread
test_main_test_CPPFLAGS = -Itest/common -DMODASSERT_USE_PTHREADS -DTESTS_RUN_IN_TOPDIR

endif



# dont link with the modassert and richbooleans library
# because we test if this is possible if MODASSERT_DONT_REPORT is defined
if WXWIDGETS
test_nomodassert_test_CPPFLAGS = -Itest/common -DMOD_ASSERT_DONT_REPORT -DRICHBOOL_USE_WX `wx-config --cxxflags`
else
test_nomodassert_test_CPPFLAGS = -Itest/common -DMOD_ASSERT_DONT_REPORT
endif

test_nomodassert_test_SOURCES = test/nomodassert/TestNoModAssert.cpp
