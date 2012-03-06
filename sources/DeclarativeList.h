/*******************************************************************************
*                                                                              *
*  Generator of QDeclarativeListProperty.                                      *
*                                                                              *
*  Copyright (C) 2011-2012 Kirill Chuvilin.                                    *
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

#ifndef _DeclarativeList_h_
#define _DeclarativeList_h_

#include <QDeclarativeListProperty>

template <typename T> class DeclarativeList {
public:
    /*
      Generates list property, based on QList object.
      object   - property owner
      list     - list container
      doAppend - append item or not
      doClear  - cliar data on destruction or not
    */
    static QDeclarativeListProperty<T> generateProperty(QObject* object, QList<T*>* list, bool doAppend = true, bool doClear = true) {
        return QDeclarativeListProperty<T>(
                    object,
                    list,
                    doAppend ? &DeclarativeList::listAppend : &DeclarativeList::listAppendNull,
                    &DeclarativeList::listCount,
                    &DeclarativeList::listAt,
                    doClear ? &DeclarativeList::listClear : &DeclarativeList::listClearNull
                );
    }

    /*
      Appends data onto list property.
    */
    static void listAppend(QDeclarativeListProperty<T>* property, T* item) {static_cast< QList<T*>* >(property->data)->append(item);}
    static void listAppendNull(QDeclarativeListProperty<T>* property, T* item) {Q_UNUSED(property); Q_UNUSED(item);}

    /*
      Returns number of items in list property.
    */
    static int listCount(QDeclarativeListProperty<T>* property) {return static_cast< QList<T*>* >(property->data)->size();}

    /*
      Retrieves item by index.
    */
    static T* listAt(QDeclarativeListProperty<T>* property, int index) {return static_cast< QList<T*>* >(property->data)->at(index);}

    /*
      Clears list property.
    */
    static void listClear(QDeclarativeListProperty<T>* property) {return static_cast< QList<T*>* >(property->data)->clear();}
    static void listClearNull(QDeclarativeListProperty<T>* property) {Q_UNUSED(property);}
};

#endif // _DeclarativeList_h_
