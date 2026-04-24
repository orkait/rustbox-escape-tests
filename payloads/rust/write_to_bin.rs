use std::fs;

fn main() {
    fs::write("/bin/evil", "pwned").unwrap();
    println!("ESCAPED");
}
