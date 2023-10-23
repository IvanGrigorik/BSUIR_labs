use chrono::prelude::*;
use local_ip_address::local_ip;
use std::fs;

use std::ops::Deref;
use std::path::PathBuf;
use std::{
    io::{prelude::*},
    net::{SocketAddr, TcpListener, TcpStream},
};

mod stream_io;

const PORT: u16 = 1203;
const CHUNK_SIZE: usize = 1024;

#[allow(dead_code)]
struct BreakerBuff {
    // load_buff: Vec<String>,
    load_buff: Vec<Vec<u8>>,
    pos: usize,
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

// Function to expand path to absolute, if start with tilde
fn expand_home(dir: PathBuf, expand: String) -> PathBuf {
    let mut path = dir.clone();
    path.clear();
    path = dirs::home_dir().unwrap();
    let mut x = path.into_os_string();
    x.push(expand.trim());
    x.into()
}

// TODO: Delete permission
#[allow(unused_variables, unused_mut, unused_assignments)]
fn handle_connection(mut stream: TcpStream, buff: &mut BreakerBuff) {
    println!("New connection: {}", stream.peer_addr().unwrap());

    // If new client connect
    if buff.ip.ip() != stream.peer_addr().unwrap().ip() {
        buff.ip = stream.peer_addr().unwrap();
        buff.is_pending = false;
    }

    loop {
        let mut message = String::new();
        if !stream_io::read_stream(stream.try_clone().unwrap(), &mut message) || message.is_empty()
        {
            break;
        }

        let message = message.trim_end().trim_start();
        let message_by_words: Vec<_> = message.split_whitespace().collect();
        let command = message_by_words.first().copied();

        match command.as_deref() {
            Some("echo") => {
                let mut echo_data = message_by_words[1..].join(" ");
                echo_data.push('\n');
                if !stream_io::write_stream(stream.try_clone().unwrap(), echo_data.clone()) {
                    return;
                }
            }

            Some("time") => {
                let mut time = Local::now().to_rfc2822();
                time.push('\n');
                if !stream_io::write_stream(stream.try_clone().unwrap(), time.clone()) {
                    return;
                }
            }

            Some("exit") => {
                if !stream_io::write_stream(
                    stream.try_clone().unwrap(),
                    "Connection closed\n".to_string(),
                ) {
                    return;
                }
                break;
            }

            Some("upload") => {
                let path = dirs::home_dir().unwrap().join("upload.txt");
            }

            // Download from server to client
            Some("download") => {
                // Get path from client request
                let path_str = message_by_words[1];
                let mut path = PathBuf::from(path_str.trim());
                if path.starts_with("~") {
                    path = expand_home(path, path_str[1..].to_string())
                }
                if !path.exists() {
                    if !stream_io::write_stream(
                        stream.try_clone().unwrap(),
                        "Error: File does not exist!\n".to_string(),
                    ) {
                        return;
                    }
                    continue;
                }

                // Read content from file and divide it by chunks
                let mut content = fs::read(path.clone()).unwrap();
                let mut chunks: Vec<Vec<u8>> =
                    content.chunks(CHUNK_SIZE).map(|mut s| s.into()).collect();

                buff.load_buff = chunks;
                if !buff.is_pending {
                    buff.pos = 0;
                }

                // Start or resume downloading
                while buff.pos != buff.load_buff.len() {
                    match stream.write_all(buff.load_buff[buff.pos].as_ref()) {
                        Err(error) => {
                            println!("Pipe is broken! Error: {}", error);
                            return;
                        }
                        _ => (),
                    }

                    // TODO: Check lines from 162 to 178
                    // Wait for acknowledgment from client after transmitting
                    let mut ack_message = String::new();
                    if !stream_io::read_stream(stream.try_clone().unwrap(), &mut ack_message) {
                        buff.is_pending = true;
                        return;
                    }

                    // Check is it right ACK
                    if ack_message.trim() == format!("ACK{}", buff.pos) {
                        buff.pos += 1;
                    }
                }

                stream.write_all("File sended!".as_bytes()).unwrap();
                println!("File sended");

                ////todo: delete this code, if the section above works fine
                // let content = String::from_utf8(fs::read(path.clone()).unwrap())
                //     .expect("File must have content!");
                // let chunks = content
                //     .chars()
                //     .collect::<Vec<char>>()
                //     .chunks(chunk_size)
                //     .map(|c| c.iter().collect::<String>())
                //     .collect::<Vec<String>>();

                // Set up buffer
                // buff.load_buff = chunks;
                // if !buff.is_pending {
                //     buff.pos = 0;
                // }

                // Retry to download or initialize downloading
                // while buff.pos != buff.load_buff.len() {
                //     // Write one chink of the file
                //     if !stream_io::write_stream(
                //         stream.try_clone().unwrap(),
                //         buff.load_buff[buff.pos as usize].clone(),
                //     ) {
                //         buff.is_pending = true;
                //         return;
                //     }

                //     // Wait for acknowledgment from client after transmitting
                //     let mut ack_message = String::new();

                //     let mut ack = BufReader::new(&mut stream);
                //     if !stream_io::read_stream(stream.try_clone().unwrap(), &mut ack_message) {
                //         buff.is_pending = true;
                //         return;
                //     }

                //     // Check is it right ACK
                //     if ack_message.trim() == format!("ACK{}", buff.pos) {
                //         buff.pos += 1;
                //     }
                // }
                // stream.write_all("File sended!".as_bytes()).unwrap();
                // println!("File sended");
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
    if buff.pos != buff.load_buff.len() {
        buff.is_pending = true;
    }
    println!("Connection closed");
}
