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

#include "MediaThumbnailGenerator.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

MediaThumbnailGenerator::MediaThumbnailGenerator() {
    this->maxWidth = 128;
    this->maxHeight = 128;
}


void MediaThumbnailGenerator::generateThumbnail(const QUrl& fileSource, const QString& thumbnailPath, bool inQueue) {
    if (inQueue) {
        QMutexLocker todoStackLocker(&this->toProcessStackMutex);
        bool isAtStack = false;
        MediaThumbnailElement element;
        // try to find it in todo stack
        for (int i = 0; i < this->toProcessStack.size(); i++) {
            if (this->toProcessStack.at(i).fileSource == fileSource) {
                isAtStack = true;
                element = this->toProcessStack.takeAt(i);
                break;
            }
        }
        if (!isAtStack) { // if wasn't in todo stack
            element.fileSource = fileSource;
            element.thumbnailPath = thumbnailPath;
        }
        this->toProcessStack.append(element); // append new or taken element
        todoStackLocker.unlock();
        if (!this->isRunning())
            this->start();
    } else {
        MediaFile mediaFile(fileSource); // media file for the source
        mediaFile.getPreviewImage(this->maxWidth, this->maxHeight).save(thumbnailPath); // saves thumbnail
        QFileInfo fileTester(thumbnailPath);
        while (!fileTester.isWritable()) {} // whait for creation
    }
}


void MediaThumbnailGenerator::run() {
    while (true) {
        QMutexLocker todoStackLocker(&this->toProcessStackMutex);
        if (this->toProcessStack.isEmpty())
            return;
        MediaThumbnailElement element = this->toProcessStack.takeLast();
        todoStackLocker.unlock();
        this->generateThumbnail(element.fileSource, element.thumbnailPath, false);
        emit thumbnailReady(element.fileSource);
    }
}
