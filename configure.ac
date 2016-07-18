# configure.ac

AC_INIT([baalued], [trunk], [thorsten.johannvorderbrueggen@t-online.de])
AC_COPYRIGHT([Copyright 2016, Thorsten Johannvorderbrueggen])

AC_CONFIG_AUX_DIR([build-aux/autoconf])
AC_CONFIG_MACRO_DIR([build-aux/m4])
AM_CONFIG_HEADER(config.h)

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])

AM_GNU_GETTEXT_VERSION([0.19.8])
AM_GNU_GETTEXT([external])

AC_PROG_CC

CFLAGS="${CFLAGS} -std=gnu11 -O2 -Wall -Wextra -pedantic -Wstrict-overflow -fno-strict-aliasing"

AM_INIT_AUTOMAKE([-Wall -Werror dist-bzip2])

# -> ./configure --enable-silent-rules to get quite build behaviour
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([no])])

# ------

# checks for programs.
PKG_PROG_PKG_CONFIG

# Checks for libraries.
PKG_CHECK_MODULES([LIBBAALUE], [libbaalue])

AC_CHECK_LIB([pthread], [pthread_create], [], [AC_MSG_ERROR([** Could not find libpthread **])])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.

AC_OUTPUT

AC_MSG_RESULT([
        $PACKAGE $VERSION
        ========

        prefix:                 ${prefix}
        sysconfdir:             ${sysconfdir}
        libdir:                 ${libdir}
        includedir:             ${includedir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
])
