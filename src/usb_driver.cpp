//
// Created by work on 6/11/23.
//
#include "../include/usb_driver.h"

daemon::usb_mx8mmddr4evk::usb_mx8mmddr4evk() {
    libusb_init(&m_ctx);

    #ifdef CY_VID_PID
        libusb_set_option(m_ctx, LIBUSB_OPTION_USE_USBDK);
    #endif // CY_VID_PID

    libusb_set_option(m_ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_DEBUG);

    m_usb_handler = 0;
}

daemon::usb_mx8mmddr4evk::~usb_mx8mmddr4evk() {
    disconnect_from_device();

    libusb_exit(m_ctx);
}

core::types::u32 daemon::usb_mx8mmddr4evk::strlen(const core::types::s8 *str) {
    const core::types::s8 *s;

    for (s = str; *s; s++);
    return s - str;
}

core::types::bit daemon::usb_mx8mmddr4evk::connect_to_device() {
    m_usb_handler = libusb_open_device_with_vid_pid(m_ctx, 0x1234, 0x0005);

    if (m_usb_handler == 0) {
        lst_err = core::interface_usb::errors::connect_error;

        return false;
    }

    core::types::s32 res = libusb_claim_interface(m_usb_handler, 0);

    if (res != 0)
        lst_err = core::interface_usb::errors::claim_error;

    return true;
}

core::types::emt daemon::usb_mx8mmddr4evk::disconnect_from_device() {
    if (m_usb_handler != 0) {
        libusb_release_interface(m_usb_handler, 0);
        libusb_close(m_usb_handler);

        m_usb_handler = 0;
    }

    else
        lst_err = core::interface_usb::errors::disconnect_error;
}

core::types::emt daemon::usb_mx8mmddr4evk::data_upload_mode(const core::types::emt *__data,
                                                            core::types::u32 size,
                                                            core::types::u32 timeout) {
    if (m_usb_handler == 0)
        lst_err = core::interface_usb::errors::connect_error;

    core::types::bit end_read = false;
    core::types::s32 actual_size =  0;

    core::types::u32 result = libusb_bulk_transfer(m_usb_handler, 0x81,
                                                   (core::types::u8 *)__data, size,
                                                   &actual_size, timeout);

    if (result != 0) {
        lst_err = core::interface_usb::errors::transfer_data_error;

        return;
    }
}

d_array<core::types::u16, core::types::u16>& daemon::usb_mx8mmddr4evk::get_usb_device_id() {
    if (m_usb_handler == 0)
        lst_err = core::interface_usb::errors::connect_error;

    d_array<core::types::u16, core::types::u16> pid_vid_device;

    libusb_device *dev;
    libusb_device_descriptor desc = {0};

    libusb_get_device_list(m_ctx, &list);

    core::types::u32 result = 0;

    for (core::types::u32 idx = 0; list[idx] != 0; idx++) {
        result = libusb_get_device_descriptor(dev, &desc);
        dev    = list[idx];

        if (result == 0) {
            lst_err = core::interface_usb::errors::get_usb_device_error;

            return (d_array<core::types::u16, core::types::u16>&)pid_vid_device;
        }

        pid_vid_device.push_back(desc.idVendor, desc.idProduct);
    }

    return (d_array<core::types::u16, core::types::u16>&)pid_vid_device;
}

core::types::u32 daemon::usb_mx8mmddr4evk::lst_error_ret() {
    return lst_err;
}