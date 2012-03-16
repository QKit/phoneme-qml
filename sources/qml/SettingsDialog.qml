/*******************************************************************************
*                                                                              *
*  Phoneme settings dialog implementation.                                     *
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
import Phoneme 1.0

QKitDialog {
    id: settingsDialog
    objectName: "settingsDialog"

    property Phoneme phoneme; // Phoneme object

    property bool antialiasSettingValue // use anti-aliased fonts
    property bool bitmapfontSettingValue // use built-in bitmap font for faster text rendering
    property bool errorlogSettingValue // redirect all console output to log files in MyDocs
    property bool fullscreenSettingValue // start MIDlets in full screen
    property bool rotateSettingValue // rotate midlet 90 degrees
    property bool sipSettingValue // enable virtual keyboard

    function saveValues() { // save all settings values to file
        phoneme.setSettingValue("antialias", antialiasSettingValue ? "true" : "false");
        phoneme.setSettingValue("bitmapfont", bitmapfontSettingValue ? "true" : "false");
        phoneme.setSettingValue("errorlog", errorlogSettingValue ? "true" : "false");
        phoneme.setSettingValue("fullscreen", fullscreenSettingValue ? "true" : "false");
        phoneme.setSettingValue("rotate", rotateSettingValue ? "true" : "false");
        phoneme.setSettingValue("sip", sipSettingValue ? "true" : "false");
        phoneme.saveSettings();
        active = false;
    }

    function resetValues() { // reset all settings values to loaded from file
        antialiasSettingValue = phoneme.getSettingValue("antialias") === "true";
        bitmapfontSettingValue = phoneme.getSettingValue("bitmapfont") === "true";
        errorlogSettingValue = phoneme.getSettingValue("errorlog") === "true";
        fullscreenSettingValue = phoneme.getSettingValue("fullscreen") === "true";
        rotateSettingValue = phoneme.getSettingValue("rotate") === "true";
        sipSettingValue = phoneme.getSettingValue("sip") === "true";
    }

    onActiveChanged: if (active) resetValues();

    QKitNavListView { // menu view
        id: view

        property int bodyHeight: Math.min(settingsDialog.height - cText.height, childrenRect.height)

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: (settingsDialog.height - cText.height - bodyHeight) / 2
        anchors.bottom: cText.top
        anchors.bottomMargin: (settingsDialog.height - cText.height - bodyHeight) / 2
        width: 0.9 * Math.min(parent.width, parent.height)
        spacing: 0.03 * width
        keyNavigationWraps: true
        model: VisualItemModel {
            SettingsDialogElement {
                controllerSource: settingsDialog
                width: view.width
                label: qsTr("Use anti-aliased fonts")
                value: settingsDialog.antialiasSettingValue
                onButtonClicked: settingsDialog.antialiasSettingValue = !settingsDialog.antialiasSettingValue
            }
            SettingsDialogElement {
                controllerSource: settingsDialog
                width: view.width
                label: qsTr("Use built-in bitmap font for faster text rendering")
                value: settingsDialog.bitmapfontSettingValue
                onButtonClicked: settingsDialog.bitmapfontSettingValue = !settingsDialog.bitmapfontSettingValue
            }
            SettingsDialogElement {
                controllerSource: settingsDialog
                width: view.width
                label: qsTr("Redirect all console output to log files in MyDocs")
                value: settingsDialog.errorlogSettingValue
                onButtonClicked: settingsDialog.errorlogSettingValue = !settingsDialog.errorlogSettingValue
            }
            SettingsDialogElement {
                controllerSource: settingsDialog
                width: view.width
                label: qsTr("Start MIDlets in full screen")
                value: settingsDialog.fullscreenSettingValue
                onButtonClicked: settingsDialog.fullscreenSettingValue = !settingsDialog.fullscreenSettingValue
            }
            SettingsDialogElement {
                controllerSource: settingsDialog
                width: view.width
                label: qsTr("Rotate midlet 90 degrees")
                value: settingsDialog.rotateSettingValue
                onButtonClicked: settingsDialog.rotateSettingValue = !settingsDialog.rotateSettingValue
            }
            SettingsDialogElement {
                controllerSource: settingsDialog
                width: view.width
                label: qsTr("Enable virtual keyboard")
                value: settingsDialog.sipSettingValue
                onButtonClicked: settingsDialog.sipSettingValue = !settingsDialog.sipSettingValue
            }
            QKitItem {
                controllerSource: settingsDialog
                width: view.width
                height: 0.1 * view.width
                QKitDialogButton {
                    anchors.left: parent.left
                    width: 0.45 * parent.width
                    height: 0.1 * parent.width
                    text: qsTr("Save")
                    onClicked: settingsDialog.saveValues()
                }
                QKitDialogButton {
                    anchors.right: parent.right
                    width: 0.45 * parent.width
                    height: 0.1 * parent.width
                    text: qsTr("Reset")
                    onClicked: settingsDialog.resetValues()
                }
            }
        }
    }
    CText {id: cText}
}
