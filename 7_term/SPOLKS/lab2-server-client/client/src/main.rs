use chrono::prelude::*;
use local_ip_address::local_ip; // To get own IPv4 addr
use std::{
    io::{prelude::*, stdin, BufReader},
    net::{IpAddr, Ipv4Addr, SocketAddr, TcpStream},
    ops::Deref,
    str::FromStr,
};

const PORT: u16 = 1203;
fn main() {
    // Socket binding
    IpAddr::V4(Ipv4Addr::from_str("192.168.1.35").unwrap());
    let addr = SocketAddr::new(local_ip().expect("You must have some IP"), PORT);

    match TcpStream::connect(addr) {
        Ok(stream) => {
            handle_connection(stream);
        }

        Err(e) => {
            println!("Failed to connect: {}", e);
        }
    }
    println!("Terminated.");
}

fn handle_connection(mut stream: TcpStream) {
    loop {
        // Read line and write it to the socket
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
        let mut line = line.trim().to_string();
        line.push('\n');
        stream.write(line.as_bytes()).expect("msg sent");

        // Wait answer and read it
        let mut message = String::new();
        let mut buf_reader = BufReader::new(&mut stream);
        buf_reader
            .read_line(&mut message)
            .expect("There must be line");

        // Just write answer to the console
        println!("{}", message.as_str());
    }
}
