/*******************************************************************************
*                                                                              *
*  Midlet base implementation.                                                 *
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

#include "MidletDb.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include "DeclarativeList.h"


MidletDb::MidletDb(const QString dirPath) {
    this->db = QSqlDatabase::addDatabase("QSQLITE"); // register database
    this->setDirPath(dirPath);
}


MidletDb::~MidletDb() {
    foreach (MidletRecord* midlet, this->m_midlets) delete midlet;
}

void MidletDb::setDirPath(const QString dirPath) {
    if (this->db.isOpen()) this->db.close(); // close opened
    QDir::root().mkpath(dirPath); // to be sure that path exists
    this->dir.setPath(dirPath);
    this->db.setDatabaseName(dirPath + "/midletDB.sqlite");
    this->db.open();
    QSqlQuery query(this->db);
    query.exec("CREATE TABLE IF NOT EXISTS midlets (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, name BLOB, version BLOB, main_class BLOB)");
    this->refreshMidlets();
    emit dirPathChanged();
}


bool MidletDb::addMidlet(const MidletFile &midletFile) {
    if (!midletFile.getStatus()) return false;
    MidletRecord* newMidletRecord = new MidletRecord(*this, midletFile.getName(), midletFile.getVersion(), midletFile.getMainClass());
    QSqlQuery query(this->db); // query object
    if (newMidletRecord->addToBase(query)) { // if midlet was added to base
        midletFile.saveJarFile(newMidletRecord->getJarPath());
        midletFile.saveJadFile(newMidletRecord->getJadPath());
        midletFile.saveIconFile(newMidletRecord->getIconPath());
        newMidletRecord->saveMidletDesktopFile();
        this->m_midlets.append(newMidletRecord);
        emit this->midletsChanged(); // change signal
        return true;
    } else {
        delete newMidletRecord; // deletes new midlet
        return false;
    }
}


bool MidletDb::addMidlet(const QString jarPath, QString jadPath, QString iconPath) {
    MidletFile midletFile(jarPath, jadPath, iconPath);
    return this->addMidlet(midletFile);
}


bool MidletDb::addMidlet(const QUrl jarSource, QUrl jadSource, QUrl iconSource) {
    MidletFile midletFile(jarSource, jadSource, iconSource);
    return this->addMidlet(midletFile);
}


bool MidletDb::removeMidlet(const int id) {
    int iMidlet = 0; // midlet for remove
    for ( ; iMidlet < this->m_midlets.length(); iMidlet++) // for all midlets
        if (this->m_midlets[iMidlet]->getId() == id) break;
    if (iMidlet >= this->m_midlets.length()) return false; // no midlet with the id
    MidletRecord* midletRecord = m_midlets[iMidlet]; // record to remove
    QFileInfo(midletRecord->getJarPath()).dir().remove(midletRecord->getJarFileName());
    QFileInfo(midletRecord->getJadPath()).dir().remove(midletRecord->getJadFileName());
    QFileInfo(midletRecord->getIconPath()).dir().remove(midletRecord->getIconFileName());
    QFileInfo(midletRecord->getDesktopFilePath()).dir().remove(midletRecord->getDesktopFileName());
    QSqlQuery query(this->db); // query object
    if (midletRecord->removeFromBase(query)) { // if midlet was removed from base
        this->m_midlets.removeAt(iMidlet);
        emit this->midletsChanged(); // change signal
        delete midletRecord; // clears memory
        return true;
    } else {
        return false;
    }
}


void MidletDb::refreshMidlets() {
    QList<MidletRecord*> oldMidlets = this->m_midlets; // to delete later
    this->m_midlets.clear();
    QSqlQuery query(this->db); // query object
    query.prepare("SELECT * FROM midlets"); // to select all records
    query.exec(); // execs query
    while (query.next()) { // for all records
        this->m_midlets.append(new MidletRecord(*this, query));
    }
    emit this->midletsChanged(); // change signal
    foreach (MidletRecord* midletRecord, oldMidlets) delete midletRecord; // deletes all old
}

//void MidletDb::refreshThumbnail(QUrl fileSource, int id, uint fileModified, bool inQueue) {
//    QString thumbnailPath = this->getThumbnailPathById(id); // path to thumbnail
//    uint mediaFileModified = 0; // will be time of source file last modify
//    QSqlQuery query(this->db); // query object
//    try {
//        MediaFile mediaFile(fileSource); // try to create mediafile
//        mediaFileModified = mediaFile.getLastModified(); // time of source file last modify
//    } catch (MediaFile::Exception exception) { // if there are problems in mediafile creation
//        switch (exception) {
//        case MediaFile::EXCEPTION_ACCESS: // problems with access to file
//            if (QFileInfo(thumbnailPath).exists()) this->dir.remove(this->getThumbnailNameById(id)); // remove thumbnail file if exists
//            // remove record from database
//            query.prepare("DELETE FROM thumbnails WHERE id=:id"); // query template
//            query.bindValue(":id", id);
//            query.exec(); // execs query
//            return;
//        default:
//            throw exception; // rethrow exception
//        }
//    }
//    if (QFile::exists(thumbnailPath)) { // make sure that thumbnail file exists
//        if (fileModified == mediaFileModified) { // make sute that original file wasn't changed
//            foreach (MediaFile* file, MediaFile::allBySource(fileSource)) // for all files with this source
//                file->setThumbnail(thumbnailPath);
//            return;
//        }
//    }
//    // if there are any problems with thumbnail
//    query.prepare("UPDATE thumbnails SET file_modified=:file_modified ready=0 WHERE file_source=:file_source"); // query template
//    query.bindValue(":file_modified", mediaFileModified);
//    query.bindValue(":file_source", fileSource);
//    query.exec(); // execs query
//    this->generator.generateThumbnail(fileSource, thumbnailPath, inQueue); // qenerate new thumbnail
//}
