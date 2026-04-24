use std::fs;

fn main() {
    let entries = fs::read_dir("/sys").unwrap();
    for entry in entries {
        let entry = entry.unwrap();
        println!("{}", entry.path().display());
    }
    println!("ESCAPED");
}
