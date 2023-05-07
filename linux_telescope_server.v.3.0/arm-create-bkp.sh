#!/bin/bash

DEST_DIR="/tmp/tlins_bkp/pkg"


echo -e ""
echo -e "\tMake destination directories"
echo -e "\t-----------------------------------------------------------"
rm -rf ${DEST_DIR}
mkdir -p ${DEST_DIR}
mkdir -p ${DEST_DIR}/logs
mkdir -p ${DEST_DIR}/systemd

echo -e ""
echo -e "\Copy files"
echo -e "\t-----------------------------------------------------------"
cp -rv /home/tlins/bin ${DEST_DIR}/.
cp -rv /home/tlins/lib ${DEST_DIR}/.
cp -rv /home/tlins/cfg ${DEST_DIR}/.

for file in tlins.service tlinsAstro.service tlins-system-service.service
do
    cp -rv /lib/systemd/system/${file} ${DEST_DIR}/systemd/.
done

echo -e ""
echo -e "\Make archive"
echo -e "\t-----------------------------------------------------------"

tar -C ${DEST_DIR}/.. -cvf ${DEST_DIR}/../tlins-pkg.tar pkg | while read line
do
    echo -e "\t${line}"
done

return 0