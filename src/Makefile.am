EXTRA_DIST=filter-templates.c

lib_LTLIBRARIES = librtfilter.la
include_HEADERS = filter.h

librtfilter_la_SOURCES = filter.h filter.c \
			  common-filters.h common-filters.c

librtfilter_la_LDFLAGS = $(AM_CFLAGS) -version-info $(CURRENT):$(REVISION):$(AGE) -release $(RELEASE) 
librtfilter_la_LIBADD = -lm
