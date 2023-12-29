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
    // Greeting from server
    let greeting_message = format!(
        "Connection established! Server IP: {}\n",
        local_ip().unwrap()
    );
    stream.write_all(greeting_message.as_bytes()).unwrap();

    println!("New connection: {}", stream.peer_addr().unwrap());
    let mut message = String::from("");

    loop {
        message.clear();
        let mut buf_reader = BufReader::new(&mut stream);
        buf_reader
            .read_line(&mut message)
            .expect("There must be line");

        // Trim any unnecessary info from line (spacing, newline symbols, etc)
        let message = message.trim();

        let message_by_words: Vec<_> = message.split_whitespace().collect();
        let command = message_by_words.first();

        match command {
            Some(&"echo") => {
                let out: Vec<_> = message_by_words.iter().skip(1).copied().collect();
                for word in out {
                    let echo_output = format!("{word} ");
                    stream.write_all(echo_output.as_bytes()).unwrap();
                }
            }

            Some(&"time") => {
                let time = Local::now().to_rfc2822();
                stream.write_all(time.as_bytes()).unwrap();
            }

            Some(&"exit") => {
                stream.write_all("Connection closed!".as_bytes()).unwrap();
                break;
            }

            None => {
                println!("Zero bytes message");
            }

            _ => {
                stream.write_all("Not a command!".as_bytes()).unwrap();
            }
        }
        stream.write_all("\n".as_bytes()).unwrap();
    }

    println!("Connection closed");
}
