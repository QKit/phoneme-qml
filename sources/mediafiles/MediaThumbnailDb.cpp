/*******************************************************************************
*                                                                              *
*  Thumbnail base implementation.                                              *
*                                                                              *
*  Copyright (C) 2011-2012 Kirill Chuvilin.                                    *
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

#include "MediaThumbnailDb.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

MediaThumbnailDb::MediaThumbnailDb(const QString dirPath) {
    this->db = QSqlDatabase::addDatabase("QSQLITE"); // register database
    this->setDirPath(dirPath);
    QObject::connect(&(this->generator), SIGNAL(thumbnailReady(QUrl)), this, SLOT(finishThumbnail(QUrl)));
}


void MediaThumbnailDb::setDirPath(const QString dirPath) {
    if (this->db.isOpen()) this->db.close(); // close opened
    QDir::root().mkpath(dirPath); // to be sure that path exists
    this->dir.setPath(dirPath);
#if defined(Q_OS_SYMBIAN)
    this->db.setDatabaseName("thumbnailDB.sqlite");
#else
    this->db.setDatabaseName(dirPath + "/thumbnailDB.sqlite");
#endif
    this->db.open();
    QSqlQuery query(this->db);
    query.exec("CREATE TABLE IF NOT EXISTS thumbnails (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, file_source BLOB, file_modified INT, ready TINYINT)");
    query.exec("CREATE INDEX IF NOT EXISTS file_source_index ON thumbnails(file_source)");
    emit dirPathChanged();
}


void MediaThumbnailDb::generateThumbnail(const QUrl &fileSource, bool inQueue) {
    QSqlQuery query(this->db); // query object
    query.prepare("SELECT id, file_modified, ready FROM thumbnails WHERE file_source=:file_source"); // query template
    query.bindValue(":file_source", fileSource);
    query.exec(); // execs query
    if (query.next()) { // there is a record for file
        QSqlRecord record = query.record();
        if (query.value(record.indexOf("ready")).toBool()) { // if thumbnail is ready
            int id = query.value(record.indexOf("id")).toInt();
            uint fileModified = query.value(record.indexOf("file_modified")).toUInt();
            this->refreshThumbnail(fileSource, id, fileModified, inQueue); // refresh it
        }
        // if isn't ready, then in process
    }
    else { // there is no record for file
        MediaFile mediaFile(fileSource); // file for source
        query.prepare("INSERT INTO thumbnails VALUES (null, :file_source, :file_modified, 0)"); // query template
        query.bindValue(":file_source", fileSource);
        query.bindValue(":file_modified", mediaFile.getLastModified());
        query.exec(); // execs query
        int id = query.lastInsertId().toInt();
        this->generator.generateThumbnail(fileSource, this->getThumbnailPathById(id), inQueue);
    }
}


void MediaThumbnailDb::refresh() {
    QSqlQuery query(this->db); // query object
    query.prepare("SELECT * FROM thumbnails"); // to select all ready
    query.exec(); // execs query
    while (query.next()) { // for all records
        QSqlRecord record = query.record();
        QUrl fileSource = query.value(record.indexOf("file_source")).toUrl();
        int id = query.value(record.indexOf("id")).toInt();
        uint fileModified = query.value(record.indexOf("file_modified")).toUInt();
        this->refreshThumbnail(fileSource, id, fileModified, false); // refresh it
    }
}


void MediaThumbnailDb::finishThumbnail(const QUrl& fileSource) {
    QSqlQuery query(this->db); // query object
    query.prepare("SELECT id FROM thumbnails WHERE file_source=:file_source"); // query template
    query.bindValue(":file_source", fileSource);
    query.exec(); // execs query
    query.next();
    int id = query.value(query.record().indexOf("id")).toInt();
    QString thumbnailPath = this->getThumbnailPathById(id);
    foreach (MediaFile* mediaFile, MediaFile::allBySource(fileSource)) // for all files with this source
        mediaFile->setThumbnail(thumbnailPath);
    query.prepare("UPDATE thumbnails SET ready=1 WHERE id=:id"); // query template
    query.bindValue(":id", id);
    query.exec(); // execs query
    this->m_lastFileSource = fileSource;
    emit lastFileSourceChanged();
}


void MediaThumbnailDb::refreshThumbnail(QUrl fileSource, int id, uint fileModified, bool inQueue) {
    QString thumbnailPath = this->getThumbnailPathById(id); // path to thumbnail
    uint mediaFileModified = 0; // will be time of source file last modify
    QSqlQuery query(this->db); // query object
    try {
        MediaFile mediaFile(fileSource); // try to create mediafile
        mediaFileModified = mediaFile.getLastModified(); // time of source file last modify
    } catch (MediaFile::Exception exception) { // if there are problems in mediafile creation
        switch (exception) {
        case MediaFile::EXCEPTION_ACCESS: // problems with access to file
            if (QFileInfo(thumbnailPath).exists()) this->dir.remove(this->getThumbnailNameById(id)); // remove thumbnail file if exists
            // remove record from database
            query.prepare("DELETE FROM thumbnails WHERE id=:id"); // query template
            query.bindValue(":id", id);
            query.exec(); // execs query
            return;
        default:
            throw exception; // rethrow exception
        }
    }
    if (QFile::exists(thumbnailPath)) { // make sure that thumbnail file exists
        if (fileModified == mediaFileModified) { // make sute that original file wasn't changed
            foreach (MediaFile* file, MediaFile::allBySource(fileSource)) // for all files with this source
                file->setThumbnail(thumbnailPath);
            return;
        }
    }
    // if there are any problems with thumbnail
    query.prepare("UPDATE thumbnails SET file_modified=:file_modified ready=0 WHERE file_source=:file_source"); // query template
    query.bindValue(":file_modified", mediaFileModified);
    query.bindValue(":file_source", fileSource);
    query.exec(); // execs query
    this->generator.generateThumbnail(fileSource, thumbnailPath, inQueue); // qenerate new thumbnail
}
