/*******************************************************************************
*                                                                              *
*  Phoneme settings dialog implementation.                                     *
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
import Phoneme 1.0

QKitDialog {
    id: settingsDialog
    objectName: "settingsDialog"

    property Phoneme phoneme; // Phoneme object

    property bool bitmapfontSettingValue // use built-in bitmap font for faster text rendering
    property bool errorlogSettingValue // redirect all console output to log files in MyDocs
    property bool fullscreenSettingValue // start MIDlets in full screen
    property bool sipSettingValue // enable virtual keyboard

    function saveValues() { // save all settings values to file
        phoneme.setSettingValue("bitmapfont", bitmapfontSettingValue ? "true" : "false");
        phoneme.setSettingValue("errorlog", errorlogSettingValue ? "true" : "false");
        phoneme.setSettingValue("fullscreen", fullscreenSettingValue ? "true" : "false");
        phoneme.setSettingValue("sip", sipSettingValue ? "true" : "false");
        phoneme.saveSettings();
        active = false;
    }

    function resetValues() { // reset all settings values to loaded from file
        bitmapfontSettingValue = phoneme.getSettingValue("bitmapfont") === "true";
        errorlogSettingValue = phoneme.getSettingValue("errorlog") === "true";
        fullscreenSettingValue = phoneme.getSettingValue("fullscreen") === "true";
        sipSettingValue = phoneme.getSettingValue("sip") === "true";
    }

    onActiveChanged: if (active) resetValues();

    QKitNavListView { // menu view
        id: view
        property int __elementWidth: 0.9 * Math.min(parent.width, parent.height)
        property int __buttonWidth: 0.2 * Math.min(parent.width, parent.height)
        property int __buttonHeight: 0.5 * __buttonWidth

        anchors.centerIn: parent
        width: __elementWidth
        height: Math.min(parent.height, childrenRect.height)
        spacing: 0.5 * __buttonHeight
        keyNavigationWraps: true
        model: VisualItemModel {
            QKitRow {
                controllerSource: settingsDialog
                width: view.__elementWidth
                spacing: 0.05 * view.__elementWidth
                QKitDialogText {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - parent.spacing - view.__buttonWidth
                    font.pixelSize: 0.5 * view.__buttonHeight
                    text: qsTr("Use built-in bitmap font for faster text rendering")
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                }
                QKitDialogButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: view.__buttonWidth
                    height: view.__buttonHeight
                    text: settingsDialog.bitmapfontSettingValue
                    onClicked: settingsDialog.bitmapfontSettingValue = !settingsDialog.bitmapfontSettingValue
                }
            }
            QKitRow {
                controllerSource: settingsDialog
                width: view.__elementWidth
                spacing: 0.05 * view.__elementWidth
                QKitDialogText {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - parent.spacing - view.__buttonWidth
                    font.pixelSize: 0.5 * view.__buttonHeight
                    text: qsTr("Redirect all console output to log files in MyDocs")
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                }
                QKitDialogButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: view.__buttonWidth
                    height: view.__buttonHeight
                    text: settingsDialog.errorlogSettingValue
                    onClicked: settingsDialog.errorlogSettingValue = !settingsDialog.errorlogSettingValue
                }
            }
            QKitRow {
                controllerSource: settingsDialog
                width: view.__elementWidth
                spacing: 0.05 * view.__elementWidth
                QKitDialogText {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - parent.spacing - view.__buttonWidth
                    font.pixelSize: 0.5 * view.__buttonHeight
                    text: qsTr("Start MIDlets in full screen")
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                }
                QKitDialogButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: view.__buttonWidth
                    height: view.__buttonHeight
                    text: settingsDialog.fullscreenSettingValue
                    onClicked: settingsDialog.fullscreenSettingValue = !settingsDialog.fullscreenSettingValue
                }
            }
            QKitRow {
                controllerSource: settingsDialog
                width: view.__elementWidth
                spacing: 0.05 * view.__elementWidth
                QKitDialogText {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - parent.spacing - view.__buttonWidth
                    font.pixelSize: 0.5 * view.__buttonHeight
                    text: qsTr("Enable virtual keyboard")
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                }
                QKitDialogButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: view.__buttonWidth
                    height: view.__buttonHeight
                    text: settingsDialog.sipSettingValue
                    onClicked: settingsDialog.sipSettingValue = !settingsDialog.sipSettingValue
                }
            }
            QKitRow {
                controllerSource: settingsDialog
                width: view.__elementWidth
                height: view.__buttonHeight
                spacing: 0.05 * view.__elementWidth
                QKitDialogButton {
                    controllerSource: settingsDialog
                    width: 0.5 * (view.__elementWidth - parent.spacing)
                    height: view.__buttonHeight
                    text: qsTr("Save")
                    onClicked: settingsDialog.saveValues()
                }
                QKitDialogButton {
                    controllerSource: settingsDialog
                    width: 0.5 * (view.__elementWidth - parent.spacing)
                    height: view.__buttonHeight
                    text: qsTr("Reset")
                    onClicked: settingsDialog.resetValues()
                }
            }
        }
    }

    CText {}
}
