use std::arch::asm;

const SIGXCPU: u64 = 24;
const SIG_IGN: u64 = 1;
const SYS_RT_SIGACTION: u64 = 13;

#[repr(C)]
struct Sigaction {
    sa_handler: u64,
    sa_flags: u64,
    sa_restorer: u64,
    sa_mask: [u64; 16],
}

fn main() {
    let act = Sigaction {
        sa_handler: SIG_IGN,
        sa_flags: 0,
        sa_restorer: 0,
        sa_mask: [0u64; 16],
    };

    unsafe {
        let ret: i64;
        asm!(
            "syscall",
            in("rax") SYS_RT_SIGACTION,
            in("rdi") SIGXCPU,
            in("rsi") &act as *const Sigaction as u64,
            in("rdx") 0u64,
            in("r10") 8u64,
            lateout("rax") ret,
            lateout("rcx") _,
            lateout("r11") _,
        );
        if ret == 0 {
            println!("ESCAPED");
        } else {
            panic!("rt_sigaction failed with {}", ret);
        }
    }

    loop {}
}
