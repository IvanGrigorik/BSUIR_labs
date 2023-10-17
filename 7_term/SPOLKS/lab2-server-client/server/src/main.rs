use chrono::prelude::*;
use local_ip_address::local_ip; // To get own IPv4 addr
use std::{
    io::{prelude::*, BufReader},
    net::{SocketAddr, TcpListener, TcpStream},
};

const PORT: u16 = 1203;

fn main() {
    println!("Your address: {}:{}", local_ip().unwrap(), PORT);
    let addr = SocketAddr::new(local_ip().expect("You must have some IP"), PORT);

    let listener = TcpListener::bind(addr).unwrap();

    println!("Server is up!");
    for stream in listener.incoming() {
        let stream = stream.unwrap();
        handle_connection(stream);
    }
}

fn handle_connection(mut stream: TcpStream) {
    println!("New connection: {}", stream.peer_addr().unwrap());

    loop {
        let mut message = String::new();
        let mut buf_reader = BufReader::new(&mut stream);
        buf_reader
            .read_line(&mut message)
            .expect("There must be line");

        // Trim any unnecessary info from line (spacing, newline symbols, etc)
        if message.is_empty() {
            break;
        }

        let message = message.trim();
        let message_by_words: Vec<_> = message.split_whitespace().collect();
        let command = message_by_words.first().copied();

        match command.as_deref() {
            Some("echo") => {
                let mut echo_data = message_by_words[1..].join(" ");
                echo_data.push('\n');
                stream.write_all(echo_data.as_bytes()).unwrap();
            }

            Some("time") => {
                let mut time = Local::now().to_rfc2822();
                time.push('\n');
                stream.write_all(time.as_bytes()).unwrap();
            }

            Some("exit") => {
                stream.write_all("Connection closed!\n".as_bytes()).unwrap();
                break;
            }

            None => {
                println!("Zero bytes message");
            }

            _ => {
                println!("{}", message);
                stream.write_all("Not a command!\n".as_bytes()).unwrap();
            }
        }
    }

    println!("Connection closed");
}
