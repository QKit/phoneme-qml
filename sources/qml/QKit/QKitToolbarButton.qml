/*******************************************************************************
*                                                                              *
*  Button item for toolbars implementation.                                    *
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

QKitButton {
    id: button
    objectName: "QKitToolbarButton"

    width: uiController.isDesktopOs ? height : parent.flow === Grid.LeftToRight ? (parent.width - (parent.nChildren - 1) * parent.spacing) / parent.nChildren : parent.width
    height: parent.flow === Grid.LeftToRight ? parent.height : (parent.height - (parent.nChildren - 1) * parent.spacing) / parent.nChildren
    radius: 0.3 * height
    borderWidth: uiController.toolbarButtonBorderWidth
    smooth: uiController.toolbarButtonSmooth
    backgroundColor: uiController.toolbarButtonBackgroundColor // background color
    backgroundColorDimmed: uiController.toolbarButtonBackgroundColorDimmed // background color when button is pressed
    backgroundColorSelected: uiController.toolbarButtonBackgroundColorSelected // background color when button is selected
    borderColor: uiController.toolbarButtonBorderColor // border color
    borderColorDimmed: uiController.toolbarButtonBorderColorDimmed // border color when button is pressed
    borderColorSelected: uiController.toolbarButtonBorderColorSelected // border color when button is selected
    textColor: uiController.toolbarButtonTextColor // text color
    textColorDimmed: uiController.toolbarButtonTextColorDimmed // text color when button is pressed
    textColorSelected: uiController.toolbarButtonTextColorSelected // text color when button is selected
    mouseHoverEnabled: uiController.mouseHoverEnabled // handle mouse hover or not
    // key properties
    pressKey: keyController.toolbarButtonPressKey // key for press
}
