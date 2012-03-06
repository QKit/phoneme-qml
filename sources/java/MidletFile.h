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

#ifndef _MildetFile_h_
#define _MildetFile_h_

#include <QObject>
#include <QString>
#include <QUrl>

/*!
 * \brief Java midlet handler.
 * \author KiRiK aka Kirill Chuvilin (kirik-ch.ru)
 */
class MidletFile : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool status READ getStatus NOTIFY statusChanged) //!< resdy for install or not
    Q_PROPERTY(QUrl jarSource READ getJarSource WRITE setJarSource NOTIFY jarSourceChanged) //!< url to .jar file
    Q_PROPERTY(QUrl jadSource READ getJadSource WRITE setJadSource NOTIFY jadSourceChanged) //!< url to .jad file
    Q_PROPERTY(QUrl iconSource READ getIconSource WRITE setIconSource NOTIFY iconSourceChanged) //!< url to icon file
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged) //!< name of midlet
    Q_PROPERTY(QString version READ getVersion NOTIFY versionChanged) //!< version of midlet
    Q_PROPERTY(QString mainClass READ getMainClass NOTIFY mainClassChanged) //!< version of midlet

public:
    /*!
     * \brief Constructor.
     * \param jarPath path to .jar file
     * \param jadPath path to .jad file
     * \param iconPath path to icon file
     */
    explicit MidletFile(const QString jarPath = QString::null, const QString jadPath = QString::null, const QString iconPath = QString::null);

    /*!
     * \brief Constructor.
     * \param jarSource url to .jar file
     * \param jadSource url to .jad file
     * \param iconSource url to icon file
     */
    explicit MidletFile(const QUrl jarSource, const QUrl jadSource = QUrl(), const QUrl iconSource = QUrl());

    /*!
     * \brief Detects ready for install or not.
     * \return true if ready, else id not
     */
    bool getStatus() const;

    /*!
     * \brief Returns path to .jar file
     * \return string with path to file
     */
    QString getJarPath() const {return this->m_jarPath;}

    /*!
     * \brief Returns url to .jar file
     * \return url to file
     */
    QUrl getJarSource() const {return QUrl::fromLocalFile(this->getJarPath());}

    /*!
     * \brief Returns path to .jad file
     * \return string with path to file
     */
    QString getJadPath() const {return this->m_jadPath;}

    /*!
     * \brief Returns url to .jad file
     * \return url to file
     */
    QUrl getJadSource() const {return QUrl::fromLocalFile(this->getJadPath());}

    /*!
     * \brief Returns path to icon file
     * \return string with path to file
     */
    QString getIconPath() const {return this->m_iconPath;}

    /*!
     * \brief Returns url to icon file
     * \return url to file
     */
    QUrl getIconSource() const {return QUrl::fromLocalFile(this->getIconPath());}

    /*!
     * \brief Returns name of midlet
     * \return string with midlet name
     */
    QString getName() const {return this->m_name;}

    /*!
     * \brief Returns version of midlet
     * \return string with midlet version
     */
    QString getVersion() const {return this->m_version;}

    /*!
     * \brief Returns main class of midlet
     * \return string with main class name
     */
    QString getMainClass() const {return this->m_mainClass;}

public slots:
    /*!
     * \brief Sets path to .jar file.
     * \param string with path to file
     */
    void setJarPath(const QString path);

    /*!
     * \brief Sets url to .jar file.
     * \param url to file
     */
    void setJarSource(const QUrl source) {this->setJarPath(source.toLocalFile());}

    /*!
     * \brief Sets path to .jad file.
     * \param string with path to file
     */
    void setJadPath(const QString path);

    /*!
     * \brief Sets url to .jad file.
     * \param url to file
     */
    void setJadSource(const QUrl source) {this->setJadPath(source.toLocalFile());}

    /*!
     * \brief Sets path to icon file.
     * \param string with path to file
     */
    void setIconPath(const QString path);

    /*!
     * \brief Sets url to icon file.
     * \param url to file
     */
    void setIconSource(const QUrl source) {this->setIconPath(source.toLocalFile());}

    /*!
     * \brief Saves .jar file.
     * \param string with path to file
     */
    void saveJarFile(const QString path) const;

    /*!
     * \brief Saves .jad file.
     * \param string with path to file
     */
    void saveJadFile(const QString path) const;

    /*!
     * \brief Saves icon file.
     * \param string with path to file
     */
    void saveIconFile(const QString path) const;

signals:
    /*!
     * \brief Emited when status property changes.
     */
    void statusChanged();

    /*!
     * \brief Emited when jarPath property changes.
     */
    void jarSourceChanged();

    /*!
     * \brief Emited when jadPath property changes.
     */
    void jadSourceChanged();

    /*!
     * \brief Emited when iconPath property changes.
     */
    void iconSourceChanged();

    /*!
     * \brief Emited when name property changes.
     */
    void nameChanged();

    /*!
     * \brief Emited when version property changes.
     */
    void versionChanged();

    /*!
     * \brief Emited when mainClass property changes.
     */
    void mainClassChanged();

private:
    QString m_jarPath; //!< path to .jar file
    QString m_jadPath; //!< path to .jad file
    QString m_iconPath; //!< path to icon file
    QString m_name; //!< midlet name
    QString m_version; //!< midlet version
    QString m_mainClass; //!< midlet main class

    /*!
     * \brief Emited when name property changes.
     * \param jadText string with content of .jad file
     */
    void parseJad(const QString &jadText);
};

#endif // _MildetFile_h_
