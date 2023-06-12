//
// Created by work on 6/11/23.
//

#ifndef DRIVER_DAEMON_IMX8MMDDR4EVK_CORE_H
#define DRIVER_DAEMON_IMX8MMDDR4EVK_CORE_H

namespace core {
    namespace types {
        typedef char                s8;
        typedef unsigned char       u8;
        typedef short              s16;
        typedef unsigned short     u16;
        typedef int                s32;
        typedef unsigned int       u32;
        typedef long long          s64;
        typedef unsigned long long u64;
        typedef void               emt;
        typedef bool               bit;
    }

    namespace interface_usb {
        namespace errors {
            const types::u32 connect_error        = 0x21;
            const types::u32 claim_error          = 0x22;
            const types::u32 disconnect_error     = 0x23;
            const types::u32 transfer_data_error  = 0x24;
            const types::u32 get_usb_device_error = 0x25;
        }
    }
}

#endif //DRIVER_DAEMON_IMX8MMDDR4EVK_CORE_H
