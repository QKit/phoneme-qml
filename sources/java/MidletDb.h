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

#ifndef _MidletDb_h_
#define _MidletDb_h_

#include <QSqlDatabase>
#include <QDir>
#include "DeclarativeList.h"

#include "MidletFile.h"
#include "MidletRecord.h"

class MidletRecord;

/*!
 * \brief Java midlet database.
 * \author KiRiK aka Kirill Chuvilin (kirik-ch.ru)
 */
class MidletDb : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString dirPath READ getDirPath WRITE setDirPath NOTIFY dirPathChanged) //!< absolute path to dir with thumbnail files
    Q_PROPERTY(QDeclarativeListProperty<MidletRecord> midlets READ getMidletsProperty NOTIFY midletsChanged) //!< installed midlets

public:
    /*!
     * \brief Constructor.
     * \param dirPath string with path path to directory with thumbnail files
     */
    explicit MidletDb(const QString dirPath = QDir::homePath() + "/.phoneME");

    /*!
     * \brief Destructor.
     */
    ~MidletDb();

    /*!
     * \brief Returns absolute path to directory with thumbnail files.
     * \return string with absolute path to directory with thumbnail files
     */
    QString getDirPath() const {return this->dir.absolutePath();}

    const QList<MidletRecord*> &getMidlets() const {return this->m_midlets;}
    QDeclarativeListProperty<MidletRecord> getMidletsProperty() {return DeclarativeList<MidletRecord>::generateProperty(this, &m_midlets, false, true);}

public slots:

    /*!
     * \brief Sets absolute path to directory with thumbnail files.
     * \param dirPath string with path to directory with thumbnail files
     */
    void setDirPath(const QString dirPath);

    /*!
     * \brief Adds midlet to base.
     * \return true if midlet was installed, false othewice
     * \param midletFile midlet description
     */
    bool addMidlet(const MidletFile &midletFile);

    /*!
     * \brief Adds midlet to base.
     * \return true if midlet was installed, false othewice
     * \param jarPath string with path to midlet .jar file
     * \param jadPath string with path to midlet .jad file
     * \param iconPath string with path to midlet icon file
     */
    bool addMidlet(const QString jarPath, QString jadPath, QString iconPath);

    /*!
     * \brief Adds midlet to base.
     * \return true if midlet was installed, false othewice
     * \param jarSource url to midlet .jar file
     * \param jadSource url to midlet .jad file
     * \param iconSource url to midlet icon file
     */
    bool addMidlet(const QUrl jarSource, QUrl jadSource, QUrl iconSource);

    /*!
     * \brief Adds midlet to base.
     * \return true if midlet was deinstalled, false othewice
     * \param id midlet record id
     */
    bool removeMidlet(const int id);

signals:
    /*!
     * Emits when dirPath ptoperty changes.
     */
    void dirPathChanged();

    /*!
     * Emits when midlets ptoperty changes.
     */
    void midletsChanged();

private:
    QSqlDatabase db; //!< database
    QDir dir; //!< to operate with thumbnails dir
    QList<MidletRecord*> m_midlets; //!< installed midlets

private slots:
    /*!
     * \brief Reasd midlet list from db.
     */
    void refreshMidlets();
};

#endif // _MidletDb_h_
