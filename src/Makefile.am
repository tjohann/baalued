#
# Makefile.am
#

if ENABLE_DEBUG_INFO
AM_CFLAGS = ${my_CFLAGS} \
	${my_DEBUG_CFLAGS}
else
AM_CFLAGS = ${my_CFLAGS}
endif
AM_LDFLAGS = -Wl,--gc-sections -Wl,--as-needed

bin_PROGRAMS = baalued

baalued_SOURCES =             	\
	main.c    	        \
	gettext.h

baalued_CFLAGS = $(AM_CFLAGS)	\
	$(LIBCONFIG_CFLAGS)     \
	$(LIBBAALUE_CFLAGS)     \
	-DLOCALEDIR=\"$(localedir)\" -I$(srcdir)/../lib

baalued_LDFLAGS = $(AM_LDFLAGS)

baalued_LDADD =  		\
	$(LIBCONFIG_LIBS)   	\
	$(LIBBAALUE_LIBS)      	\
	$(LIBINTL) ../lib/libservice.a
