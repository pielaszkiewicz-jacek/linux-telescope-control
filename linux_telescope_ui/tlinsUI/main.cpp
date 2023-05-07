#include "tlinsuimainwindow.h"
#include "tlinsuistylesmanager.h"
#include <tlinsastrocatalogitem.h>
#include <tlinsuiconfgiurationitem.h>
#include <tlinsuidatabase.h>
#include <tlinsuidatabasedefinition.h>

#include <QApplication>
#include <QDebug>
#include <QStyleFactory>
#include <string>

#include "tlinsconfiguration.h"
#include <tlinsLogger.hpp>

#include <tlinskeyboard.h>

static void defaultConfiguration()
{
    char* home = getenv("HOME");

    std::string dbPath(home);
    dbPath += "/.astro.db";

    auto& cfg = TlinsAstroBase::tlinsConfiguration::getInstance();

    try {
        if (!cfg.hasKeyFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_FILE))
            cfg.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_FILE, dbPath);
    } catch (...) {
    }

    try {
        if (!cfg.hasKeyFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_TYPE))
            cfg.setValueFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_TYPE, "QSQLITE");
    } catch (...) {
    }
}

bool createDefaultDatabase()
{
    qDebug() << "---------------------------------------------------";
    qDebug() << "Create database";

    try {
        TlinsAstroBase::tlinsUIDatabase db;
        TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);
        dbDef.createDatabae();
    } catch (...) {
        qDebug() << "Error create database !!!";
        qDebug() << "---------------------------------------------------";
        return false;
    }
    qDebug() << "Success";
    qDebug() << "---------------------------------------------------";
    return true;
}

static tlinsUIMainWindow* mainWindowsPtr;

tlinsUIMainWindow* getMainWindowInstance()
{
    return mainWindowsPtr;
}

int main(int argc, char* argv[])
{
    auto& loggerInstance = tlinsLogger::instance();
    loggerInstance.setLoggerStd();
    loggerInstance.setLogLevel(tlinsLogger::LOG_LEVEL_DEBUG);

    // Domyslne wartosci parameterow
    defaultConfiguration();

    TlinsAstroBase::ObjectType::init();
    TlinsAstroBase::CatalogType::init();
    TlinsAstroBase::Constelations::init();

    if (!createDefaultDatabase()) {
        exit(1);
    }

    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    a.setPalette(darkPalette);

    tlinsUIMainWindow mainWindows;
    mainWindows.showFullScreen();
    mainWindows.show();
    mainWindowsPtr = &mainWindows;

    return a.exec();
}
