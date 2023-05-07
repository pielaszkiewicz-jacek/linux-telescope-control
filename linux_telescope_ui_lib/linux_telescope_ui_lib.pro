#-------------------------------------------------
#
# Project created by QtCreator 2018-07-27T10:30:20
#
#-------------------------------------------------

QT += network xml widgets sql core

TARGET = linux_telescope_ui_lib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14

#	../current/generated/astro.grpc.pb.cc		\
#	../current/generated/astro.pb.cc			\
#	../current/generated/base.grpc.pb.cc		\
#	../current/generated/base.pb.cc				\
#	../current/generated/device.grpc.pb.cc		\
#	../current/generated/device.pb.cc


SOURCES += linux_telescope_ui_lib.cpp			\
    tlinsastrouibase.cpp						\
    tlinscommunicationthread.cpp				\
    tlinsconnection.cpp							\
    tlinsconfiguration.cpp						\
    tlinsjoystick.cpp \
    tlinsserverstatusinfo.cpp					\
    tlinsuiexception.cpp						\
    tlinsupdatestatemanager.cpp					\
    tlinskeyssortcut.cpp						\
    tlinspilotshortcutsdefinitioninterface.cpp	\
    sofa/src/a2af.c								\
    sofa/src/a2tf.c								\
    sofa/src/ab.c								\
    sofa/src/af2a.c								\
    sofa/src/anp.c								\
    sofa/src/anpm.c								\
    sofa/src/apcg13.c							\
    sofa/src/apcg.c								\
    sofa/src/apci13.c							\
    sofa/src/apci.c								\
    sofa/src/apco13.c							\
    sofa/src/apco.c								\
    sofa/src/apcs13.c							\
    sofa/src/apcs.c								\
    sofa/src/aper13.c							\
    sofa/src/aper.c								\
    sofa/src/apio13.c							\
    sofa/src/apio.c								\
    sofa/src/atci13.c							\
    sofa/src/atciq.c							\
    sofa/src/atciqn.c							\
    sofa/src/atciqz.c							\
    sofa/src/atco13.c							\
    sofa/src/atic13.c							\
    sofa/src/aticq.c							\
    sofa/src/aticqn.c							\
    sofa/src/atio13.c							\
    sofa/src/atioq.c							\
    sofa/src/atoc13.c							\
    sofa/src/atoi13.c							\
    sofa/src/atoiq.c							\
    sofa/src/bi00.c								\
    sofa/src/bp00.c								\
    sofa/src/bp06.c								\
    sofa/src/bpn2xy.c							\
    sofa/src/c2i00a.c							\
    sofa/src/c2i00b.c							\
    sofa/src/c2i06a.c							\
    sofa/src/c2ibpn.c							\
    sofa/src/c2ixy.c							\
    sofa/src/c2ixys.c							\
    sofa/src/c2s.c								\
    sofa/src/c2t00a.c							\
    sofa/src/c2t00b.c							\
    sofa/src/c2t06a.c							\
    sofa/src/c2tcio.c							\
    sofa/src/c2teqx.c							\
    sofa/src/c2tpe.c							\
    sofa/src/c2txy.c							\
    sofa/src/cal2jd.c							\
    sofa/src/cp.c								\
    sofa/src/cpv.c								\
    sofa/src/cr.c								\
    sofa/src/d2dtf.c							\
    sofa/src/d2tf.c								\
    sofa/src/dat.c								\
    sofa/src/dtdb.c								\
    sofa/src/dtf2d.c							\
    sofa/src/ee00a.c							\
    sofa/src/ee00b.c							\
    sofa/src/ee00.c								\
    sofa/src/ee06a.c							\
    sofa/src/eect00.c							\
    sofa/src/eform.c							\
    sofa/src/eo06a.c							\
    sofa/src/eors.c								\
    sofa/src/epb2jd.c							\
    sofa/src/epb.c								\
    sofa/src/epj2jd.c							\
    sofa/src/epj.c								\
    sofa/src/epv00.c							\
    sofa/src/eqeq94.c							\
    sofa/src/era00.c							\
    sofa/src/fad03.c							\
    sofa/src/fae03.c							\
    sofa/src/faf03.c							\
    sofa/src/faju03.c							\
    sofa/src/fal03.c							\
    sofa/src/falp03.c							\
    sofa/src/fama03.c							\
    sofa/src/fame03.c							\
    sofa/src/fane03.c							\
    sofa/src/faom03.c							\
    sofa/src/fapa03.c							\
    sofa/src/fasa03.c							\
    sofa/src/faur03.c							\
    sofa/src/fave03.c							\
    sofa/src/fk52h.c							\
    sofa/src/fk5hip.c							\
    sofa/src/fk5hz.c							\
    sofa/src/fw2m.c								\
    sofa/src/fw2xy.c							\
    sofa/src/g2icrs.c							\
    sofa/src/gc2gd.c							\
    sofa/src/gc2gde.c							\
    sofa/src/gd2gc.c							\
    sofa/src/gd2gce.c							\
    sofa/src/gmst00.c							\
    sofa/src/gmst06.c							\
    sofa/src/gmst82.c							\
    sofa/src/gst00a.c							\
    sofa/src/gst00b.c							\
    sofa/src/gst06a.c							\
    sofa/src/gst06.c							\
    sofa/src/gst94.c							\
    sofa/src/h2fk5.c							\
    sofa/src/hfk5z.c							\
    sofa/src/icrs2g.c							\
    sofa/src/ir.c								\
    sofa/src/jd2cal.c							\
    sofa/src/jdcalf.c							\
    sofa/src/ld.c								\
    sofa/src/ldn.c								\
    sofa/src/ldsun.c							\
    sofa/src/num00a.c							\
    sofa/src/num00b.c							\
    sofa/src/num06a.c							\
    sofa/src/numat.c							\
    sofa/src/nut00a.c							\
    sofa/src/nut00b.c							\
    sofa/src/nut06a.c							\
    sofa/src/nut80.c							\
    sofa/src/nutm80.c							\
    sofa/src/obl06.c							\
    sofa/src/obl80.c							\
    sofa/src/p06e.c								\
    sofa/src/p2pv.c								\
    sofa/src/p2s.c								\
    sofa/src/pap.c								\
    sofa/src/pas.c								\
    sofa/src/pb06.c								\
    sofa/src/pdp.c								\
    sofa/src/pfw06.c							\
    sofa/src/plan94.c							\
    sofa/src/pmat00.c							\
    sofa/src/pmat06.c							\
    sofa/src/pmat76.c							\
    sofa/src/pm.c								\
    sofa/src/pmp.c								\
    sofa/src/pmpx.c								\
    sofa/src/pmsafe.c							\
    sofa/src/pn00a.c							\
    sofa/src/pn00b.c							\
    sofa/src/pn00.c								\
    sofa/src/pn06a.c							\
    sofa/src/pn06.c								\
    sofa/src/pn.c								\
    sofa/src/pnm00a.c							\
    sofa/src/pnm00b.c							\
    sofa/src/pnm06a.c							\
    sofa/src/pnm80.c							\
    sofa/src/pom00.c							\
    sofa/src/ppp.c								\
    sofa/src/ppsp.c								\
    sofa/src/pr00.c								\
    sofa/src/prec76.c							\
    sofa/src/pv2p.c								\
    sofa/src/pv2s.c								\
    sofa/src/pvdpv.c							\
    sofa/src/pvm.c								\
    sofa/src/pvmpv.c							\
    sofa/src/pvppv.c							\
    sofa/src/pvstar.c							\
    sofa/src/pvtob.c							\
    sofa/src/pvu.c								\
    sofa/src/pvup.c								\
    sofa/src/pvxpv.c							\
    sofa/src/pxp.c								\
    sofa/src/refco.c							\
    sofa/src/rm2v.c								\
    sofa/src/rv2m.c								\
    sofa/src/rx.c								\
    sofa/src/rxp.c								\
    sofa/src/rxpv.c								\
    sofa/src/rxr.c								\
    sofa/src/ry.c								\
    sofa/src/rz.c								\
    sofa/src/s00a.c								\
    sofa/src/s00b.c								\
    sofa/src/s00.c								\
    sofa/src/s06a.c								\
    sofa/src/s06.c								\
    sofa/src/s2c.c								\
    sofa/src/s2p.c								\
    sofa/src/s2pv.c								\
    sofa/src/s2xpv.c							\
    sofa/src/sepp.c								\
    sofa/src/seps.c								\
    sofa/src/sp00.c								\
    sofa/src/starpm.c							\
    sofa/src/starpv.c							\
    sofa/src/sxp.c								\
    sofa/src/sxpv.c								\
    sofa/src/taitt.c							\
    sofa/src/taiut1.c							\
    sofa/src/taiutc.c							\
    sofa/src/tcbtdb.c							\
    sofa/src/tcgtt.c							\
    sofa/src/tdbtcb.c							\
    sofa/src/tdbtt.c							\
    sofa/src/tf2a.c								\
    sofa/src/tf2d.c								\
    sofa/src/tr.c								\
    sofa/src/trxp.c								\
    sofa/src/trxpv.c							\
    sofa/src/tttai.c							\
    sofa/src/tttcg.c							\
    sofa/src/tttdb.c							\
    sofa/src/ttut1.c							\
    sofa/src/ut1tai.c							\
    sofa/src/ut1tt.c							\
    sofa/src/ut1utc.c							\
    sofa/src/utctai.c							\
    sofa/src/utcut1.c							\
    sofa/src/xy06.c								\
    sofa/src/xys00a.c							\
    sofa/src/xys00b.c							\
    sofa/src/xys06a.c							\
    sofa/src/zp.c								\
    sofa/src/zpv.c								\
    sofa/src/zr.c								\
    tlinsastrobaseutils.cpp 					\
    tlinsuidatabasedefinition.cpp				\
    tlinsastrocatalogcollection.cpp				\
    tlinsastrocatalogitem.cpp					\
    tlinsastrocalibrationitem.cpp				\
    tlinsuiconfgiurationitem.cpp				\
    tlinsastroenginestate.cpp					\
    tlinsuidatabase.cpp							\
    tlinsiers.cpp								\
    tlinsplace.cpp								\
	tlinskeyboard.cpp


INCLUDEPATH += $$PWD/../external/release/include \
	../current/math/astro/include/	\
    ../current/client/include/					\
    ../current/include/parameters/				\
    ../current/include/							\
    ../current/include/sdevice/					\
    ../current/generated/						\
	../current/system_service/include/          \
    sofa/include/

HEADERS += linux_telescope_ui_lib.h				\
    csvparser.h \
    tlinsastrouibase.h							\
    tlinsjoystick.h \
    tlinskeyssortcut.h							\
    tlinscommunicationthread.h					\
    tlinspilotshortcutsdefinitioninterface.h	\
    tlinsconnection.h							\
    tlinsserverstatusinfo.h						\
    tlinsconfiguration.h						\
    tlinsuiexception.h							\
    tlinsupdatestatemanager.h					\
    tlinsastrobaseutils.h						\
    sofa/include/sofa.h							\
    sofa/include/sofam.h						\
    tlinsuidatabasedefinition.h					\
    tlinsastrocatalogcollection.h				\
    tlinsastrocatalogitem.h						\
    tlinsastrocalibrationitem.h					\
    tlinsuiconfgiurationitem.h					\
    tlinsastroenginestate.h						\
    tlinsuidatabase.h							\
    tlinsiers.h									\
    tlinsplace.h								\
    tlinskeyboard.h								\
    tlinspilotshortcutsdefinitionvalidmode.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
