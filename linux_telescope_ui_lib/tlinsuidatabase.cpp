#include "tlinsuidatabase.h"
#include "tlinsconfiguration.h"
#include <QDebug>
#include <QThread>
#include <QVariant>
#include <stdio.h>

namespace TlinsAstroBase {

void tlinsUIDatabase::Query::prepere(const std::string& sql)
{
    if (!query.prepare(sql.c_str())) {
        qDebug() << "Error text            = " << query.driver()->lastError().text();
        qDebug() << "Error statement error = " << query.driver()->lastError().StatementError;
        qDebug() << "Error unknow error    = " << query.driver()->lastError().UnknownError;
        qDebug() << "Error database text   = " << query.driver()->lastError().databaseText();
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_PREPARE,
            std::string("Error prepeare query") + query.driver()->lastError().text().toStdString());
    }
}

long long tlinsUIDatabase::Query::lastInsertId() const
{
    return query.lastInsertId().toLongLong();
}

void tlinsUIDatabase::Query::execute()
{
    if (!query.exec()) {
        qDebug() << "Error text            = " << query.driver()->lastError().text();
        qDebug() << "Error statement error = " << query.driver()->lastError().StatementError;
        qDebug() << "Error unknow error    = " << query.driver()->lastError().UnknownError;
        qDebug() << "Error database text   = " << query.driver()->lastError().databaseText();
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_EXECUTE,
            std::string("Error execute query") + query.driver()->lastError().text().toStdString());
    }

    if (query.isSelect()) {
        resultRecord = query.record();
    }
}

void tlinsUIDatabase::Query::clear()
{
    query.clear();
}

int tlinsUIDatabase::Query::size() const
{
    return query.numRowsAffected();
}

bool tlinsUIDatabase::Query::next()
{
    if (!query.isSelect()) {
        qDebug() << "Error text            = " << query.driver()->lastError().text();
        qDebug() << "Error statement error = " << query.driver()->lastError().StatementError;
        qDebug() << "Error unknow error    = " << query.driver()->lastError().UnknownError;
        qDebug() << "Error database text   = " << query.driver()->lastError().databaseText();
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY,
            std::string("Error execute query") + query.driver()->lastError().text().toStdString());
    }
    bool res = query.next();
    if (res) {
        if (query.isSelect())
            resultRecord = query.record();
    }
    return res;
}

void tlinsUIDatabase::Query::bindValue(const std::string& name, const std::string& v)
{
    query.bindValue(QString(name.c_str()), QVariant(QString(v.c_str())), QSql::In);
}

void tlinsUIDatabase::Query::bindValue(const std::string& name, const double v)
{
    query.bindValue(QString(name.c_str()), v, QSql::In);
}

void tlinsUIDatabase::Query::bindValue(const std::string& name, const long long v)
{
    query.bindValue(QString(name.c_str()), v, QSql::In);
}

void tlinsUIDatabase::Query::bindValue(const std::string& name, const int v)
{
    query.bindValue(QString(name.c_str()), v, QSql::In);
}

void tlinsUIDatabase::Query::readValue(const std::string& name, std::string& v, bool& isNull)
{
    QVariant var = resultRecord.value(QString(name.c_str()));
    if (!var.isValid())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unknown column"));

    if (var.type() != QVariant::String)
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unexpected column type"));

    isNull = var.isNull();
    if (!isNull)
        v = var.toString().toStdString();
}

void tlinsUIDatabase::Query::readValue(const std::string& name, double& v, bool& isNull)
{
    QVariant var = resultRecord.value(QString(name.c_str()));
    if (!var.isValid())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unknown column"));

    if (var.type() != QVariant::Double)
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unexpected column type"));

    isNull = var.isNull();
    if (!isNull)
        v = var.toDouble();
}

void tlinsUIDatabase::Query::readValue(const std::string& name, long long& v, bool& isNull)
{
    QVariant var = resultRecord.value(QString(name.c_str()));
    if (!var.isValid())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unknown column"));

    if (var.type() != QVariant::LongLong)
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unexpected column type"));

    isNull = var.isNull();
    if (!isNull)
        v = var.toLongLong();
}

void tlinsUIDatabase::Query::readValue(const std::string& name, int& v, bool& isNull)
{
    QVariant var = resultRecord.value(QString(name.c_str()));
    if (!var.isValid())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unknown column"));

    if (var.type() != QVariant::LongLong)
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unexpected column type"));

    isNull = var.isNull();
    if (!isNull)
        v = var.toLongLong();
}

void tlinsUIDatabase::Query::readValue(const int idx, std::string& v, bool& isNull)
{
    if (idx >= resultRecord.count())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unknown column"));

    QVariant var = resultRecord.value(idx);
    if (var.type() != QVariant::String)
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unexpected column type"));

    isNull = var.isNull();
    if (!isNull)
        v = var.toString().toStdString();
}

void tlinsUIDatabase::Query::readValue(const int idx, double& v, bool& isNull)
{
    if (idx >= resultRecord.count())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unknown column"));

    QVariant var = resultRecord.value(idx);
    if (var.type() != QVariant::Double)
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unexpected column type"));

    isNull = var.isNull();
    if (!isNull)
        v = var.toDouble();
}

void tlinsUIDatabase::Query::readValue(const int idx, long long& v, bool& isNull)
{
    if (idx >= resultRecord.count())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unknown column"));

    QVariant var = resultRecord.value(idx);
    if (var.type() != QVariant::Double)
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unexpected column type"));

    isNull = var.isNull();
    if (!isNull)
        v = var.toLongLong();
}

void tlinsUIDatabase::Query::readValue(const int idx, int& v, bool& isNull)
{
    if (idx >= resultRecord.count())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unknown column"));

    QVariant var = resultRecord.value(idx);
    if (var.type() != QVariant::Double)
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_QUERY, std::string("Unexpected column type"));

    isNull = var.isNull();
    if (!isNull)
        v = var.toLongLong();
}

tlinsUIDatabase::Query::~Query()
{
}

// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------

std::shared_ptr<tlinsUIDatabase::Query> tlinsUIDatabase::createQuery()
{
    return std::shared_ptr<tlinsUIDatabase::Query>(new tlinsUIDatabase::Query(database));
}

void tlinsUIDatabase::startTransaction()
{
    if (!database.driver()->hasFeature(QSqlDriver::Transactions))
        return;

    database.transaction();
}

void tlinsUIDatabase::commitTransaction()
{
    if (!database.driver()->hasFeature(QSqlDriver::Transactions))
        return;

    database.commit();
}

void tlinsUIDatabase::rollbackTransaction()
{
    if (!database.driver()->hasFeature(QSqlDriver::Transactions))
        return;

    database.rollback();
}

tlinsUIDatabase::tlinsUIDatabase(const std::string& dbName)
{
    database = QSqlDatabase::addDatabase("QSQLITE", "EmbeddedDB");
    database.setDatabaseName(dbName.c_str());

    if (!database.open()) {
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_OPEN, std::string("Error open db : ") + dbName);
    }
}

tlinsUIDatabase::tlinsUIDatabase(const std::string& dbType,
    const std::string& connName,
    const std::string& databaseName,
    const std::string& host,
    const std::string& user,
    const std::string& pass)
{
    database = QSqlDatabase::addDatabase(dbType.c_str(), connName.c_str());
    database.setHostName(host.c_str());
    database.setUserName(user.c_str());
    database.setPassword(pass.c_str());
    database.setDatabaseName(databaseName.c_str());

    if (!database.open()) {
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_OPEN, std::string("Error open db : ") + databaseName);
    }
}

tlinsUIDatabase::tlinsUIDatabase()
{
    auto& conf = TlinsAstroBase::tlinsConfiguration::getInstance();

    std::string dbType { "" };
    if (conf.hasKeyFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
            TlinsAstroBase::tlinsConfiguration::DATABASE_TYPE))
        dbType = conf.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
            TlinsAstroBase::tlinsConfiguration::DATABASE_TYPE);
    if (dbType.length() == 0)
        dbType = "QSQLITE";

    std::string connName { "" };
    if (conf.hasKeyFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
            TlinsAstroBase::tlinsConfiguration::DATABASE_CONNECTION_NAME))
        connName = conf.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
            TlinsAstroBase::tlinsConfiguration::DATABASE_CONNECTION_NAME);
    if (connName.length() == 0) {
        std::string root_path {};
        if (getenv("TLINS_ASTRO_BAS_DIR") != NULL)
            root_path = getenv("TLINS_ASTRO_BAS_DIR");
        else
            root_path = getenv("HOME");

        connName = root_path + "/.astro.db" + QString::number((quint64)QThread::currentThread(), 16).toStdString();
    }

    if (!QSqlDatabase::contains(QString::fromStdString(connName))) {
        database = QSqlDatabase::addDatabase(QString::fromStdString(dbType), QString::fromStdString(connName));

        std::string host { "" };
        if (conf.hasKeyFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_HOST)) {
            host = conf.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_HOST);
            if (host.length() != 0)
                database.setHostName(QString::fromStdString(host));
        }

        std::string user { "" };
        if (conf.hasKeyFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_USER)) {
            user = conf.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_USER);
            if (user.length() != 0)
                database.setUserName(QString::fromStdString(user));
        }

        std::string pass { "" };
        if (conf.hasKeyFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_PASSWORD)) {
            pass = conf.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_PASSWORD);
            if (pass.length() != 0)
                database.setPassword(QString::fromStdString(pass));
        }

        std::string dbName { connName };
        if (conf.hasKeyFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_FILE)) {
            dbName = conf.getStringFile(TlinsAstroBase::tlinsConfiguration::DATABASE_GROUP,
                TlinsAstroBase::tlinsConfiguration::DATABASE_FILE);
            if (dbName.length() != 0)
                database.setDatabaseName(QString::fromStdString(dbName));
        }

        if (!database.isOpen()) {
            if (!database.open()) {
                {
                    auto err1 = database.lastError();
                }

                throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_DB_OPEN, std::string("Error open db : ") + dbName);
            }
        }
    } else {
        database = QSqlDatabase::database(QString::fromStdString(connName));
    }
}

tlinsUIDatabase::~tlinsUIDatabase()
{
    if (database.isOpen()) {
        database.close();
    }
}

}
