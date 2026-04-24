use std::fs;

fn main() {
    let content = fs::read_to_string("/proc/cpuinfo").unwrap();
    println!("ESCAPED");
    println!("{}", content);
}
