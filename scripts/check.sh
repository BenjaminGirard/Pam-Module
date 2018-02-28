#!/bin/bash

install=0
conf=0

if [ -e /lib/x86_64-linux-gnu/security/pam_lib.so ]
then echo pam_lib.so is installed && install=1
else echo pam_lib.so is not installed
fi

var1=`grep pam_lib.so /etc/pam.d/common-session`
var2="session optional pam_lib.so"

if [ "$var1" == "$var2" ]
then echo pam_lib.so is configured && conf=1
else echo pam_lib.so is not configured
fi

if [ $install == 1 ] && [ $conf == 1 ]
then exit 0
else exit 1
fi
