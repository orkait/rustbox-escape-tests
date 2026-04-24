use std::fs;

fn main() {
    let content = fs::read_to_string("/etc/shadow").unwrap();
    println!("ESCAPED");
    println!("{}", content);
}
