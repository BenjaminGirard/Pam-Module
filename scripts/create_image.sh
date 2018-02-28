#!/bin/bash

if [ -e /lib/x86_64-linux-gnu/security/pam_lib.so ]
then echo pam_lib.so is installed && install=1
else echo pam_lib.so is not installed
fi

