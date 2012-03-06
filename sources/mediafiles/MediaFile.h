/*******************************************************************************
*                                                                              *
*  Abstract media file implementation.                                         *
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

#ifndef _MediaFile_h_
#define _MediaFile_h_

#include <QObject>
#include <QUrl>
#include <QFileInfo>
#include <QImage>
#include <QDateTime>
#include <QMultiMap>

/*!
 * \brief Media file class.
 * \author KiRiK aka Kirill Chuvilin (kirik-ch.ru)
 */
class MediaFile : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ getName NOTIFY sourceChanged) //!< name of file
    Q_PROPERTY(QUrl source READ getSource WRITE setSource NOTIFY sourceChanged) //!< path to file
    Q_PROPERTY(QUrl thumbnail READ getThumbnail NOTIFY thumbnailChanged) //!< path to thumbnail file
    Q_PROPERTY(uint lastModified READ getLastModified NOTIFY sourceChanged) //!< time of last modify
    Q_PROPERTY(QSize previewSize READ getPreviewSize NOTIFY sourceChanged) //!< size of preview image

public:
    enum Exception { //!< MediaFile exceptions
        EXCEPTION_ACCESS //!< throws when cann't access to source file
    };

    /*!
     * \brief Constructor.
     * \param path   string with path to file
     * \param parent parent object
     */
    explicit MediaFile(const QString &path = QString::null, QObject *parent = 0);

    /*!
     * \brief Constructor.
     * \param source url to to file
     * \param parent parent object
     */
    explicit MediaFile(const QUrl &source, QObject *parent = 0);

    /*!
     * \brief Destructor.
     * \param source url to to file
     * \param parent parent object
     */
    ~MediaFile();

    /*!
     * \brief Returns name of file.
     * \return string with directory name
     */
    QString getName() const {return this->fileInfo.baseName();}

    /*!
     * \brief Returns path to file.
     * \return string with absolute path
     */
    QString getPath() const {return this->fileInfo.absoluteFilePath();}

    /*!
     * \brief Returns url to file.
     * \return source url
     */
    QUrl getSource() const {return QUrl::fromLocalFile(this->fileInfo.absoluteFilePath());}

    /*!
     * \brief Returns path to thumbnail file.
     * \return string with absolute path
     */
    QUrl getThumbnail();

    /*!
     * \brief Returns preview image for file.
     * \param width  max width
     * \param height max height
     */
    QImage getPreviewImage(int width, int height) const;

    /*!
     * \brief Returns time of last modify.
     * \return time of last modify in seconds since 1970-01-01T00:00:00, Coordinated Universal Time
     */
    uint getLastModified() const {return this->fileInfo.lastModified().toTime_t();}

    /*!
     * \brief Returns size of preview image.
     * \return size of file preview image or (0,0) if it can't be determined
     */
    QSize getPreviewSize() const;

    /*!
     * \brief Selects all files with particular source.
     * \return list of pointers to files
     * \param source url with file source
     */
    static QList<MediaFile*> allBySource(const QUrl &source) {return MediaFile::mediaFiles.values(source);}

public slots:
    /*!
     * \brief Sets path to file.
     * \param string with path to file
     */
    void setPath(const QString &path);

    /*!
     * \brief Sets url to file.
     * \param source source url
     */
    void setSource(const QUrl &source);

    /*!
     * \brief Sets path to thumbnail file.
     * \param thumbnailPath string with path to thumbnail image
     */
    void setThumbnail(const QString thumbnailPath);

signals:
    /*!
     * \brief Emited when source property changes.
     */
    void sourceChanged();

    /*!
     * \brief Emited when thumbnail property changes.
     */
    void thumbnailChanged();

    /*!
     * \brief Emited when new thumbnail is needed.
     * \param source url to file source
     */
    void generateThumbnail(const QUrl &source);

private:
    QFileInfo fileInfo; //!< file info object
    QString thumbnailPath; //!< path to thumbnail
    static QMultiMap<QUrl, MediaFile*> mediaFiles; //!< list of all media files
};

#endif // _MediaFile_h_
