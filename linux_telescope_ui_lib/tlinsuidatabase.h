#ifndef TLINSUIDATABASE_H
#define TLINSUIDATABASE_H

#include <QSqlError>
#include <QtSql>
#include <memory>
#include <string>
#include <tlinsuiexception.h>

namespace TlinsAstroBase {

class tlinsUIDatabase {
private:
    QSqlDatabase database;

public:
    class Query {
    private:
        QSqlQuery query;
        QSqlRecord resultRecord;

    public:
        void prepere(const std::string& sql);
        void execute();
        void clear();
        bool next();

        QSqlError getLastError()
        {
            return query.lastError();
        }

        void bindValue(const std::string& name, const std::string& v);
        void bindValue(const std::string& name, const double v);
        void bindValue(const std::string& name, const long long v);
        void bindValue(const std::string& name, const int v);

        void readValue(const std::string& name, std::string& v, bool& isNull);
        void readValue(const std::string& name, double& v, bool& isNull);
        void readValue(const std::string& name, long long& v, bool& isNull);
        void readValue(const std::string& name, int& v, bool& isNull);

        void readValue(const int idx, std::string& v, bool& isNull);
        void readValue(const int idx, double& v, bool& isNull);
        void readValue(const int idx, long long& v, bool& isNull);
        void readValue(const int idx, int& v, bool& isNull);

        long long lastInsertId() const;
        int size() const;

        Query(QSqlDatabase db)
            : query(db)
        {
        }

        virtual ~Query();
    };

private:
    void createDatabaseSchema();

public:
    std::shared_ptr<tlinsUIDatabase::Query> createQuery();
    void startTransaction();
    void commitTransaction();
    void rollbackTransaction();

    tlinsUIDatabase();
    tlinsUIDatabase(const std::string& dbName);
    tlinsUIDatabase(const std::string& dbType,
        const std::string& connName,
        const std::string& databaseName,
        const std::string& host,
        const std::string& user,
        const std::string& pass);

    virtual ~tlinsUIDatabase();
};

}
#endif // TLINSUIDATABASE_H
