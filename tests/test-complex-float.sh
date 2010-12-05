#!/bin/sh

LOGFILE=testcf.log

if { 
    cmpwmatlab* -d 0 -p 2 -c 15 \
 && cmpwmatlab* -d 0 -p 2 -c 16 \
 && cmpwmatlab* -d 2 -p 0 -c 16 \
 && cmpwmatlab* -d 2 -p 0 -c 15 \
 && cmpwmatlab* -d 2 -p 2 -c 16 \
 && cmpwmatlab* -d 2 -p 2 -c 15
} > $LOGFILE
then
	rm $LOGFILE
	exit 0
else
	exit 1
fi
