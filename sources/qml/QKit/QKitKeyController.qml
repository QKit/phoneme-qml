/*******************************************************************************
*                                                                              *
*  Key settings item implementation.                                            *
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

Item {
    property int navMoveLeftKey: Qt.Key_Left // key for left moving in nav items
    property int navMoveRightKey: Qt.Key_Right // key for right moving in nav items
    property int navMoveUpKey: Qt.Key_Up // key for up moving in nav items
    property int navMoveDownKey: Qt.Key_Down // key for down moving in nav items

    property int buttonPressKey: Qt.Key_Select // key for button press

    property int dialogCloseKey: Qt.Key_Backspace // key for dialog close
    property int dialogButtonPressKey: buttonPressKey // key for dialog button press

    property int toolbarLeftButtonPressKey: Qt.Key_Context1 // key for left toolbar button
    property int toolbarRightButtonPressKey: Qt.Key_Context2 // key for right toolbar button
    property int toolbarButtonPressKey: buttonPressKey // key for toolbar button press

}
