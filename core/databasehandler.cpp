#include "databasehandler.h"

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent)
{
}

DatabaseHandler::~DatabaseHandler()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseHandler::initialize()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("socialapp.db");

    if (!m_db.open()) {
        qCritical() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }

    return createTables();
}

bool DatabaseHandler::createTables()
{
    QSqlQuery query(m_db);

    const QString createUsers = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            avatar TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";

    const QString createStories = R"(
        CREATE TABLE IF NOT EXISTS stories (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            video_path TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
        )
    )";

    if (!query.exec(createUsers)) {
        qCritical() << "Failed to create users table:" << query.lastError().text();
        return false;
    }

    if (!query.exec(createStories)) {
        qCritical() << "Failed to create stories table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHandler::addUser(const QString &username, const QString &avatar)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (username, avatar) VALUES (:username, :avatar)");
    query.bindValue(":username", username);
    query.bindValue(":avatar", avatar);

    if (!query.exec()) {
        qWarning() << "Failed to add user:" << query.lastError().text();
        return false;
    }
    return true;
}

QVariantList DatabaseHandler::getAllUsers()
{
    QVariantList users;
    QSqlQuery query(m_db);

    if (query.exec("SELECT id, username, avatar FROM users ORDER BY username")) {
        while (query.next()) {
            QVariantMap user;
            user["id"] = query.value(0).toInt();
            user["username"] = query.value(1).toString();
            user["avatar"] = query.value(2).toString();
            users.append(user);
        }
    }
    return users;
}

bool DatabaseHandler::addStory(const QString &userId, const QString &videoPath)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO stories (user_id, video_path) VALUES (:userId, :videoPath)");
    query.bindValue(":userId", userId);
    query.bindValue(":videoPath", videoPath);

    if (!query.exec()) {
        qWarning() << "Failed to add story:" << query.lastError().text();
        return false;
    }
    return true;
}
