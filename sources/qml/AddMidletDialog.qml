/*******************************************************************************
*                                                                              *
*  Midlet installation dialog implementation.                                  *
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
import MidletFile 1.0

QKitDialog {
    id: addMidletDialog
    objectName: "AddMidletDialog"

    property MidletFile midletFile: MidletFile {}

    signal installToggled() // emits when install button clicked

    QKitDialogText {
        id: infoText

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 0.5 * font.pixelSize
        text: qsTr("Select .jar, .jad and icon files, than click on \"Install\".")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 0.04 * Math.min(parent.width, parent.height)
    }

    QKitNavListView { // menu view
        id: view

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: infoText.bottom
        anchors.topMargin: (addMidletDialog.height - infoText.height - cText.height - height) / 2
        width: 0.9 * Math.min(parent.width, parent.height)
        height: 0.6 * width
        spacing: 0.025 * width
        keyNavigationWraps: true

        model: VisualItemModel {
            AddMidletDialogElement {
                controllerSource: view
                width: view.width
                label: qsTr("JAR")
                source: addMidletDialog.midletFile.jarSource
                onButtonClicked: {
                    selectFilePage.action = "jar"
                    selectFilePage.mediaDir.nameFilters = ["*.jar"];
                    selectFilePage.open()
                }
            }
            AddMidletDialogElement {
                controllerSource: view
                width: view.width
                label: qsTr("JAD")
                source: addMidletDialog.midletFile.jadSource
                onButtonClicked: {
                    selectFilePage.action = "jad"
                    selectFilePage.mediaDir.nameFilters = ["*.jad"];
                    selectFilePage.open()
                }
            }
            AddMidletDialogElement {
                controllerSource: view
                width: view.width
                label: qsTr("Icon")
                source: addMidletDialog.midletFile.iconSource
                onButtonClicked: {
                    selectFilePage.action = "icon"
                    selectFilePage.mediaDir.nameFilters = ["*.png", "*.jpg", "*.gif", "*.bmp", "*.svg"];
                    selectFilePage.open()
                }
            }
            QKitDialogText {
                controllerSource: view
                width: view.width
                height: 0.1 * width
                font.pixelSize: 0.5 * height
                text: addMidletDialog.midletFile.name + " " + addMidletDialog.midletFile.version
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideLeft
            }
            QKitItem {
                controllerSource: view
                width: view.width
                height: 0.1 * width
                QKitDialogButton {
                    anchors.left: parent.left
                    anchors.leftMargin: 0.25 * view.width
                    anchors.right: parent.right
                    anchors.rightMargin: 0.25 * view.width
                    height: parent.height
                    text: qsTr("Install")
                    onClicked: addMidletDialog.installToggled()
                }
            }
        }
    }

    CText {id: cText}

    SelectFilePage {
        id: selectFilePage
        objectName: "SelectDialog"

        property string action: ""

        visible: false

        onVisibleChanged: if (!visible) addMidletDialog.forceActiveFocus()
        onSelectedFileChanged: {
            if (selectedFile != "") {
                if (action == "jar") {
                    addMidletDialog.midletFile.jarSource = selectedFile
                } else if (action == "jad") {
                    addMidletDialog.midletFile.jadSource = selectedFile
                } else if (action == "icon") {
                    addMidletDialog.midletFile.iconSource = selectedFile
                }
            }
        }
    }
}
