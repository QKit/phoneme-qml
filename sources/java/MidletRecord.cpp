/*******************************************************************************
*                                                                              *
*  Midlet base record implementation.                                          *
*                                                                              *
*  Copyright (C) 2012 Kirill Chuvilin.                                         *
*  All rights reserved.                                                        *
*  Contact: Kirill Chuvilin (kirill.chuvilin@gmail.com, kirik-ch.ru)           *
*                                                                              *
*  This file is part of the Folder Gallery project.                            *
*                                                                              *
*  $QT_BEGIN_LICENSE:GPL$                                                      *
*  You may use this file under the terms of the GNU General Public License     *
*  as published by the Free Software Foundation; version 3 of the License.     *
*                                                                              *
*  This file is distributed in the hope that it will be useful,                *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
*  GNU General Public License for more details.                                *
*                                                                              *
*  You should have received a copy of the GNU General Public License           *
*  along with this package; if not, write to the Free Software                 *
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.   *
*  $QT_END_LICENSE$                                                            *
*                                                                              *
*******************************************************************************/

#include "MidletRecord.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include "Phoneme.h"

MidletRecord::MidletRecord(MidletDb &midletDb, const QString name, const QString version, const QString mainClass) {
    this->m_midletDb = &midletDb;
    this->m_id = 0;
    this->m_name = name;
    this->m_version = version;
    this->m_mainClass = mainClass;
}


MidletRecord::MidletRecord(MidletDb &midletDb, const QSqlQuery &sqlQuery) {
    this->m_midletDb = &midletDb;
    QSqlRecord record = sqlQuery.record();
    this->m_id = sqlQuery.value(record.indexOf("id")).toInt();
    this->m_name = sqlQuery.value(record.indexOf("name")).toString();
    this->m_version = sqlQuery.value(record.indexOf("version")).toString();
    this->m_mainClass = sqlQuery.value(record.indexOf("main_class")).toString();
}


QString MidletRecord::getJarPath() const {
    return this->m_midletDb->getDirPath() + "/" + this->getJarFileName();
}


QString MidletRecord::getJadPath() const {
    return this->m_midletDb->getDirPath() + "/" + this->getJadFileName();
}


QString MidletRecord::getIconPath() const {
#if defined(Q_WS_MAEMO_5)
    return QDir::homePath() + "/.local/share/icons/hicolor/64x64/apps/" + this->getIconFileName();
#elif defined(Q_WS_HARMATTAN)
    return QDir::homePath() + "/.local/share/icons/hicolor/80x80/apps/" + this->getIconFileName();
#endif
    return this->m_midletDb->getDirPath() + "/" + this->getIconFileName();
}


QString MidletRecord::getDesktopFilePath() const {
#if defined(Q_WS_MAEMO_5)
    return QDir::homePath() + "/.local/share/applications/hildon/" + this->getDesktopFileName();
#elif defined(Q_WS_HARMATTAN)
    return QDir::homePath() + "/.local/share/applications/" + this->getDesktopFileName();
#else
    return this->m_midletDb->getDirPath() + QString("/") + this->getDesktopFileName();
#endif
}


QString MidletRecord::getExecCommand() const {
    return Phoneme::instance()->getExecMidletCommand(this->getJarPath(), this->getJadPath(), this->getMainClass());
}


bool MidletRecord::addToBase(QSqlQuery &sqlQuery) {
    if (this->m_id) return false; // already in base
    sqlQuery.prepare("INSERT INTO midlets VALUES (null, :name, :version, :main_class)"); // query template
    sqlQuery.bindValue(":name", this->m_name);
    sqlQuery.bindValue(":version", this->m_version);
    sqlQuery.bindValue(":main_class", this->m_mainClass);
    if (sqlQuery.exec()) { // if query exec id correct
        this->m_id = sqlQuery.lastInsertId().toInt();
        emit this->idChanged();
        return true;
    } else {
        return false;
    }
}


bool MidletRecord::removeFromBase(QSqlQuery &sqlQuery) {
    if (!this->m_id) return false; // not in base
    sqlQuery.prepare("DELETE FROM midlets WHERE id=:id"); // query template
    sqlQuery.bindValue(":id", this->m_id);
    if (sqlQuery.exec()) { // if query exec id correct
        this->m_id = 0;
        emit this->idChanged();
        return true;
    } else {
        return false;
    }
}


void MidletRecord::saveMidletDesktopFile() const {
    QString path = this->getDesktopFilePath();
    QDir::root().mkpath(QFileInfo(path).dir().path()); // creates dir for file
    QFile desktopFile(path);
    desktopFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outStream(&desktopFile);
    outStream << "[Desktop Entry]\n";
    outStream << "Encoding=UTF-8\n";
    outStream << "Version=1.0\n";
    outStream << "Type=Application\n";
    outStream << "Terminal=false\n";
    outStream << "Name=" << this->getName() << "\n";
    outStream << "Exec=" << "/opt/phoneme-qml/bin/phoneme-qml --execmidlet --id " << this->getId() << "\n";
#if defined(Q_WS_MAEMO_5)
    outStream << "Icon=" << QFileInfo(this->getIconPath()).baseName() << "\n";
#elif defined(Q_WS_HARMATTAN)
    outStream << "Icon=" << this->getIconPath() << "\n";
#endif
    outStream << "X-Window-Icon=\n";
    outStream << "X-HildonDesk-ShowInToolbar=true\n";
    outStream << "X-Osso-Type=application/x-executable\n";
    desktopFile.close();
}


int MidletRecord::exec() const {
    return Phoneme::instance()->execMidlet(this->getJarPath(), this->getJadPath(), this->getMainClass());
}
