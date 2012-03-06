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

#ifndef _MidletRecord_h_
#define _MidletRecord_h_

#include "MidletDb.h"
#include <QObject>
#include <QString>
#include <QUrl>

class MidletDb;

/*!
 * \brief Java midlet database record.
 * \author KiRiK aka Kirill Chuvilin (kirik-ch.ru)
 */
class MidletRecord : public QObject {
    Q_OBJECT

    Q_PROPERTY(int id READ getId NOTIFY idChanged) //!< midlet id in base
    Q_PROPERTY(QString name READ getName CONSTANT) //!< midlet name
    Q_PROPERTY(QString version READ getVersion CONSTANT) //!< midlet version
    Q_PROPERTY(QString mainClass READ getMainClass CONSTANT) //!< midlet mainClass
    Q_PROPERTY(QUrl iconSource READ getIconSource CONSTANT) //!< url to midlet icon

public:
    explicit MidletRecord() {}

    /*!
     * \brief Constructor.
     * \param midletDb midlet base
     * \param name string with midlet name
     * \param vetsion string with midlet version
     * \param mainClass string with midlet main class
     */
    explicit MidletRecord(MidletDb &midletDb, const QString name, const QString version, const QString mainClass);

    /*!
     * \brief Constructor.
     * \param midletDb midlet base
     * \param sqlQuery database query object
     */
    explicit MidletRecord(MidletDb &midletDb, const QSqlQuery &sqlQuery);

    /*!
     * \brief Returns id in base.
     * \return id
     */
    int getId() const {return this->m_id;}

    /*!
     * \brief Returns name.
     * \return string with name
     */
    const QString& getName() const {return this->m_name;}

    /*!
     * \brief Returns version.
     * \return string with version
     */
    const QString& getVersion() const {return this->m_version;}

    /*!
     * \brief Returns main class.
     * \return string with main class name
     */
    const QString& getMainClass() const {return this->m_mainClass;}

    /*!
     * \brief Returns name of midlet .jar file.
     * \return string with name of midlet .jar file
     */
    QString getJarFileName() const {return QString("midlet") + QString::number(this->m_id) + QString(".jar");}

    /*!
     * \brief Returns path to midlet .jar file.
     * \return string with absolute path to midlet .jar file
     */
    QString getJarPath() const;

    /*!
     * \brief Returns url to midlet .jar file
     * \return url to midlet .jar file
     */
    const QUrl getJarSource() const {return QUrl::fromLocalFile(this->getJarPath());}

    /*!
     * \brief Returns name of midlet .jad file.
     * \return string with name of midlet .jad file
     */
    QString getJadFileName() const {return QString("midlet") + QString::number(this->m_id) + QString(".jad");}

    /*!
     * \brief Returns path to midlet .jad file.
     * \return string with absolute path to midlet .jad file
     */
    QString getJadPath() const;

    /*!
     * \brief Returns url to midlet .jad file
     * \return url to midlet .jad file
     */
    const QUrl getJadSource() const {return QUrl::fromLocalFile(this->getJadPath());}

    /*!
     * \brief Returns name of midlet icon file.
     * \return string with name of midlet icon file
     */
    QString getIconFileName() const {return QString("phoneme-midlet") + QString::number(this->m_id) + QString(".png");}

    /*!
     * \brief Returns path to midlet icon file.
     * \return string with absolute path to midlet icon file
     */
    QString getIconPath() const;

    /*!
     * \brief Returns url to midlet icon file
     * \return url to midlet icon file
     */
    const QUrl getIconSource() const {return QUrl::fromLocalFile(this->getIconPath());}

    /*!
     * \brief Returns name of midlet desktop file.
     * \return string with name of midlet desktop file
     */
    QString getDesktopFileName() const {return QString("phoneme-midlet") + QString::number(this->m_id) + QString(".desktop");}

    /*!
     * \brief Returns path to midlet desktop file.
     * \return string with absolute path to midlet desktop file
     */
    QString getDesktopFilePath() const;

    /*!
     * \brief Returns system command to launch midlet.
     * \return string with command text
     */
    QString getExecCommand() const;

public slots:
    /*!
     * \brief Adds midlet to base if it is not there.
     * \return true if was added, false otherwice
     * \param sqlQuery database query object
     */
    bool addToBase(QSqlQuery &sqlQuery);

    /*!
     * \brief Removes midlet from base if it is there.
     * \return true if was removed, false otherwice
     * \param sqlQuery database query object
     */
    bool removeFromBase(QSqlQuery &sqlQuery);

    /*!
     * \brief Saves .desktop file for midlet.
     */
    void saveMidletDesktopFile() const;

    /*!
     * \brief Starts the midlet.
     * \return result of start
     */
    int exec() const;

signals:
    /*!
     * Emits when id ptoperty changes.
     */
    void idChanged();

private:
    MidletDb* m_midletDb; //!< pointer to midlet base
    int m_id; //!< midlet id in base
    QString m_name; //!< midlet name
    QString m_version; //!< midlet version
    QString m_mainClass; //!< midlet main class
};

#endif // _MidletRecord_h_
