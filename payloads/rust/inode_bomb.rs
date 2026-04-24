use std::fs::File;

fn main() {
    for i in 0..100_000 {
        File::create(format!("/tmp/inode_{}", i)).unwrap();
    }
    println!("ESCAPED");
}
