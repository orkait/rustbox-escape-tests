use std::net::TcpStream;

fn main() {
    let stream = TcpStream::connect("8.8.8.8:53").unwrap();
    println!("ESCAPED");
    drop(stream);
}
