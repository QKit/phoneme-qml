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

#include "MediaFile.h"
#include <QImageReader>
#include <QColor>

QMultiMap<QUrl, MediaFile*> MediaFile::mediaFiles;

MediaFile::MediaFile(const QString &path, QObject *parent) :
    QObject(parent) {
    this->setPath(path);
    MediaFile::mediaFiles.insertMulti(this->getSource(), this); // add new file to list
}


MediaFile::MediaFile(const QUrl &source, QObject *parent) :
    QObject(parent) {
    this->setSource(source);
    mediaFiles.insertMulti(this->getSource(), this); // add new file to list
}


MediaFile::~MediaFile() {
    mediaFiles.remove(this->getSource(), this); // remove from file list
}


QUrl MediaFile::getThumbnail() {
    if (this->thumbnailPath.isNull()) emit generateThumbnail(this->getSource()); // signal to generate thumbnail for file if thumbnail isn't defined
    return this->thumbnailPath.isNull() ? QUrl(""): QUrl::fromLocalFile(this->thumbnailPath); // path to thumbnail
}


QImage MediaFile::getPreviewImage(int width, int height) const {
    if (!this->fileInfo.exists()) throw MediaFile::EXCEPTION_ACCESS;
    QImageReader imageReader(this->fileInfo.absoluteFilePath());
    imageReader.setQuality(0);
    QSize previewSize = imageReader.size();
    if ((width > 0 && height > 0) && (previewSize.width() > width || previewSize.height() > height)) previewSize.scale(width, height, Qt::KeepAspectRatio);
    imageReader.setScaledSize(previewSize);
    imageReader.setBackgroundColor(QColor(0,0,0,0));
    return imageReader.read();
}


QSize MediaFile::getPreviewSize() const {
    if (!this->fileInfo.exists()) throw MediaFile::EXCEPTION_ACCESS;
    QImageReader imageReader(this->fileInfo.absoluteFilePath());
    return imageReader.size();
}


void MediaFile::setPath(const QString &path) {
    mediaFiles.remove(this->getSource(), this); // remove with old source
    this->fileInfo.setFile(path);
    if (!this->fileInfo.exists()) throw MediaFile::EXCEPTION_ACCESS;
    mediaFiles.insertMulti(this->getSource(), this); // add with new source
    this->setThumbnail(QString::null); // no thumbnail
    emit sourceChanged();
}


void MediaFile::setSource(const QUrl &source) {
    this->setPath(source.toLocalFile());
}


void MediaFile::setThumbnail(const QString thumbnailPath) {
    this->thumbnailPath = thumbnailPath;
    emit thumbnailChanged(); // thumbnail was changed
}
