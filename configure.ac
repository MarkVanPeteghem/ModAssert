AC_INIT([ModAssert], [2.0.6], [support@q-mentum.com])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE
AC_PROG_RANLIB
AC_CONFIG_FILES([Makefile])
AC_CONFIG_SUBDIRS([include])
AC_PROG_CXX

AC_ARG_WITH(wx,
        AS_HELP_STRING([--with-wx], [use wxWidgets wxStrings to stream values instead of std::string (default is std::string)]),
     [case "${with_wx}" in
       yes) wx=true ;;
       no)  wx=false ;;
       *) AC_MSG_ERROR(bad value ${with_wx} for --with-wx) ;;
     esac],
     [wx=false])
AM_CONDITIONAL(WXWIDGETS, test x$wx = xtrue)
AC_OUTPUT
