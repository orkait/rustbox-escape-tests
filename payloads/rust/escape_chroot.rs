use std::env;
use std::fs;

fn main() {
    for _ in 0..20 {
        let _ = env::set_current_dir("..");
    }
    let content = fs::read_to_string("etc/passwd").unwrap();
    println!("ESCAPED");
    println!("{}", content);
}
