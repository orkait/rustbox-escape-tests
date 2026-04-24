use std::process::Command;

fn main() {
    loop {
        let _ = Command::new("/bin/true").spawn().unwrap();
    }
}
