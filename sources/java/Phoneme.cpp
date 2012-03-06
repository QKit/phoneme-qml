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

#include "Phoneme.h"
#include <stdlib.h>
#include <QDir>
#include <QFile>
#include <QTextStream>

Phoneme* Phoneme::s_instance = 0; // no static insstance
QString Phoneme::s_binPath = "/opt/phoneme/bin";
QString Phoneme::s_midpPath = "/opt/phoneme/midp";
QString Phoneme::s_settingsPath = QDir::homePath() + "/.config/phoneme/user.conf";
QMap<QString, QString> Phoneme::s_settings; // settings


Phoneme* Phoneme::instance() {
    if (!Phoneme::s_instance) delete new Phoneme(); // creates static instance, if there was no it
    return Phoneme::s_instance;
}


Phoneme::Phoneme() {
    if (!Phoneme::s_instance) { // there was no static instance
        Phoneme::s_instance = this; // to prevent endless loop
        Phoneme::s_instance = new Phoneme(); // noew it just creates an object
        Phoneme::s_instance->loadSettings(); // load settings
    }
}


QString Phoneme::getExecMidletCommand(QString jarPath, QString jadPath, QString mainClass) const {
    QString command = Phoneme::s_binPath + "/cvm -Xmx12m -Dmicroedition.profiles=MIDP-2.1 -Dsun.midp.library.name=midp -Dsun.midp.home.path=" + Phoneme::s_midpPath + "/midp_linux_fb_gcc -Dcom.sun.midp.mainClass.name=com.sun.midp.main.CdcMIDletSuiteLoader sun.misc.MIDPLauncher -suitepath " + jarPath;
    if (!jadPath.isEmpty()) command += " -jadpath " + jadPath;
    if (!mainClass.isEmpty()) command += " -1 " + mainClass;
#if defined(Q_WS_MAEMO_5)
    return command;
#elif defined(Q_WS_HARMATTAN)
    return QString("/usr/bin/single-instance ") + command;
#endif
    return command;
//    return Phoneme::s_binPath + "/runmidlet " + jadPath;
}


const QString Phoneme::getSettingValue(QString key) const {
    return Phoneme::s_settings[key];
}


int Phoneme::execMidlet(QString jarPath, QString jadPath, QString mainClass) const {
    return system(this->getExecMidletCommand(jarPath, jadPath, mainClass).toLocal8Bit());
}


void Phoneme::setSettingValue(QString key, QString value) {
    Phoneme::s_settings[key] = value;
}


bool Phoneme::loadSettings() {
    // default settings
    Phoneme::s_settings["fullscreen"] = "true"; // settings: start in full screen
    Phoneme::s_settings["bitmapfont"] = "false"; // settings: use built-in bitmap font for faster text rendering
    Phoneme::s_settings["errorlog"] = "false"; // settings: redirect all console output to log files in MyDocs
    Phoneme::s_settings["sip"] = "true"; // settings: enable virtual keyboard
    // try to load
    QFile settingsFile(this->s_settingsPath); // settings file
    if (!settingsFile.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QTextStream settingsStream(&settingsFile);
    settingsStream.setCodec("UTF-8");
    QStringList settingsLines = settingsStream.readAll().split('\n'); // get all lines of file
    settingsFile.close();
    foreach(const QString &line, settingsLines) { // for all lines
        QStringList lineSplitted = line.split('='); // key=value
        if (lineSplitted.length() == 2) {
            QString key = lineSplitted[0].trimmed(); // key
            QString value = lineSplitted[1].trimmed(); // value
            this->setSettingValue(key, value);
        }
    }
    return true;
}


bool Phoneme::saveSettings() const {
    QFile settingsFile(this->s_settingsPath); // settings file
    QDir::root().mkpath(QFileInfo(this->s_settingsPath).dir().path()); // creates dir for file
    if (!settingsFile.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QTextStream settingsStream(&settingsFile);
    settingsStream.setCodec("UTF-8");
    settingsStream << "[General]\n";
    foreach (const QString &key, Phoneme::s_settings.keys()) { // for all settings
        settingsStream << key << "=" << Phoneme::s_settings[key] << "\n";
    }
    settingsFile.close();
    return true;
}
