/*******************************************************************************
*                                                                              *
*  Credits text implementation.                                                *
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

QKitDialogText {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    textFormat: Text.RichText
    horizontalAlignment: Text.AlignHCenter
    text: qsTr("by Kirill Chuvilin aka KiRiK for MaemoWorld.ru") + (application.isForStore ? "" : "<br />" + qsTr("This is free full-featured version of application. Please pay it at <a href=\""+ application.externalUrl('store') +"\" style=\"color:#FF0000\">Nokia Store</a> if you liked it or want it to be developed."))
    onLinkActivated: Qt.openUrlExternally(link)
    font.pixelSize: 0.035 * Math.min(parent.width, parent.height)
    wrapMode: Text.WordWrap
}
