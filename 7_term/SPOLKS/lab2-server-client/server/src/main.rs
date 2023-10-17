use chrono::prelude::*;
use local_ip_address::local_ip;
use std::char::from_digit;
use std::fs;

use std::{
    io::{prelude::*, BufReader},
    net::{SocketAddr, TcpListener, TcpStream},
};

const PORT: u16 = 1203;
#[allow(dead_code)]
struct BreakerBuff {
    load_buff: Vec<String>,
    pos: u32,
    ip: SocketAddr,
    is_pending: bool,
}

#[allow(unused_variables, unused_mut, unused_assignments)]
fn main() {
    println!("Your address: {}:{}", local_ip().unwrap(), PORT);
    let addr = SocketAddr::new(local_ip().expect("You must have some IP"), PORT);

    let listener = TcpListener::bind(addr).unwrap();

    println!("Server is up!");
    let mut buff = BreakerBuff {
        load_buff: Vec::new(),
        pos: 0,
        ip: addr,
        is_pending: false,
    };
    for stream in listener.incoming() {
        let stream = stream.unwrap();
        buff.ip = stream.peer_addr().unwrap().clone();

        handle_connection(stream, &mut buff);
    }
}

// TODO: Delete permission
#[allow(unused_variables, unused_mut, unused_assignments)]

fn handle_connection(mut stream: TcpStream, buff: &mut BreakerBuff) {
    println!("New connection: {}", stream.peer_addr().unwrap());

    if buff.ip.ip() != stream.peer_addr().unwrap().ip() {
        buff.ip = stream.peer_addr().unwrap();
        buff.is_pending = false;
    }

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

            Some("upload") => {
                let path = dirs::home_dir().unwrap().join("upload.txt");
            }

            // Download from server to client
            Some("download") => {
                let path = dirs::home_dir().unwrap().join("download.txt");

                let content = String::from_utf8(fs::read(path.clone()).unwrap()).unwrap();
                let chunks = content
                    .chars()
                    .collect::<Vec<char>>()
                    .chunks(10)
                    .map(|c| c.iter().collect::<String>())
                    .collect::<Vec<String>>();
                buff.load_buff = chunks;
                buff.pos = 0;

                for i in 0..buff.load_buff.len() {
                    stream.write_all(buff.load_buff[i].as_bytes()).unwrap();

                    // Wait for acknowledgment after transmitting
                    let mut ack_message = String::new();
                    let mut ack = BufReader::new(&mut stream);
                    ack.read_line(&mut ack_message).expect("ACK not sended!");

                    if ack_message == "ACK" {
                        buff.pos += 1;
                    }
                }
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

    // If connection closed by client during file transmitting
    if buff.pos != buff.load_buff.len() as u32 {
        buff.is_pending = true;
    }
    println!("Connection closed");
}
