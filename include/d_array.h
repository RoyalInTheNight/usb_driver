//
// Created by work on 6/12/23.
//

#ifndef DRIVER_DAEMON_IMX8MMDDR4EVK_D_ARRAY_H
#define DRIVER_DAEMON_IMX8MMDDR4EVK_D_ARRAY_H

#include "memory_manage.h"
#include "core.h"

template<class __fT, class __sT,
         class _Allocator_line_1 = mem_alloc<__fT>,
         class _Allocator_line_2 = mem_alloc<__sT>> class d_array {
private:
    typedef core::types::u32 __Sz;
    typedef core::types::s32 __It;
    typedef d_array<__fT, __sT, _Allocator_line_1, _Allocator_line_2> array;

    _Allocator_line_1  line_1;
    _Allocator_line_2  line_2;
    mem_alloc<__It> reference;

    __fT  *first_line_array;
    __sT *second_line_array;

    __Sz   size_lines_array;
    __It          lst_error;
    __It       *ref_counter;

public:
    d_array(const array& cpy)
            : first_line_array{cpy.first_line_array}, second_line_array{cpy.second_line_array},
              size_lines_array{cpy.size_lines_array}, ref_counter{cpy.ref_counter} {
        ++(*ref_counter);
    }

    d_array(const __Sz size)
            : first_line_array{line_1.allocator(size)}, second_line_array{line_2.allocator(size)},
              size_lines_array{size}, ref_counter{reference.allocator(1)} {
        ++(*ref_counter);
    }

    d_array()
            : first_line_array{nullptr}, second_line_array{nullptr},
              size_lines_array{0}, ref_counter{reference.allocator(1)} {
        ++(*ref_counter);
    }

    inline __Sz size() const {return size_lines_array;}
    inline __Sz length() const {return size_lines_array <= 0 ? 0 : size_lines_array - 1;}
    inline __fT *get_first_line_data() const {return first_line_array;}
    inline __sT *get_second_line_data() const {return second_line_array;}
    inline __fT& at_first(__Sz pos = 0) {
        if (pos >= size_lines_array) {
            lst_error = 0x51;

            return (__fT&)__fT();
        }

        return (__fT&)*(first_line_array + pos);
    }

    inline __sT& at_second(__Sz pos = 0) {
        if (pos >= size_lines_array) {
            lst_error = 0x51;

            return (__sT&)__sT();
        }

        return (__sT&)*(second_line_array + pos);
    }

    void push_back(__fT& ft_line, __sT& st_line) {
        if (size_lines_array == 0) {
            first_line_array  = line_1.allocator(1);
            second_line_array = line_2.allocator(1);

            size_lines_array++;
        }

        else {
            first_line_array  = line_1.mem_resize(first_line_array, size_lines_array, size_lines_array + 1);
            second_line_array = line_2.mem_resize(second_line_array, size_lines_array,  ++size_lines_array);
        }

        *(first_line_array + length())  = ft_line;
        *(second_line_array + length()) = st_line;
    }

    void pop_back() {
        if (size_lines_array == 0)
            return;

        first_line_array  = line_1.mem_resize(first_line_array, size_lines_array, size_lines_array - 1);
        second_line_array = line_2.mem_resize(second_line_array, size_lines_array,  --size_lines_array);
    }

    ~d_array() {
        if (ref_counter) {
            --(*ref_counter);

            if (!(*ref_counter)) {
                if (first_line_array != nullptr &&
                    second_line_array != nullptr) {
                    delete[]  first_line_array;
                    delete[] second_line_array;
                }

                delete ref_counter;
            }
        }
    }
};

#endif //DRIVER_DAEMON_IMX8MMDDR4EVK_D_ARRAY_H
