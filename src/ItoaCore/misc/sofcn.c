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

#include "sofcn.h"
#include <linux/elf.h>
#include <string.h>

///////////////////////////////////////////////// soinfo_t

soinfo_t* get_first_so() {
    static soinfo_t* first_so=0;
    if (!first_so) {
        first_so=(soinfo_t*)dlopen("libdl.so",RTLD_NOW | RTLD_GLOBAL);
    }
    return first_so;
}

soinfo_t* find_so(const char* name) {
    soinfo_t* i=get_first_so();
    for (;i;i=i->next) {
        if (!strcmp(i->name,name)) {
            return i;
        }
    }
    return NULL;
}

// ///////////////////////////////////////////////// Dl_info

// int dladdr(const void * address,Dl_info * info) {
//     if (!address || !info) {
//         return 0;
//     }
//     soinfo_t* i=get_first_so();
//     for (;i;i=i->next) {
//         if ((unsigned)address>=i->base &&
//             (unsigned)address<(i->base+i->size))
//         {
//             info->dli_fname=i->name;
//             info->dli_fbase=(void*)i->base;
//             return 1;
//         }
//     }
//     return 0;
// }

/////////////////////////////////////////////////

