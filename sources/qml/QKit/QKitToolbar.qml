/*******************************************************************************
*                                                                              *
*  Toolbar item implementation.                                                *
*                                                                              *
*  Copyright (C) 2011-2012 Kirill Chuvilin.                                    *
*  All rights reserved.                                                        *
*  Contact: Kirill Chuvilin (kirill.chuvilin@gmail.com, kirik-ch.ru)           *
*                                                                              *
*  This file is part of the QKit project.                                      *
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

QKitRectangle {
    id: toolbar
    objectName: "QKitToolbar"

    default property alias content: toolbarContent.children // toolbar content
    // UI properties
    property int   animationDuration: uiController.toolbarAnimationDuration
    property int   borderWidth: uiController.toolbarBorderWidth
    property color borderColor: uiController.toolbarBorderColor
    // key properties
    property int leftButtonPressKey: keyController.toolbarLeftButtonPressKey
    property int rightButtonPressKey: keyController.toolbarRightButtonPressKey

    function keyPressedEvent(event) { // key event handler
        switch (event.key) {
        case leftButtonPressKey:
            if (__local.leftButton)
                __local.leftButton.pressByKey(event);
            break;
        case rightButtonPressKey:
            if (__local.rightButton)
                __local.rightButton.pressByKey(event);
            break;
        default:
            return;
        }
        event.accepted = true;
    }

    active: true // initially opened
    anchors.fill: parent
    z: 1 // to view ower other
    color: uiController.toolbarBackgroundColor

    Keys.onPressed: keyPressedEvent(event);

    property Item __local: Item { // local variables
        property variant leftButton: 0
        property variant rightButton: 0
        states: [
            State {
                name: "opened desktop"
                when: toolbar.active && uiController.isDesktopOs
                PropertyChanges {
                    target: toolbar
                    visible: true
                    focus: true
                    anchors.bottomMargin: toolbar.parent.height - 24
                }
                PropertyChanges {
                    target: toolbarContent
                    flow: Grid.LeftToRight
                    columns: toolbarContent.nChildren
                }
                PropertyChanges {
                    target: toolbarBorder
                    anchors.topMargin: toolbar.height - toolbar.borderWidth
                }
            },
            State {
                name: "closed desktop"
                when: !toolbar.active && uiController.isDesktopOs
                PropertyChanges {
                    target: toolbar
                    visible: false
                    anchors.bottomMargin: toolbar.parent.height
                }
                PropertyChanges {
                    target: toolbar.parent
                    focus: true
                }
            },
            State {
                name: "opened landskape"
                when: toolbar.active && !uiController.isDesktopOs && uiController.isLandscapeOrientation
                PropertyChanges {
                    target: toolbar
                    visible: true
                    focus: true
                    anchors.leftMargin: toolbar.parent.width - toolbar.parent.height / 6
                }
                PropertyChanges {
                    target: __local
                    leftButton: toolbarContent.nChildren > 0 ? toolbarContent.children[toolbarContent.nChildren - 1] : 0
                    rightButton: toolbarContent.nChildren > 0 ? toolbarContent.children[0] : 0
                }
                PropertyChanges {
                    target: toolbarContent
                    flow: Grid.TopToBottom
                    rows: toolbarContent.nChildren
                }
                PropertyChanges {
                    target: toolbarBorder
                    anchors.rightMargin: toolbar.width - toolbar.borderWidth
                }
            },
            State {
                name: "closed landskape"
                when: !toolbar.active && !uiController.isDesktopOs && uiController.isLandscapeOrientation
                PropertyChanges {
                    target: toolbar
                    visible: false
                    anchors.leftMargin: toolbar.parent.width
                }
                PropertyChanges {
                    target: toolbar.parent
                    focus: true
                }
            },
            State {
                name: "opened portrait"
                when: toolbar.active && !uiController.isDesktopOs && uiController.isPortraitOrientation
                PropertyChanges {
                    target: toolbar
                    visible: true
                    focus: true
                    anchors.topMargin: toolbar.parent.height - toolbar.parent.width / 8
                }
                PropertyChanges {
                    target: __local
                    leftButton: toolbarContent.nChildren > 0 ? toolbarContent.children[0] : 0
                    rightButton: toolbarContent.nChildren > 0 ? toolbarContent.children[toolbarContent.nChildren - 1] : 0
                }
                PropertyChanges {
                    target: toolbarContent
                    flow: Grid.LeftToRight
                    columns: toolbarContent.nChildren
                }
                PropertyChanges {
                    target: toolbarBorder
                    anchors.bottomMargin: toolbar.height - toolbar.borderWidth
                }
            },
            State {
                name: "closed portrait"
                when: !toolbar.active && !uiController.isDesktopOs && uiController.isPortraitOrientation
                PropertyChanges {
                    target: toolbar
                    visible: false
                    anchors.topMargin: toolbar.parent.height
                }
                PropertyChanges {
                    target: toolbar.parent
                    focus: true
                }
            }
        ]

        transitions: [
            Transition {
                from: "closed desktop"
                to: "opened desktop"
                SequentialAnimation {
                    PropertyAnimation {
                        target:  toolbar
                        property: "visible"
                        duration: 0
                    }
                    PropertyAnimation {
                        target:  toolbar
                        property: "anchors.bottomMargin"
                        duration: toolbar.animationDuration
                    }
                }
            },
            Transition {
                from: "opened desktop"
                to: "closed desktop"
                SequentialAnimation {
                    PropertyAnimation {
                        target:  toolbar
                        property: "anchors.bottomMargin"
                        duration: toolbar.animationDuration
                    }
                    PropertyAnimation {
                        target:  toolbar
                        property: "visible"
                        duration: 0
                    }
                }
            },
            Transition {
                from: "closed landskape"
                to: "opened landskape"
                SequentialAnimation {
                    PropertyAnimation {
                        target:  toolbar
                        property: "visible"
                        duration: 0
                    }
                    PropertyAnimation {
                        target:  toolbar
                        property: "anchors.leftMargin"
                        duration: toolbar.animationDuration
                    }
                }
            },
            Transition {
                from: "opened landskape"
                to: "closed landskape"
                SequentialAnimation {
                    PropertyAnimation {
                        target:  toolbar
                        property: "anchors.leftMargin"
                        duration: toolbar.animationDuration
                    }
                    PropertyAnimation {
                        target:  toolbar
                        property: "visible"
                        duration: 0
                    }
                }
            },
            Transition {
                from: "closed portrait"
                to: "opened portrait"
                SequentialAnimation {
                    PropertyAnimation {
                        target:  toolbar
                        property: "visible"
                        duration: 0
                    }
                    PropertyAnimation {
                        target:  toolbar
                        property: "anchors.topMargin"
                        duration: toolbar.animationDuration
                    }
                }
            },
            Transition {
                from: "opened portrait"
                to: "closed portrait"
                SequentialAnimation {
                    PropertyAnimation {
                        target:  toolbar
                        property: "anchors.topMargin"
                        duration: toolbar.animationDuration
                    }
                    PropertyAnimation {
                        target:  toolbar
                        property: "visible"
                        duration: 0
                    }
                }
            }
        ]
    }

    QKitGrid {
        id: toolbarContent
        objectName: toolbar.objectName + ":Content"

        property int nChildren: 0 // childrent number

        anchors.fill: parent
        anchors.margins: 0.1 * Math.min(toolbar.width, toolbar.height);
        spacing: anchors.margins
        onChildrenChanged: {
            for (nChildren = 0; children[nChildren]; nChildren++); // count all children
        }
    }

    Rectangle {
        id: toolbarBorder
        anchors.fill: parent
        color: toolbar.borderColor
    }
}
