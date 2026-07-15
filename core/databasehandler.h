#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariantList>
#include <QDebug>

class DatabaseHandler : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    ~DatabaseHandler();

    Q_INVOKABLE bool initialize();
    Q_INVOKABLE bool addUser(const QString &username, const QString &avatar);
    Q_INVOKABLE QVariantList getAllUsers();
    Q_INVOKABLE bool addStory(const QString &userId, const QString &videoPath);

private:
    QSqlDatabase m_db;
    bool createTables();
};

#endif // DATABASEHANDLER_H
