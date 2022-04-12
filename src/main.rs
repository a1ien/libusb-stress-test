use libusb1_sys as ffi;

fn main() {

    let th1 = std::thread::spawn(|| {
        let mut context: *mut ffi::libusb_context = std::ptr::null_mut();
        for i in 0..=1000 {
            match unsafe { ffi::libusb_init(&mut context) } {
                0 => (),
                err => panic!("Failed to init libusb on iteration {}: {}", i, err),
            }
            unsafe {
                ffi::libusb_exit(context);
            }
            context = std::ptr::null_mut();
        }
    });
    let th2 = std::thread::spawn(|| {
    let mut context: *mut ffi::libusb_context = std::ptr::null_mut();
    for i in 0..=1000 {
        match unsafe { ffi::libusb_init(&mut context) } {
            0 => (),
            err => panic!("Failed to init libusb on iteration {}: {}", i, err),
        }
        unsafe {
            ffi::libusb_exit(context);
        }
        context = std::ptr::null_mut();
        }
    });
    th1.join().unwrap();
    th2.join().unwrap();
}
