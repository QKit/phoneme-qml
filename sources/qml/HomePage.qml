/*******************************************************************************
*                                                                              *
*  Page with installed midlets implementation.                                 *
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

import Qt 4.7
import "QKit"
import MidletRecord 1.0

QKitPage {
    id: homePage

    property alias midlets: midletsView.model
    signal addMidletToggled() // emits when add button clicked
    signal removeMidletToggled(int midletId) // emits when need to remove midlet

    toolbar: QKitToolbar {
        QKitToolbarAddButton { onClicked: homePage.addMidletToggled() }
        QKitToolbarMenuButton { onClicked: homePage.menuToggled() }
    }

    QKitNavGridView {
        id: midletsView

        anchors.fill: parent
        cellWidth: Math.min(1.0 / Math.round(width / 120), 0.5) * width - 0.5
        cellHeight: 1.1 * cellWidth
        keyNavigationWraps: false

        delegate: QKitItem {
            property MidletRecord midlet: midletsView.model[index]

            width: midletsView.cellWidth
            height: midletsView.cellHeight
            controllerSource: midletsView
            Item {
                anchors.fill: parent
                anchors.bottomMargin: 0.2 * parent.height
                Image {
                    anchors.centerIn: parent
                    source: midlet.iconSource
                }
            }
            Text {
                anchors.fill: parent
                anchors.topMargin: 0.75 * parent.height
                anchors.leftMargin: 0.05 * parent.width
                anchors.rightMargin: 0.05 * parent.width
                text: midlet.name + "\n" + midlet.version
                font.pixelSize: 0.5 * height
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
            Keys.onPressed: midlet.exec()
            MouseArea {
                anchors.fill: parent
                onClicked: midlet.exec()
                onPressAndHold: homePage.removeMidletToggled(midlet.id)
            }
        }
    }

}
