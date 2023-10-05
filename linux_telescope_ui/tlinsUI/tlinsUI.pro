#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T04:28:21
#
#-------------------------------------------------

#CONFIG   += qxt

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = tlinsUI
TEMPLATE = app

DEFINES += __DEBUG__

SOURCES += main.cpp				\
    tlinsdatetimewidget.cpp \
	tlinsinfowidget.cpp \
    tlinslimitsmanagment.cpp \
    tlinssettingswidget.cpp \
    tlinstoolbarbutton.cpp \
    tlinstoolsbasewidget.cpp \
    tlinsuiastrodatabasemanagementwidget.cpp \
    tlinsuicalibrationwidget.cpp \
    tlinsuimainwindow.cpp			\
    tlinswapplayastroconfigurationwidget.cpp \
    tlinswcoordinatehourangle.cpp		\
    tlinswcoordinatedeclination.cpp		\
    tlinswcoordinatedegris.cpp			\
    tlinswastroengineconfiguration.cpp		\
    tlinswenvironmentwidget.cpp \
    tlinswguidercorrections.cpp \
    tlinswhardwerconfiguration.cpp		\
    tlinsastroobjectsviewmodel.cpp		\
    tlinsuiastrodatabasemanagement.cpp		\
    tlinswastrodatabaseobject.cpp		\
    tlinswconstelation.cpp			\
    tlinswastroobjecttype.cpp			\
    tlinswastrocatalog.cpp			\
    tlinswmessagebox.cpp \
    tlinswobjectname.cpp			\
    tlinswastrodatabasesearch3.cpp		\
    tlinswcatalogobjecttype.cpp			\
    tlinsuistrutils.cpp				\
    tlinswdecimalvalue.cpp			\
    tlinsuistylesmanager.cpp			\
    tlinswdatabasesearchmain.cpp		\
    tlinseditdatabaseobject.cpp			\
    tlinscalibrationitemmodel.cpp		\
    tlinsastrosearchwindow.cpp			\
    tlinspilotwindow.cpp			\
    tlinsastroobjectcoordinate.cpp		\
    tlinsuiutils.cpp				\
    tlinsuipolit4.cpp				\
    tlinsuimainform.cpp				\
    tlinswpilothorisintalverticalsteps.cpp \
	tlinswpilothorisontalverticalkeys.cpp \
    tlinswpilottrackingstart.cpp \
    tlinswpilottrackingstop.cpp \
    tlinswrampsettings.cpp			\
    tlinssettingswindow.cpp			\
    tlinswsettingsrampparameters.cpp		\
    tlinswsettingsconnection.cpp		\
    tlinswsettingsdatabase.cpp			\
    tlinswsettingsupdateinterface.cpp		\
    tlinsdatabase.cpp				\
    tlinsstatusicons.cpp			\
    tlinsvalueabstract.cpp			\
    tlinswtimedateierssettings.cpp		\
    tlinsiersmodel.cpp				\
    tlinsierswindow.cpp				\
    tlinswobservationplace.cpp			\
    tlinsobservationplacenodel.cpp		\
    tlinsobservationsplaceswindow.cpp		\
    tlinswenvironment.cpp			\
    tlinswenvironmentwindow.cpp			\
    tlinsenvironment.cpp			\
    tlinswapplayastroconfiguration.cpp		\
    tlinswapplayastroconfigurationwindow.cpp	\
    tlinswobservationerror.cpp			\
    tlinswobservationerrorsettings.cpp		\
    tlinswobservationerrorswindow.cpp		\
    tlinswcalibrationsettings.cpp		\
    tlinswpilotsettings.cpp			\
    tlinswmanageenginestate.cpp			\
    tlinswindowsenginestate.cpp			\
    tlinswtarget.cpp				\
    tlinstarget.cpp				\
    tlinswindowtarget.cpp			\
    tlinswdatetime.cpp				\
    tlinsdatetimewindow.cpp			\
    tlinswpilotshortcutsdefinitions.cpp		\
    tlinspilotshortcutsdefinitionswindow.cpp	\
    tlinswpilothorisintalverticalincrement.cpp	\
    tlinswpilothvdelta.cpp 			\
    tlinswpilothvspeeddelta.cpp 		\
    tlinswpilotradcdelta.cpp 			\
    tlinswpilotradcspeeddelta.cpp 		\
    tlinswpilotradcincrement.cpp 		\
    tlinswpilotstartresetcalibration.cpp 	\
    tlinswpilotsetreferenceobject.cpp 		\
    tlinswpilotsetvelocitymeasurment.cpp 	\
    tlinswpilotclosevelocitymeasurment.cpp 	\
	tlinswpilotclosecalibration.cpp \
	csvparser.c \
	tlinswtrackingcontrol.cpp

HEADERS  += tlinsuimainwindow.h			\
    tlinsdatetimewidget.h \
    tlinsinfowidget.h \
    tlinslimitsmanagment.h \
    tlinssettingswidget.h \
    tlinstoolbarbutton.h \
    tlinstoolsbasewidget.h \
    tlinsuiastrodatabasemanagementwidget.h \
    tlinsuicalibrationwidget.h \
    tlinswapplayastroconfigurationwidget.h \
    tlinswcoordinatehourangle.h			\
    tlinswcoordinatedeclination.h		\
    tlinswcoordinatedegris.h			\
    tlinswastroengineconfiguration.h		\
    tlinswenvironmentwidget.h \
    tlinswguidercorrections.h \
    tlinswhardwerconfiguration.h		\
    tlinsastroobjectsviewmodel.h		\
    tlinsuiastrodatabasemanagement.h		\
    tlinswastrodatabaseobject.h			\
    tlinswconstelation.h			\
    tlinswastroobjecttype.h			\
    tlinswastrocatalog.h			\
    tlinswmessagebox.h \
    tlinswobjectname.h				\
    tlinswastrodatabasesearch3.h		\
    tlinswcatalogobjecttype.h			\
    tlinsuistrutils.h				\
    tlinswdecimalvalue.h			\
    tlinsuistylesmanager.h			\
    tlinswdatabasesearchmain.h			\
    tlinseditdatabaseobject.h			\
    tlinscalibrationitemmodel.h			\
    tlinsastrosearchwindow.h			\
    tlinspilotwindow.h				\
    tlinsastroobjectcoordinate.h		\
    tlinsuiutils.h				\
    tlinsuipolit4.h				\
    tlinsuimainform.h				\
    tlinswpilothorisintalverticalsteps.h \
    tlinswpilothorisontalverticalkeys.h \
    tlinswpilottrackingstart.h \
    tlinswpilottrackingstop.h \
    tlinswrampsettings.h			\
    tlinssettingswindow.h			\
    tlinswsettingsrampparameters.h		\
    tlinswsettingsconnection.h			\
    tlinswsettingsdatabase.h			\
    tlinswsettingsupdateinterface.h		\
    tlinsdatabase.h				\
    tlinsstatusicons.h				\
    tlinsvalueabstract.h			\
    tlinswtimedateierssettings.h		\
    tlinsiersmodel.h				\
    logevent.hpp				\
    tlinsierswindow.h				\
    tlinswobservationplace.h			\
    tlinsobservationplacenodel.h		\
    tlinsobservationsplaceswindow.h		\
    tlinswenvironment.h				\
    tlinswenvironmentwindow.h			\
    tlinsenvironment.h				\
    tlinswapplayastroconfiguration.h		\
    tlinswapplayastroconfigurationwindow.h	\
    tlinswobservationerror.h			\
    tlinswobservationerrorsettings.h		\
    tlinswobservationerrorswindow.h		\
    tlinswcalibrationsettings.h			\
    tlinswpilotsettings.h			\
    tlinswmanageenginestate.h			\
    tlinswindowsenginestate.h			\
    tlinswtarget.h				\
    tlinstarget.h				\
    tlinswindowtarget.h				\
    tlinswdatetime.h				\
    tlinsdatetimewindow.h			\
    tlinswpilotshortcutsdefinitions.h		\
    tlinspilotshortcutsdefinitionswindow.h	\
    tlinswpilothorisintalverticalincrement.h 	\
    tlinswpilothvdelta.h 			\
    tlinswpilothvspeeddelta.h 			\
    tlinswpilotradcdelta.h 			\
    tlinswpilotradcspeeddelta.h 		\
    tlinswpilotradcincrement.h 			\
    tlinswpilotstartresetcalibration.h 		\
    tlinswpilotsetreferenceobject.h 		\
    tlinswpilotsetvelocitymeasurment.h 		\
    tlinswpilotclosevelocitymeasurment.h 	\
    tlinswpilotclosecalibration.h \
    tlinswtrackingcontrol.h


FORMS    += tlinsuimainwindow.ui		\
    tlinsdatetimewidget.ui \
    tlinsinfowidget.ui \
    tlinslimitsmanagment.ui \
    tlinssettingswidget.ui \
    tlinstoolbarbutton.ui \
    tlinstoolsbasewidget.ui \
    tlinsuiastrodatabasemanagementwidget.ui \
    tlinsuicalibrationwidget.ui \
    tlinswapplayastroconfigurationwidget.ui \
    tlinswcoordinatehourangle.ui		\
    tlinswcoordinatedeclination.ui		\
    tlinswcoordinatedegris.ui			\
    tlinswastroengineconfiguration.ui		\
    tlinswenvironmentwidget.ui \
    tlinswguidercorrections.ui \
    tlinswhardwerconfiguration.ui		\
    tlinsuiastrodatabasemanagement.ui		\
    tlinswastrodatabaseobject.ui		\
    tlinswconstelation.ui			\
    tlinswastroobjecttype.ui			\
    tlinswastrocatalog.ui			\
    tlinswobjectname.ui				\
    tlinswastrodatabasesearch3.ui		\
    tlinswcatalogobjecttype.ui			\
    tlinswdecimalvalue.ui			\
    tlinswdatabasesearchmain.ui			\
    tlinseditdatabaseobject.ui			\
    tlinsastrosearchwindow.ui			\
    tlinsmainbuttons.ui				\
    tlinspilotwindow.ui				\
    tlinsastroobjectcoordinate.ui		\
    tlinsuipolit4.ui				\
    tlinsuimainform.ui				\
    tlinswpilothorisintalverticalsteps.ui \
    tlinswpilothorisontalverticalkeys.ui \
    tlinswpilottrackingstart.ui \
    tlinswpilottrackingstop.ui \
    tlinswrampsettings.ui			\
    tlinssettingswindow.ui			\
    tlinswsettingsrampparameters.ui		\
    tlinswsettingsconnection.ui			\
    tlinswsettingsdatabase.ui			\
    tlinsstatusicons.ui				\
    tlinswtimedateierssettings.ui		\
    tlinsierswindow.ui				\
    tlinswobservationplace.ui			\
    tlinsobservationsplaceswindow.ui		\
    tlinsastrosearchwindow_kopia.ui		\
    tlinswenvironment.ui			\
    tlinswenvironmentwindow.ui			\
    tlinswapplayastroconfiguration.ui		\
    tlinswapplayastroconfigurationwindow.ui	\
    tlinswobservationerror.ui			\
    tlinswobservationerrorsettings.ui		\
    tlinswobservationerrorswindow.ui		\
    tlinswcalibrationsettings.ui		\
    tlinswpilotsettings.ui			\
    tlinswmanageenginestate.ui			\
    tlinswindowsenginestate.ui			\
    tlinswtarget.ui				\
    tlinswindowtarget.ui			\
    tlinswdatetime.ui				\
    tlinsdatetimewindow.ui			\
    tlinswpilotshortcutsdefinitions.ui		\
    tlinspilotshortcutsdefinitionswindow.ui	\
    tlinswpilothorisintalverticalincrement.ui 	\
    tlinswpilothvdelta.ui 			\
    tlinswpilothvspeeddelta.ui 			\
    tlinswpilotradcdelta.ui 			\
    tlinswpilotradcspeeddelta.ui 		\
    tlinswpilotradcincrement.ui 		\
    tlinswpilotstartresetcalibration.ui 	\
    tlinswpilotsetreferenceobject.ui 		\
    tlinswpilotsetvelocitymeasurment.ui 	\
    tlinswpilotclosevelocitymeasurment.ui 	\
    tlinswpilotclosecalibration.ui \
    tlinswtrackingcontrol.ui

RESOURCES +=					\
    resource.qrc

DISTFILES += \
    icons/settings-black.svg

unix|win32: LIBS += -L$$PWD/../../build-linux_telescope_ui_lib-Debug/
unix|win32: LIBS += -L$$PWD/../../build-linux_telescope_pilot_lib-Debug/
unix|win32: LIBS += -L$$PWD/../../current/x86/

unix|win32: LIBS += -Wl,--whole-archive -llinux_telescope_pilot_lib -Wl,--no-whole-archive
unix|win32: LIBS += -ltlins_system_service_client
unix|win32: LIBS += -llinux_telescope_ui_lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../current/release/ -ltlins_client -D__DEBUG__
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../current/debug/ -ltlins_client -D__DEBUG__
LIBS += -D__DEBUG__ -L$$PWD/../../current/x86 -ltlins_client -ltlins_loger -ltlins_rpc -ltlins_attitude
LIBS += -L$$PWD/../../external/release.x86/lib \
    -lssl \
    -lcrypto \
    -laddress_sorting \
    -lcares \
    -lgpr \
    -lgrpc++ \
    -lgrpc++_alts \
    -lgrpc_authorization_provider \
    -lgrpc++_error_details \
    -lgrpc_plugin_support \
    -lgrpcpp_channelz \
    -lgrpc++_reflection \
    -lgrpc++_unsecure \
    -lgrpc_unsecure \
    -lre2  \
    -lupb \
    -lz \
    -lgrpc
LIBS += -L$$PWD/../../external/release.x86/lib64 \
    -labsl_symbolize \
    -labsl_flags_reflection \
    -labsl_cordz_info \
    -labsl_base \
    -labsl_time \
    -labsl_int128 \
    -labsl_bad_variant_access \
    -labsl_bad_optional_access \
    -labsl_debugging_internal \
    -lprotobuf \
    -lz \
    -lssl \
    -lcrypto \
    -lutf8_validity \
    -laddress_sorting \
    -lcares \
    -lupb \
    -lgpr \
    -labsl_stacktrace \
    -labsl_base \
    -labsl_civil_time \
    -labsl_cord \
    -labsl_cord_internal \
    -labsl_cordz_functions \
    -labsl_cordz_sample_token \
    -labsl_crc_cord_state \
    -labsl_crc_cpu_detect \
    -labsl_exponential_biased \
    -labsl_failure_signal_handler \
    -labsl_flags \
    -labsl_flags_commandlineflag \
    -labsl_flags_config \
    -labsl_flags_internal \
    -labsl_flags_marshalling \
    -labsl_flags_reflection \
    -labsl_flags_usage \
    -labsl_flags_usage_internal \
    -labsl_graphcycles_internal \
    -labsl_hash \
    -labsl_hashtablez_sampler \
    -labsl_leak_check \
    -labsl_log_entry \
    -labsl_log_flags \
    -labsl_log_initialize \
    -labsl_log_internal_check_op \
    -labsl_log_internal_conditions \
    -labsl_log_internal_message \
    -labsl_log_internal_nullguard \
    -labsl_low_level_hash \
    -labsl_malloc_internal \
    -labsl_periodic_sampler \
    -labsl_random_distributions \
    -labsl_random_internal_distribution_test_util \
    -labsl_random_internal_pool_urbg \
    -labsl_random_internal_randen \
    -labsl_random_internal_randen_hwaes \
    -labsl_random_internal_randen_hwaes_impl \
    -labsl_random_internal_randen_slow \
    -labsl_random_internal_seed_material \
    -labsl_random_seed_gen_exception \
    -labsl_random_seed_sequences \
    -labsl_raw_hash_set \
    -labsl_raw_logging_internal \
    -labsl_scoped_set_env \
    -labsl_spinlock_wait \
    -labsl_stacktrace \
    -labsl_status \
    -labsl_statusor \
    -labsl_strerror \
    -labsl_str_format_internal \
    -labsl_strings \
    -labsl_strings_internal \
    -labsl_synchronization \
    -labsl_throw_delegate \
    -labsl_time \
    -labsl_time_zone \
    -labsl_flags_reflection \
    -labsl_flags_parse \
    -labsl_flags_config \
    -labsl_malloc_internal \
    -labsl_stacktrace \
    -labsl_log_internal_message \
    -labsl_graphcycles_internal \
    -labsl_flags_commandlineflag \
    -labsl_flags_internal \
    -labsl_crc_cord_state \
    -labsl_base \
    -labsl_cordz_info \
    -labsl_cordz_handle \
    -labsl_crc32c \
    -labsl_crc_internal \
    -labsl_flags_program_name \
    -labsl_log_internal_globals \
    -labsl_city \
    -labsl_int128 \
    -labsl_flags_commandlineflag_internal \
    -labsl_random_internal_platform \
    -labsl_symbolize \
    -labsl_debugging_internal \
    -labsl_flags_private_handle_accessor \
    -labsl_demangle_internal \
    -labsl_log_internal_proto \
    -labsl_log_globals \
    -labsl_log_internal_log_sink_set \
    -labsl_examine_stack \
    -labsl_log_internal_format \
    -labsl_log_sink \
    -fPIE


#-lgrpc++_unsecure -lgrpc_unsecure

INCLUDEPATH += $$PWD/../../external/release.x86/include
INCLUDEPATH += $$PWD/../../current/generated
INCLUDEPATH += $$PWD/../../current/client/include
INCLUDEPATH += $$PWD/../../current/include
INCLUDEPATH += $$PWD/../../current/include/sdevice
INCLUDEPATH += $$PWD/../../current/math/astro/include
INCLUDEPATH += $$PWD/../../current/math/attitude/include
INCLUDEPATH += $$PWD/../../current/current/include/parameters
INCLUDEPATH += $$PWD/../../linux_telescope_ui_lib/sofa/include

INCLUDEPATH += $$PWD/../../current_pilot_lib
INCLUDEPATH += $$PWD/../../current/system_service/client/include
INCLUDEPATH += $$PWD/../../current/system_service/include
INCLUDEPATH += $$PWD/../../external/eigen-3.4.0



win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../current/release/libtlins_client.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../current/debug/libtlins_client.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../current/release/tlins_client.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../current/debug/tlins_client.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../current/x86/libtlins_client.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-linux_telescope_ui_lib-Debug/release/ -llinux_telescope_ui_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-linux_telescope_ui_lib-Debug/debug/ -llinux_telescope_ui_lib
else:unix: LIBS += -L$$PWD/../../build-linux_telescope_ui_lib-Debug/ -llinux_telescope_ui_lib

INCLUDEPATH += $$PWD/../../build-linux_telescope_ui_lib-Debug
DEPENDPATH += $$PWD/../../build-linux_telescope_ui_lib-Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/release/liblinux_telescope_ui_lib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/debug/liblinux_telescope_ui_lib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/release/linux_telescope_ui_lib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/debug/linux_telescope_ui_lib.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/liblinux_telescope_ui_lib.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-linux_telescope_ui_lib-Debug/release/ -llinux_telescope_ui_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-linux_telescope_ui_lib-Debug/debug/ -llinux_telescope_ui_lib
else:unix: LIBS += -L$$PWD/../../build-linux_telescope_ui_lib-Debug/ -llinux_telescope_ui_lib

INCLUDEPATH += $$PWD/../../linux_telescope_ui_lib
DEPENDPATH += $$PWD/../../linux_telescope_ui_lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/release/liblinux_telescope_ui_lib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/debug/liblinux_telescope_ui_lib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/release/linux_telescope_ui_lib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/debug/linux_telescope_ui_lib.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../build-linux_telescope_ui_lib-Debug/liblinux_telescope_ui_lib.a
