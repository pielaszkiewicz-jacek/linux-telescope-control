#!/bin/sh

echo ""
echo "\t-------------------------------------------------------------------"
echo ""
echo "\tJacek Pielaszkiewicz"
echo "\tInstall tlins binaries"
echo ""
echo "\t-------------------------------------------------------------------"

echo ""
echo "\tReload systemd configuration"
echo "\t-------------------------------------------"
systemctl daemon-reload

for service in `echo "tlins.service tlinsAstro.service tlins-system-service.service"`
do
        echo "\tstop service ${service}"
        systemctl stop ${service}
done

echo ""
echo "\tSystemd configuration"
echo "\t-------------------------------------------"
for file in `ls -1 install.pkg/systemd`
do
	echo "\tFile: ${file} into /lib/systemd/system/${file}"
	cp install.pkg/systemd/${file} /lib/systemd/system/
	ln -sf /lib/systemd/system/${file} /etc/systemd/system/multi-user.target.wants/${file}
done

echo ""
echo "\tCopy files"
echo "\t-------------------------------------------"
cp -v -r install.pkg/bin install.pkg/lib install.pkg/cfg /home/tlins/. | while read line
do
	echo "\t${line}"
done

echo ""
echo "\tCreate logs directory"
echo "\t-------------------------------------------"
mkdir -p /home/tlins/logs

echo ""
echo "\tReload systemd configuration"
echo "\t-------------------------------------------"
systemctl daemon-reload

echo ""

for service in tlins.service tlinsAstro.service tlins-system-service.service
do
	echo "\tStart service ${service}"
	systemctl start ${service}
done

echo ""
echo "\tDone"
echo ""
