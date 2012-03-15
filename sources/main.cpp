/*******************************************************************************
*                                                                              *
*  phoneME QML main source file.                                               *
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

#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include <QtDeclarative>

#include "mediafiles/MediaFile.h"
#include "mediafiles/MediaDir.h"

#include "java/Phoneme.h"
#include "java/MidletFile.h"
#include "java/MidletDb.h"

int main(int argc, char *argv[]) {
    QStringList consoleParams; // params from console
    for (int iArg = 1; iArg < argc; iArg++)
        consoleParams.append(QString(argv[iArg]));

    if (consoleParams.length() > 0 && consoleParams.at(0) == "--execmidlet") {
        if (consoleParams.length() > 1 && consoleParams.at(1) == "--id") {
            if (consoleParams.length() > 2) {
                int id = consoleParams.at(2).toInt();
                MidletDb midletDb;
                foreach (const MidletRecord* midletRecord, midletDb.getMidlets()) {
                    if (midletRecord->getId() == id) return midletRecord->exec();
                }
            }
        }
    }

    QApplication app(argc, argv);
    QmlApplicationViewer viewer;

    app.setApplicationName(app.trUtf8("phoneME QML"));
    viewer.setWindowTitle(app.trUtf8("phoneME QML"));

    qmlRegisterType<MediaFile>("MediaFile", 1, 0, "MediaFile");
    qmlRegisterType<MediaDir>("MediaDir", 1, 0, "MediaDir");
    qmlRegisterType<Phoneme>("Phoneme", 1, 0, "Phoneme");
    qmlRegisterType<MidletFile>("MidletFile", 1, 0, "MidletFile");
    qmlRegisterType<MidletRecord>("MidletRecord", 1, 0, "MidletRecord");
    qmlRegisterType<MidletDb>("MidletDb", 1, 0, "MidletDb");

#if defined(Q_WS_MAEMO_5)
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/Main_fremantle.qml"));
    viewer.show();
#elif defined(Q_WS_HARMATTAN)
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/Main_harmattan.qml"));
    viewer.showFullScreen();
#else
    viewer.setMainQmlFile(QLatin1String("qml/Main_desktop.qml"));
    viewer.show();
#endif
    return app.exec();
}
