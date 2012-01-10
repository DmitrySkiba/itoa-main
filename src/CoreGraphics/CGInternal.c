/*
 * Copyright (C) 2011 Dmitry Skiba
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CGInternal.h"
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////

static OSSpinLock _CGRegisterClassLock=OS_SPINLOCK_INIT;

__private_extern__
CFTypeID _CGRegisterObjectClass(CFTypeID* typeID,const CFRuntimeClass* class) {
    OSSpinLockLock(&_CGRegisterClassLock);
    {
        if (*typeID==_kCFRuntimeNotATypeID) {
            *typeID=_CFRuntimeRegisterClass(class);
        }
    }
    OSSpinLockUnlock(&_CGRegisterClassLock);
    return *typeID;
}
