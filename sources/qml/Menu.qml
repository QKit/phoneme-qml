/*******************************************************************************
*                                                                              *
*  Menu item implementation.                                                   *
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

import "QKit"
import Qt 4.7

QKitMenu {
    id: menu
    objectName: "Menu"

    signal settingsToggled() // emits when settings button clicked

    QKitMenuElement { // goto website button
        text: application.isOnStoreQA ? qsTr("Back") : qsTr("Homepage")
        onClicked: if (!application.isOnStoreQA) Qt.openUrlExternally(qsTr("https://github.com/QKit/phoneME-QML/wiki"))
    }

    QKitMenuElement { // goto website button
        text: application.isOnStoreQA ? qsTr("Back") : qsTr("phoneME page")
        onClicked: if (!application.isOnStoreQA) Qt.openUrlExternally(qsTr("http://davy.preuveneers.be/phoneme/?q=node/34"))
    }

    QKitMenuElement { // goto website button
        text: qsTr("Settings")
        onClicked: menu.settingsToggled()
    }

    QKitMenuElement { // exit button
        text: qsTr("Quit")
        onClicked: Qt.quit()
    }

    children: [CText{}]
}
