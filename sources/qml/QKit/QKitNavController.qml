/*******************************************************************************
*                                                                              *
*  Key navigation controller item implementation.                              *
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
    property Component highlight // component to use as the highlight
    property bool highlightFollowsCurrentItem: false // whether the highlight is managed by the view
    property real highlightMoveSpeed: 400 // highlight move animation speed
    property int  highlightMoveDuration: -1 // highlight move animation duration
    property real highlightResizeSpeed: 400 // highlight resize animation speed
    property int  highlightResizeDuration: -1 // highlight resize animation duration
    property bool keyNavigationWraps: false // whether the list wraps key navigation

    // changes navItem's current item, according to key event
    function moveCurrentIndexByKey(navItem, event) {
        switch (event.key) {
        case navItem.moveLeftKey:
            navItem.highlightFollowsCurrentItem = true
            navItem.moveCurrentIndexLeft()
            break
        case navItem.moveRightKey:
            navItem.highlightFollowsCurrentItem = true
            navItem.moveCurrentIndexRight()
            break
        case navItem.moveUpKey:
            navItem.highlightFollowsCurrentItem = true
            navItem.moveCurrentIndexUp()
            break
        case navItem.moveDownKey:
            navItem.highlightFollowsCurrentItem = true
            navItem.moveCurrentIndexDown()
            break
        default: return // to not accept event
        }
        event.accepted = true
    }
}
