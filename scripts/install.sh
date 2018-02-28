#!/bin/bash

if [ $# != 1 ]
then echo Usage: ./install.sh arg1; exit 84
fi

if [ ! -e ./scripts/check.sh ] || [ ! -x ./scripts/check.sh ]
then echo Error: check.sh is absent install become ambiguous; exit 84
fi

ret=`./scripts/check.sh`
err=`echo $?`

if [ $err -eq 0 ]
then echo PAM module is already installed; exit 84
fi

make re
sudo cp $1 /lib/x86_64-linux-gnu/security/
sudo chown root:root /lib/x86_64-linux-gnu/security/$1
sudo chmod 755 /lib/x86_64-linux-gnu/security/$1
line=`grep pam_permit.so /etc/pam.d/common-session -n | grep required | sed 's/[^0-9]//g'`
sudo sed -i $line'i\session optional pam_lib.so' /etc/pam.d/common-session
lsmod | grep dm_crypt
sudo modprobe -v dm_crypt
sudo apt-get install cryptsetup
