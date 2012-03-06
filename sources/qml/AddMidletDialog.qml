/*******************************************************************************
*                                                                              *
*  Midlet installation dialog implementation.                                  *
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
import MidletFile 1.0

QKitDialog {
    id: addMidletDialog
    objectName: "AddMidletDialog"

    property MidletFile midletFile: MidletFile {}

    signal installToggled() // emits when install button clicked

    QKitDialogText {
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

        property int __elementWidth: 0.9 * Math.min(addMidletDialog.width, addMidletDialog.height)
        property int __buttonWidth: 0.2 * Math.min(addMidletDialog.width, addMidletDialog.height)
        property int __buttonHeight: 0.5 * __buttonWidth

        anchors.centerIn: parent
        width: __elementWidth
        height: Math.min(parent.height, childrenRect.height)
        spacing: 0.5 * __buttonHeight
        keyNavigationWraps: true
        model: VisualItemModel {
            QKitRow {
                controllerSource: addMidletDialog
                width: view.__elementWidth
                spacing: 0.05 * view.__elementWidth
                QKitDialogButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: view.__buttonWidth
                    height: view.__buttonHeight
                    text: qsTr("JAR")
                    onClicked: {
                        selectFilePage.action = "jar"
                        selectFilePage.mediaDir.nameFilters = ["*.jar"];
                        selectFilePage.open()
                    }
                }
                QKitDialogText {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - parent.spacing - view.__buttonWidth
                    font.pixelSize: 0.5 * view.__buttonHeight
                    clip: true
                    text: addMidletDialog.midletFile.jarSource != "file:" ? addMidletDialog.midletFile.jarSource : "..."
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideLeft
                }
            }
            QKitRow {
                controllerSource: addMidletDialog
                width: view.__elementWidth
                spacing: 0.05 * view.__elementWidth
                QKitDialogButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: view.__buttonWidth
                    height: view.__buttonHeight
                    text: qsTr("JAD")
                    onClicked: {
                        selectFilePage.action = "jad";
                        selectFilePage.mediaDir.nameFilters = ["*.jad"];
                        selectFilePage.open();
                    }
                }
                QKitDialogText {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - parent.spacing - view.__buttonWidth
                    font.pixelSize: 0.5 * view.__buttonHeight
                    clip: true
                    text: addMidletDialog.midletFile.jadSource != "file:" ? addMidletDialog.midletFile.jadSource : "..."
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideLeft
                }
            }
            QKitRow {
                controllerSource: addMidletDialog
                width: view.__elementWidth
                spacing: 0.05 * view.__elementWidth
                QKitDialogButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: view.__buttonWidth
                    height: view.__buttonHeight
                    text: qsTr("Icon")
                    onClicked: {
                        selectFilePage.action = "icon"
                        selectFilePage.mediaDir.nameFilters = ["*.png", "*.jpg", "*.gif", "*.bmp", "*.svg"];
                        selectFilePage.open()
                    }
                }
                QKitDialogText {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - parent.spacing - view.__buttonWidth
                    font.pixelSize: 0.5 * view.__buttonHeight
                    clip: true
                    text: addMidletDialog.midletFile.iconSource != "file:" ? addMidletDialog.midletFile.iconSource : "..."
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideLeft
                }
            }
            QKitDialogText {
                controllerSource: addMidletDialog
                anchors.horizontalCenter: parent.horizontalCenter
                width: view.__elementWidth
                font.pixelSize: 0.5 * view.__buttonHeight
                text: addMidletDialog.midletFile.name + " " + addMidletDialog.midletFile.version
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideLeft
            }
            QKitDialogButton {
                controllerSource: addMidletDialog
                anchors.horizontalCenter: parent.horizontalCenter
                width: 0.5 * view.__elementWidth
                height: view.__buttonHeight
                text: qsTr("Install")
                onClicked: addMidletDialog.installToggled()
            }
        }
    }

    CText {}

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
