use local_ip_address::local_ip;
use std::fmt::format;
// To get own IPv4 addr
use std::time::Duration;
use std::{
    io::{prelude::*, stdin, BufReader},
    net::{SocketAddr, TcpStream},
};

mod stream_io;

const PORT: u16 = 1203;
const CHUNK_SIZE: usize = 1024;
fn main() {
    // Socket binding
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
        if !stream_io::write_stream(stream.try_clone().unwrap(), line.clone()) {
            println!("Server error!");
            return;
        }

        let message_words: Vec<_> = line.trim_end().trim_start().split_whitespace().collect();
        let command = message_words.first().copied();
        // let mut message = String::new();

        match command.as_deref() {
            // Download from server
            Some("download") => {
                let mut chunk = [0u8; CHUNK_SIZE];
                let mut buf = BufReader::new(&mut stream);

                loop {
                    match buf.read(&mut chunk) {
                        Err(error) => {
                            println!("Server error: {}", error);
                        }

                        _ => (),
                    };
                }
            }

            // Empty line
            None => continue,

            // All other commands
            _ => {
                let mut message = String::new();

                if !stream_io::read_stream(stream.try_clone().unwrap(), &mut message) {
                    println!("Server error!");
                    return;
                }

                println!("{}", message.as_str().trim());
            }
        }

        // Wait answer and read it
        // let mut message = String::new();

        // if !stream_io::read_stream(stream.try_clone().unwrap(), &mut message) {
        //     println!("Server error!");
        //     return;
        // }

        // Just write answer to the console
        // println!("{}", message.as_str().trim());
    }
}
