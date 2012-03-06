/*******************************************************************************
*                                                                              *
*  Thumbnails generator implementation.                                        *
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

#ifndef _MediaThumbnailGenerator_h_
#define _MediaThumbnailGenerator_h_

#include <QThread>
#include <QMutex>
#include "MediaFile.h"

/*!
 * \brief Element of thumbnails queue.
 * \author KiRiK aka Kirill Chuvilin (kirik-ch.ru)
 */
struct MediaThumbnailElement {
    QUrl fileSource; //!< source file
    QString thumbnailPath; //!< path to thumbnail
};

/*!
 * \brief Thumbnail generator thread.
 * \author KiRiK aka Kirill Chuvilin (kirik-ch.ru)
 */
class MediaThumbnailGenerator : public QThread {
    Q_OBJECT

public:
    /*!
     * \brief Constructor.
     * \param dirPath path to dir with thumbnails
     */
    MediaThumbnailGenerator();

public slots:
    /*!
     * \brief Adds thumbnail for file.
     * \param fileSource    source file
     * \param thumbnailPath path to thumbnail
     * \param inQueue       use queue of separate thread or not
     */
    void generateThumbnail(const QUrl& fileSource, const QString& thumbnailPath, bool inQueue = true);

    /*!
     * \brief Separate thread action.
     */
    virtual void run();

signals:
    /*!
     * \brief Emits when thumbnail file generated.
     * \param fileSource source file
     */
    void thumbnailReady(const QUrl& fileSource) const;

private:
    int maxWidth; //!< max width of thumbnail
    int maxHeight; //!< max height of thumbnail
    QList<MediaThumbnailElement> toProcessStack; //!< unfinished thumbnails
    QMutex toProcessStackMutex; //!< to protect todoStack in threads
};

#endif // _MediaThumbnailGenerator_h_
