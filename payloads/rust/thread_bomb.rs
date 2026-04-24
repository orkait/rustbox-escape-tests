use std::thread;

fn main() {
    loop {
        thread::spawn(|| loop {});
    }
}
