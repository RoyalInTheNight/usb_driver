//
// Created by work on 6/11/23.
//

#ifndef DRIVER_DAEMON_IMX8MMDDR4EVK_USB_DRIVER_H
#define DRIVER_DAEMON_IMX8MMDDR4EVK_USB_DRIVER_H

#include <libusb-1.0/libusb.h>
#include "memory_manage.h"
#include "d_array.h"
#include "core.h"

namespace daemon {
    class usb_mx8mmddr4evk {
    private:
        libusb_context *   m_ctx;
        libusb_device     **list;

        core::types::u32 lst_err;
        core::types::u32 strlen(const core::types::s8 *);

    public:
        usb_mx8mmddr4evk(); // init

        core::types::bit connect_to_device();
        core::types::emt disconnect_from_device();

        core::types::emt data_upload_mode(const core::types::emt *, core::types::u32, core::types::u32); // D+ realise
        d_array<core::types::u16, core::types::u16>& get_usb_device_id();

        core::types::u32 lst_error_ret();

        libusb_device_handle* m_usb_handler;

        ~usb_mx8mmddr4evk();
    };
}

#endif //DRIVER_DAEMON_IMX8MMDDR4EVK_USB_DRIVER_H
