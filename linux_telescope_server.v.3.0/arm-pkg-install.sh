#!/bin/bash

PKG_FILE=${1}
SYSTEMD_DEST_DIR="/lib/systemd/system"
DEST_DIR="/home/tlins"
TEMP_DIR="/tmp/.pkg-`date +'%Y%m%d_%H%M%S'`"

if [ ! -f ${PKG_FILE} ]
then
    echo -e "\tNo proper file: ${PKG_FILE}"
    exit 1
fi

#
# Create working directory
#
echo -e ""
echo -e "\tMake destination directories"
echo -e "\t-----------------------------------------------------------"
rm -rf ${TEMP_DIR} 2> /dev/null > /dev/null
mkdir -p ${TEMP_DIR}
mkdir -p ${DEST_DIR}
mkdir -p ${DEST_DIR}/bin/
mkdir -p ${DEST_DIR}/logs/
mkdir -p ${DEST_DIR}/lib/
mkdir -p ${DEST_DIR}/cfg/
mkdir -p ${SYSTEMD_DEST_DIR}

echo -e ""
echo -e "\tMove archive file"
echo -e "\t-----------------------------------------------------------"
#
# Copy package file into temp dir
#
cp ${PKG_FILE} ${TEMP_DIR}/.

#
# Change dir
#
cd ${TEMP_DIR}/.

#
# Extract archive
#
echo -e ""
echo -e "\tExtract archive"
echo -e "\t-----------------------------------------------------------"
tar -xvf `basename ${PKG_FILE}` | while read line
do
    echo -e "\t${line}"
done

#
# Stop services
#
echo -e ""
echo -e "\Stop services"
echo -e "\t-----------------------------------------------------------"
for service in tlins.service tlinsAstro.service tlins-system-service.service
do
    systemctl stop ${service}
done

#
# copy files
#
echo -e ""
echo -e "\tCopy files"
echo -e "\t-----------------------------------------------------------"

for infile in pkg/bin/*
do
    file=`basename ${infile}`
    echo -e "\t'${infile}' -> '${DEST_DIR}/bin/${infile}'"
    rm -f ${DEST_DIR}/bin/${file} 2> /dev/null > /dev/null
    cp ${infile} ${DEST_DIR}/bin/.
done

echo -e ""
cp -rv pkg/lib ${DEST_DIR} | while read line
do
    echo -e "\t${line}"
done

echo -e ""
cp -rv pkg/cfg ${DEST_DIR} | while read line
do
    echo -e "\t${line}"
done

echo -e ""
cp -r pkg/logs ${DEST_DIR}

echo -e ""
cp -rv pkg/systemd/* ${SYSTEMD_DEST_DIR} | while read line
do
    echo -e "\t${line}"
done

#
# Reload
#
echo -e ""
echo -e "\tReload systemd configuration"
echo -e "\t-----------------------------------------------------------"
systemctl daemon-reload

for f in tlins.service tlinsAstro.service tlins-system-service.service
do
    systemctl enable ${f}
    systemctl start ${f}
done

echo -e ""
echo -e "\tCleanup"
echo -e "\t-----------------------------------------------------------"
rm -rf "${TEMP_DIR}"
rm -f "${PKG_FILE}"

exit 0