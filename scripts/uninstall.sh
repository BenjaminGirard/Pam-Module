#!/bin/bash

if [ $# != 1 ]
then echo Usage: ./uninstall.sh arg1; exit 84
fi

if [ ! -e ./scripts/check.sh ] || [ ! -x ./scripts/check.sh ]
then echo Error: check.sh is absent uninstall become ambiguous; exit 84
fi

ret=`./scripts/check.sh`
err=`echo $?`

if [ $err -eq 1 ]
then echo PAM module is already uninstalled; exit 84
fi

make fclean
sudo rm -f /lib/x86_64-linux-gnu/security/$1
line=`grep pam_lib.so /etc/pam.d/common-session -n | sed 's/[^0-9]//g'`
sudo sed -i $line'd' /etc/pam.d/common-session
sudo chown root:root /etc/pam.d/login
