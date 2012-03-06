/*******************************************************************************
*                                                                              *
*  PhoneME interactor implementation.                                          *
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

#ifndef _Phoneme_h_
#define _Phoneme_h_

#include <QObject>
#include <QString>
#include <QMap>

/*!
 * \brief Java midlet handler.
 * \author KiRiK aka Kirill Chuvilin (kirik-ch.ru)
 */
class Phoneme : public QObject {
    Q_OBJECT

public:
    /*!
     * \brief Returns static instance of class.
     * \return pointer to static instance object
     */
    static Phoneme* instance();

    /*!
     * \brief Constructor.
     */
    Phoneme();

    /*!
     * \brief Returns system command to launch midlet.
     * \return string with command text
     * \param jarPath string with path to midlets .jar file
     * \param jarPath string with path to midlets .jad file
     * \param jarPath string with name of midlets main class
     */
    QString getExecMidletCommand(QString jarPath, QString jadPath = QString::null, QString mainClass = QString::null) const;

    /*!
     * \brief Returns setting value.
     * \return string with value
     * \param key string with setting key
     */
    Q_INVOKABLE const QString getSettingValue(QString key) const;

public slots:
    /*!
     * \brief Launchs a midlet.
     * \return result of launch
     * \param jarPath string with path to midlets .jar file
     * \param jarPath string with path to midlets .jad file
     * \param jarPath string with name of midlets main class
     */
    int execMidlet(QString jarPath, QString jadPath = QString::null, QString mainClass = QString::null) const;

    /*!
     * \brief Sets setting value.
     * \param key string with setting key
     * \param value string with value
     */
    void setSettingValue(QString key, QString value);

    /*!
     * \brief Loads settings.
     * \return true, if the download is successful, false otherwise
     */
    bool loadSettings();

    /*!
     * \brief Saves settings.
     * \return true, if the save is successful, false otherwise
     */
    bool saveSettings() const;

private:
    static Phoneme* s_instance; //!< instance of object
    static QString s_binPath; //!< phoneme binaries path
    static QString s_midpPath; //!< phoneme midlets path
    static QString s_settingsPath; //!< phoneme settings file path
    static QMap<QString, QString> s_settings; //!< settings
};

#endif // _Phoneme_h_
