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

#ifndef _SOFCN_INCLUDED_
#define _SOFCN_INCLUDED_

#include <dlfcn.h>
#include <stdint.h>

__BEGIN_DECLS

///////////////////////////////////////////////// soinfo

#define SOINFO_NAME_LEN 128

typedef struct soinfo {
    const char name[SOINFO_NAME_LEN];
    void *phdr;
    int phnum;
    unsigned entry;
    unsigned base;
    unsigned size;

    int ba_index;

    unsigned *dynamic;

    unsigned wrprotect_start;
    unsigned wrprotect_end;

    struct soinfo *next;
   
    // more ...
} soinfo_t;

soinfo_t* get_first_so();
soinfo_t* find_so(const char* name);

// ///////////////////////////////////////////////// Dl_info

// typedef struct Dl_info {
//     const char* dli_fname;
//     void* dli_fbase;
// } Dl_info;

// int dladdr(const void* address, Dl_info* info);

/////////////////////////////////////////////////

__END_DECLS

#endif // _SOFCN_INCLUDED_

