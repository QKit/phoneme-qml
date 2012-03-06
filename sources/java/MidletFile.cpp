/*******************************************************************************
*                                                                              *
*  Java midlet handle implementation.                                          *
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

#include "MidletFile.h"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>
#include <QImageReader>
#include <QColor>


MidletFile::MidletFile(const QString jarPath, const QString jadPath, const QString iconPath) {
    this->setJarPath(jarPath); // path to .jar file
    this->setJadPath(jadPath); // path to .jad file
    this->setIconPath(iconPath); // path to icon file
}


MidletFile::MidletFile(const QUrl jarSource, const QUrl jadSource, const QUrl iconSource) {
    this->setJarSource(jarSource); // url to .jar file
    this->setJadSource(jadSource); // url to .jad file
    this->setIconSource(iconSource); // url to icon file
}


bool MidletFile::getStatus() const {
    if (this->m_jarPath.isEmpty()) return false;
    if (this->m_iconPath.isEmpty()) return false;
    if (this->m_mainClass.isEmpty()) return false;
    if (this->m_name.isEmpty()) return false;
    if (this->m_version.isEmpty()) return false;
    return true;
}


void MidletFile::setJarPath(const QString path) {
    this->m_jarPath = path; // sets path
    emit this->jarSourceChanged(); // signal of change
    emit this->statusChanged(); // signal of status change
}


void MidletFile::setJadPath(const QString path) {
    this->m_jadPath = path; // sets path
    QFile jadFile(this->m_jadPath);
    jadFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream jadStream(&jadFile);
    jadStream.setCodec("UTF-8");
    QString jadText = jadStream.readAll(); // content of .jad file
    jadFile.close();
    this->parseJad(jadText); // gets meta from file
    emit this->jadSourceChanged(); // signal of change
    emit this->statusChanged(); // signal of status change
}


void MidletFile::setIconPath(const QString path) {
    this->m_iconPath = path; // sets path
    emit this->iconSourceChanged(); // signal of change
    emit this->statusChanged(); // signal of status change
}


void MidletFile::saveJarFile(const QString path) const {
    QDir::root().mkpath(QFileInfo(path).dir().path()); // creates dir for file
    QFile::copy(this->m_jarPath, path);
}


void MidletFile::saveJadFile(const QString path) const {
    QDir::root().mkpath(QFileInfo(path).dir().path()); // creates dir for file
    QFile::copy(this->m_jadPath, path);
}


void MidletFile::saveIconFile(const QString path) const {
    QDir::root().mkpath(QFileInfo(path).dir().path()); // creates dir for file
    QImageReader imageReader(this->m_iconPath); // reader
    imageReader.setQuality(100); // bers quality
    imageReader.setBackgroundColor(QColor(0,0,0,0)); // transparent background
    QSize previewSize = imageReader.size(); // size of image in file
#if defined(Q_WS_MAEMO_5)
    previewSize.scale(64, 64, Qt::KeepAspectRatio);
#elif defined(Q_WS_HARMATTAN)
    previewSize.scale(80, 80, Qt::KeepAspectRatio);
#endif
    imageReader.setScaledSize(previewSize); // result image size
    imageReader.read().save(path, 0, 100); // saves to file
}


void MidletFile::parseJad(const QString &jadText) {
    this->m_name = QString::null;
    this->m_version = QString::null;
    this->m_mainClass = QString::null;
    QStringList lines = jadText.split('\n'); // get all lines of file
    foreach(const QString &line, lines) { // for all lines
        if (line.leftRef(8) == "MIDlet-1") { // line with midlet general
            QStringList elems = line.split(':')[1].trimmed().split(',');
            this->m_mainClass = elems[2];
        } else if (line.leftRef(11) == "MIDlet-Name") { // line with name
            this->m_name = line.split(':')[1].trimmed();
        } else if (line.leftRef(14) == "MIDlet-Version") { // line with version
            this->m_version = line.split(':')[1].trimmed();
        }
    }
    emit this->nameChanged();
    emit this->versionChanged();
    emit this->mainClassChanged();
}
