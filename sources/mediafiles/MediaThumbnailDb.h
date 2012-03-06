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

#ifndef _MediaThumbnailDb_h_
#define _MediaThumbnailDb_h_

#include <QMap>
#include <QDir>
#include <QSqlDatabase>

#include "MediaFile.h"
#include "MediaThumbnailGenerator.h"

class MediaThumbnailDb : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString dirPath READ getDirPath WRITE setDirPath NOTIFY dirPathChanged) //!< absolute path to dir with thumbnail files
    Q_PROPERTY(QUrl lastFileSource READ getLastFileSource NOTIFY lastFileSourceChanged) //!< last processed file

public:
    /*!
     * \brief Constructor.
     * \param dirPath string with path path to directory with thumbnail files
     */
    explicit MediaThumbnailDb(const QString dirPath = QDir::tempPath());

    /*!
     * \brief Returns absolute path to directory with thumbnail files.
     * \return string absolute path to directory with thumbnail files
     */
    QString getDirPath() const {return this->dir.absolutePath();}

    /*!
     * \brief Returns last processed file.
     * \return url with source of last precessed file
     */
    QUrl getLastFileSource() const {return this->m_lastFileSource;}

public slots:
    /*!
     * \brief Sets directory for thumbnails.
     * \param dirPath string with path path to directory with thumbnail files
     */
    void setDirPath(const QString dirPath);

    /*!
     * \brief Adds thumbnail for file.
     * \param fileSource url to file source
     * \param inQueue use queue of separate thread or not
     */
    void generateThumbnail(const QUrl &fileSource, bool inQueue = true);

    /*!
     * \brief Adds thumbnail for file.
     */
    void refresh();

signals:
    /*!
     * Emits when dirPath ptoperty changes.
     */
    void dirPathChanged();
    /*!
     * Emits when lastFile ptoperty changes.
     */
    void lastFileSourceChanged();

private:
    QSqlDatabase db; //!< database
    QDir dir; //!< to operate with thumbnails dir
    MediaThumbnailGenerator generator; //!< to generate thumbnails in separate thread
    QUrl m_lastFileSource; //!< last processed file

    /*!
     * \brief Returns name of thumbnail file by id.
     * \return string with name of thumbnail file
     * \param id file id
     */
    QString getThumbnailNameById(int id) const {return QString("thumbnail" + QString::number(id) + ".png");}

    /*!
     * \brief Returns path to thumbnail by id.
     * \return string with absolute path to thumbnail file
     * \param id file id
     */
    QString getThumbnailPathById(int id) const {return this->dir.absoluteFilePath(this->getThumbnailNameById(id));}

private slots:
    /*!
     * \brief Sets ready thumbnails to files.
     * \param fileSource url to file
     */
    void finishThumbnail(const QUrl& fileSource);

    void refreshThumbnail(QUrl fileSource, int id, uint fileModified, bool inQueue);
};

#endif // _MediaThumbnailDb_h_
