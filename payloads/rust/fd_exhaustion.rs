use std::fs::File;

fn main() {
    let mut handles = Vec::new();
    loop {
        handles.push(File::open("/dev/null").unwrap());
    }
}
