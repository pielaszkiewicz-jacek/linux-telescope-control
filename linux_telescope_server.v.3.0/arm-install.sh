#!/bin/bash

echo -e ""
echo -e "\tBuild "
echo -e "\t-----------------------------------"
echo -e ""

rm -f ./install/* 2> /dev/null
./arm | while read line
do
	echo -e "\t${line}"
done

if [ ${?} != 0 ]
then
    echo ""
	echo -e "\t!!!!!"
	echo -e "\tError build"
	exit 1
fi

BASE_DIR="./install"

if [ ${#} != 0 ]
then
	BASE_DIR="${1}"
fi

BASE_DIR="./install"

if [ ${#} != 0 ]
then
	BASE_DIR="${1}"
fi

DEST_DIR=${BASE_DIR}/pkg

echo -e ""
echo -e "\tCreate directories"
echo -e "\t-----------------------------------------------------"
for item in ${DEST_DIR}/bin/ ${DEST_DIR}/cfg/ ${DEST_DIR}/logs/ ${DEST_DIR}/lib/ ${DEST_DIR}/systemd/
do
	echo -e "\tDirectory: ${item}"
	mkdir -p ${item}
done

echo -e ""
echo -e "\tCopy files"
echo -e "\t-----------------------------------------------------"
#
# Executables
#
for file in tlins tlinsAstro tlins_system_service tlins_tests
do
	echo -e "\tFile: ${file}"
	cp ${file} ${DEST_DIR}/bin/. > /dev/null 2> /dev/null
done

echo -e ""

for file in configuration/configuration.xml configuration/configuration-astro.xml configuration/configuration-system-service.xml
do
	echo -e "\tFile: ${file}"
	cp ${file} ${DEST_DIR}/cfg > /dev/null 2> /dev/null
done

echo -e ""

for file in systemd/tlins.service systemd/tlinsAstro.service systemd/tlins-system-service.service
do
	echo -e "\tFile: ${file}"
	cp ${file} ${DEST_DIR}/systemd/. > /dev/null 2> /dev/null
done

echo -e ""
echo -e "\tCreate tar archive. "
echo -e "\t-----------------------------------------------------"

__DD__="`date +'%Y%m%d'`"
OUT_FILE_NAME="tlins-pkg-${__DD__}.sh"
OUT_FILE="${BASE_DIR}/${OUT_FILE_NAME}"
TEMP_DIR="./.pkg-${__DD__}"
SYSTEMD_DEST_DIR="/lib/systemd/system"
DEST_DIR="/home/tlins"
ARCHIVE_FILE="tlins-pkg-${__DD__}.base64"
ARCHIVE_FILE_DEST="tlins-pkg-${__DD__}.tar"

echo "#!/bin/bash"                                                                            > ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}

echo "START_DIR=\`pwd\`"                                                                     >> ${OUT_FILE}

echo "__DDS__=\"\`date +'%Y%m%d'\`\""                                                        >> ${OUT_FILE}
echo "TEMP_BKP_DIR=\"./.pkg-\${__DDS__}/bkp/pkg\""                                           >> ${OUT_FILE}

# echo "echo \"Create backup directories\""                                                    >> ${OUT_FILE}
# echo "echo ----------------------------------------------------------------"                 >> ${OUT_FILE}
# echo "mkdir -p \${TEMP_BKP_DIR}"                                                             >> ${OUT_FILE}
# echo "mkdir -p \${TEMP_BKP_DIR}/logs"                                                        >> ${OUT_FILE}
# echo "mkdir -p \${TEMP_BKP_DIR}/systemd"                                                     >> ${OUT_FILE}
# echo ""                                                                                      >> ${OUT_FILE}

# echo "echo \"Backup binaries and configs\""                                                  >> ${OUT_FILE}
# echo "echo ----------------------------------------------------------------"                 >> ${OUT_FILE}
# echo "cp -rv /home/tlins/bin \${TEMP_BKP_DIR}/."                                             >> ${OUT_FILE}
# echo "cp -rv /home/tlins/lib \${TEMP_BKP_DIR}/."                                             >> ${OUT_FILE}
# echo "cp -rv /home/tlins/cfg \${TEMP_BKP_DIR}/."                                             >> ${OUT_FILE}
# echo ""                                                                                      >> ${OUT_FILE}

# echo "echo \"Backup systemd configuration\""                                                 >> ${OUT_FILE}
# echo "echo ----------------------------------------------------------------"                 >> ${OUT_FILE}
# echo "for file in tlins.service tlinsAstro.service tlins-system-service.service"             >> ${OUT_FILE}
# echo "do"                                                                                    >> ${OUT_FILE}
# echo "    cp -rv /lib/systemd/system/\${file} \${TEMP_BKP_DIR}/systemd/."                    >> ${OUT_FILE}
# echo "done"                                                                                  >> ${OUT_FILE}
# echo ""                                                                                      >> ${OUT_FILE}

# echo "echo \"Create backup archive\""                                                        >> ${OUT_FILE}
# echo "echo ----------------------------------------------------------------"                 >> ${OUT_FILE}
# echo "tar -C \${TEMP_BKP_DIR}/.. -cvf \${TEMP_BKP_DIR}/../tlins-bkp-pkg-\${__DDS__}.tar pkg" >> ${OUT_FILE}
# echo "gzip \${TEMP_BKP_DIR}/../tlins-bkp-pkg-\${__DDS__}.tar"                                >> ${OUT_FILE}
# echo "mkdir -p /home/tlins/bkp/"                                                             >> ${OUT_FILE}
# echo "find \${START_DIR} -name \"tlins-bkp-pkg-.*\" -exec mv {} /home/tlins/bkp/. \;"        >> ${OUT_FILE}
# echo ""                                                                                      >> ${OUT_FILE}

echo "echo \"\""                                                                             >> ${OUT_FILE}
echo "echo \"Package binary\""                                                               >> ${OUT_FILE}
echo "echo ----------------------------------------------------------------"                 >> ${OUT_FILE}
echo "echo \"\""                                                                             >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}

echo "INSTALL_SCRIPT_NAME=\"\`pwd\`/\${0}\""                                                 >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}

echo "rm -rf ${TEMP_DIR} 2> /dev/null > /dev/null"                                           >> ${OUT_FILE}
echo "mkdir -p ${TEMP_DIR}"                                                                  >> ${OUT_FILE}
echo "mkdir -p ${DEST_DIR}"                                                                  >> ${OUT_FILE}
echo "mkdir -p ${SYSTEMD_DEST_DIR}"                                                          >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}

echo "cd ${TEMP_DIR}"                                                                        >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}

echo "cp  ../${ARCHIVE_FILE} ."                                                              >> ${OUT_FILE}
echo "cat ${ARCHIVE_FILE} | base64 -d | gzip -d -c | tar -xvf -"                             >> ${OUT_FILE}

echo ""                                                                                      >> ${OUT_FILE}
echo "# ----------------------------------------------------------------"                    >> ${OUT_FILE}
echo "for service in tlins.service tlinsAstro.service tlins-system-service.service"          >> ${OUT_FILE}
echo "do"                                                                                    >> ${OUT_FILE}
echo "    systemctl stop \${service}"                                                        >> ${OUT_FILE}
echo "done"                                                                                  >> ${OUT_FILE}

echo ""                                                                                      >> ${OUT_FILE}
echo "# ----------------------------------------------------------------"                    >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}

echo "for infile in pkg/bin/*"                                                               >> ${OUT_FILE}
echo "do"                                                                                    >> ${OUT_FILE}
echo "    file=\`basename \${infile}\`"                                                      >> ${OUT_FILE}
echo "    cp -v \${infile} ${DEST_DIR}/bin/."                                                >> ${OUT_FILE}
echo "done"                                                                                  >> ${OUT_FILE}

echo ""                                                                                      >> ${OUT_FILE}
echo "cp -rv pkg/lib       ${DEST_DIR}"                                                      >> ${OUT_FILE}
echo "cp -rv pkg/cfg       ${DEST_DIR}"                                                      >> ${OUT_FILE}
echo "cp -r  pkg/logs      ${DEST_DIR}"                                                      >> ${OUT_FILE}
echo "cp -rv pkg/systemd/* ${SYSTEMD_DEST_DIR}"                                              >> ${OUT_FILE}

echo ""                                                                                      >> ${OUT_FILE}
echo "# ----------------------------------------------------------------"                    >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}
echo "systemctl daemon-reload"                                                               >> ${OUT_FILE}

echo ""                                                                                      >> ${OUT_FILE}
echo "# ----------------------------------------------------------------"                    >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}
echo "for f in tlins.service tlinsAstro.service tlins-system-service.service"                >> ${OUT_FILE}
echo "do"                                                                                    >> ${OUT_FILE}
echo "    systemctl enable \${f}"                                                            >> ${OUT_FILE}
echo "    systemctl start  \${f}"                                                            >> ${OUT_FILE}
echo "done"                                                                                  >> ${OUT_FILE}

echo ""                                                                                      >> ${OUT_FILE}
echo "# ----------------------------------------------------------------"                    >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}
echo "cd \${START_DIR}"                                                                      >> ${OUT_FILE}
echo "rm -rf ${TEMP_DIR}"                                                                    >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}
echo "exit 0"                                                                                >> ${OUT_FILE}
echo ""                                                                                      >> ${OUT_FILE}

chmod 755 ${OUT_FILE}

cd ${BASE_DIR} 2> /dev/null > /dev/null
tar cf - pkg | gzip -c | base64 > ${ARCHIVE_FILE}
cd - 2> /dev/null > /dev/null

tar -cvf ${ARCHIVE_FILE_DEST} ${BASE_DIR}/${ARCHIVE_FILE} ${BASE_DIR}/${OUT_FILE_NAME} 2> /dev/null > /dev/null

echo -e ""
echo -e "\t--------------"
echo -e "\tDone"
echo -e "\t--------------"
echo -e ""



