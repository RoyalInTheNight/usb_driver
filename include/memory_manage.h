//
// Created by work on 6/11/23.
//

#ifndef DRIVER_DAEMON_IMX8MMDDR4EVK_MEMORY_MANAGE_H
#define DRIVER_DAEMON_IMX8MMDDR4EVK_MEMORY_MANAGE_H

#include "core.h"

template<class __Tp> class mem_alloc {
private:
    typedef __Tp *__Pt;

public:
    __Pt allocator(core::types::u32 size) {
        __Pt ptr = new __Tp[size];

        if (ptr == nullptr)
            return nullptr;

        return ptr;
    }

    __Pt mem_resize(__Pt ptr, core::types::u32 size, core::types::u32 new_size) {
        __Pt tmp = allocator(new_size);

        if (tmp == nullptr)
            return ptr;

        size = size > new_size ? new_size : size;

        if (size != 0) {
            for (core::types::u32 i = 0; i < size; i++)
                *(tmp + i) = *(ptr + i);

            delete[] ptr;
        }

        return tmp;
    }
};

#endif //DRIVER_DAEMON_IMX8MMDDR4EVK_MEMORY_MANAGE_H
