/*******************************************************************************
*                                                                              *
*  GridView vith key navigation item implementation.                           *
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

QKitGridView {
    id: navGridView
    objectName: "QKitNavGridView"

    property int moveLeftKey: keyController.navMoveLeftKey
    property int moveRightKey: keyController.navMoveRightKey
    property int moveUpKey: keyController.navMoveUpKey
    property int moveDownKey: keyController.navMoveDownKey

    function highlightCurrentItem() {
        if (currentItem && highlightFollowsCurrentItem) { // if there is selected item
            currentItem.focus = true // focus on it
        } else { // if no selected item
            invisible.focus = true // reset focus from previous item
            navGridView.focus = true // set focus to view
        }
    }

    Item { id: invisible; visible: false } // to reset focus

    highlight: navController.highlight // component to use as the highlight
    // todo: remove declaration
    property bool highlightFollowsCurrentItem: navController.highlightFollowsCurrentItem // whether the highlight is managed by the view
//    highlightMoveSpeed: navController.highlightMoveSpeed // highlight move animation speed
    highlightMoveDuration: navController.highlightMoveDuration // highlight move animation duration
//    highlightResizeSpeed: navController.highlightResizeSpeed // highlight resize animation speed
//    highlightResizeDuration: navController.highlightResizeDuration // highlight resize animation duration
    keyNavigationWraps: navController.keyNavigationWraps // whether the list wraps key navigation

    currentIndex: -1 // no selected item

    onHighlightFollowsCurrentItemChanged: highlightCurrentItem()
    onCurrentItemChanged: highlightCurrentItem()
    onModelChanged: currentIndex = -1

    Keys.onLeftPressed: navController.moveCurrentIndexByKey(navGridView, event) // standart left key handler
    Keys.onRightPressed: navController.moveCurrentIndexByKey(navGridView, event) // standart right key handler
    Keys.onUpPressed: navController.moveCurrentIndexByKey(navGridView, event) // standart up key handler
    Keys.onDownPressed: navController.moveCurrentIndexByKey(navGridView, event) // standart down key handler
    Keys.onPressed: navController.moveCurrentIndexByKey(navGridView, event) // unstandart keys handler
}
