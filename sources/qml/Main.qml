/*******************************************************************************
*                                                                              *
*  Main application item implementation.                                       *
*                                                                              *
*  Copyright (C) 2012 Kirill Chuvilin.                                         *
*  All rights reserved.                                                        *
*  Contact: Kirill Chuvilin (kirill.chuvilin@gmail.com, kirik-ch.ru)           *
*                                                                              *
*  This file is part of the phoneME QML project.                               *
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

import Qt 4.7
import "QKit"
import MidletDb 1.0
import Phoneme 1.0

QKitApplication {
    id: application

    property MidletDb midletDb: MidletDb {}
    property Phoneme phoneme: Phoneme {}

    property bool isForStore: false
    property string version: "1.0.4"

    function externalUrl(link) {
        return "http://scripts.kirik-ch.ru/appredirect.php?app=phoneme-qml&link=" + link +"&platform=" + os + "&version=" + version + (isForStore ? "&isforstore=true" : "");
    }

    logController: LogController { }

    HomePage {
        id: homePage
        objectName: "HomePage"
        midlets: midletDb.midlets
        onMenuToggled: menu.active = true
        onAddMidletToggled: addMidletDialog.active = true
        onRemoveMidletToggled: midletDb.removeMidlet(midletId)
    }

    Menu {
        id: menu
        onClosed: homePage.forceActiveFocus()
        onSettingsToggled: settingsDialog.active = true;
    }

    AddMidletDialog {
        id: addMidletDialog
        onClosed: homePage.forceActiveFocus()
        onInstallToggled: {
            if (midletDb.addMidlet(addMidletDialog.midletFile.jarSource, addMidletDialog.midletFile.jadSource, addMidletDialog.midletFile.iconSource)) active = false;
        }
    }

    SettingsDialog {
        id: settingsDialog
        phoneme: application.phoneme;
        onClosed: homePage.forceActiveFocus()
    }

    // todo: why does focus goes to menuview?
    Component.onCompleted: forceActiveFocus()
}
