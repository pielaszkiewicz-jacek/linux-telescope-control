#!/bin/bash

echo -e ""
echo -e "\tJacek Pielaszkiewicz"
echo -e "\tKrasnik 2021"
echo -e ""

if [ $# != 1 ]
then
    echo -e ""
    echo -e "\tIncorrect input parameter"
    echo -e "\tAbort"
    echo -e ""
    exit 1
fi

if [ ! -f /tmp/arm-create-bkp.sh -o ! -f /tmp/arm-pkg-install.sh -o ! -f ${1} ]
then
    echo -e ""
    echo -e "\tMisisng update files"
    echo -e "\tAbort"
    echo -e ""
    exit 1
fi

chmod 755 /tmp/arm-create-bkp.sh
chmod 755 /tmp/arm-pkg-install.sh

echo -e "\t-------------------------------------------"
echo -e "\t"
echo -e "\tStart updater"
echo -e ""

cd /tmp/

echo -e "\t-------------------------------------------"
echo -e "\t"
echo -e "\tMake backup"
echo -e ""

/tmp/arm-create-bkp.sh

if [ $? != "0" ]
then
    echo -e ""
    echo -e "\tError create backup"
    echo -e "\tAbort"
    echo -e ""
    exit 1
fi

echo -e "\t-------------------------------------------"
echo -e "\t"
echo -e "\tUpdate binary files, configuration, libraries and systemd configuration"
echo -e ""

/tmp/arm-pkg-install.sh ${1}
if [ $? != "0" ]
then
    echo -e ""
    echo -e "\tUpdate failed - restore backup"
    echo -e "\tAbort"
    echo -e ""
    exit 1
fi

echo -e ""
echo -e "\tDone"
echo -e ""

exit 0