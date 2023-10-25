use local_ip_address::local_ip;
use std::fs::{File, OpenOptions};
use std::path::PathBuf;
use std::{
    io::{prelude::*, stdin, BufReader},
    net::{SocketAddr, TcpStream},
};

mod nets_io;

const PORT: u16 = 1203;
const CHUNK_SIZE: usize = 1024;
fn main() {
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

fn expand_home(dir: std::path::PathBuf, expand: String) -> std::path::PathBuf {
    let mut path = dir.clone();
    path.clear();
    path = dirs::home_dir().unwrap();
    let mut x = path.into_os_string();
    x.push(expand.trim());
    x.into()
}

fn handle_connection(mut stream: TcpStream)  {
    stream
        .set_read_timeout(Some(std::time::Duration::new(20, 0)))
        .expect("set_read_timeout call failed");
    stream
    .set_write_timeout(Some(std::time::Duration::new(20, 0)))
    .expect("set_read_timeout call failed");

    loop {
        // Read line and write it to the socket
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
        let mut line = line.trim().to_string();
        line.push('\n');
        if !nets_io::write_stream(stream.try_clone().unwrap(), line.clone()) {
            println!("Server error!");
            return;
        }

        let message_words: Vec<_> = line.trim_end().trim_start().split_whitespace().collect();
        let command = message_words.first().copied();

        // Same thing in server
        if message_words.len() < 2 && (command == Some("download") || command == Some("upload")) {
            continue;
        }

        match command.as_deref() {
            // Upload to the server
            Some("upload") => {
                let path_str = message_words[1];

                let mut path = PathBuf::from(path_str.trim());
                if path.starts_with("~") {
                    path = expand_home(path, path_str[1..].to_string())
                }

                if !path.exists() {
                    if !nets_io::write_stream(
                        stream.try_clone().unwrap(),
                        "File does not exist\n".to_string(),
                    ) {
                        return;
                    }
                    println!("File does no exist!");
                    continue;
                } else {
                    if !nets_io::write_stream(
                        stream.try_clone().unwrap(),
                        "Initiate file transfer\n".to_string(),
                    ) {
                        return;
                    }
                }

                // Get file length at server
                let mut pos_msg = String::new();
                if !nets_io::read_stream(stream.try_clone().unwrap(), &mut pos_msg) {
                    continue;
                }

                let content = std::fs::read(path.clone()).unwrap();
                let chunks: Vec<Vec<u8>> = content.chunks(CHUNK_SIZE).map(|s| s.into()).collect();

                // Calculate how much bytes we need to upload and how much at the server rn
                let mut pos = pos_msg.trim().parse::<usize>().unwrap() / 1024; // <---------------------------
                let total_bytes = content.len();
                let mut transferred_bytes = pos * CHUNK_SIZE;

                // Send file status: uploaded or not
                if pos_msg.trim().parse::<usize>().unwrap() == total_bytes {
                    if !nets_io::write_stream(stream.try_clone().unwrap(), "SENDED\n".to_string()) {
                        return;
                    }
                    println!("File already on the server!");
                    continue;
                } else {
                    if !nets_io::write_stream(
                        stream.try_clone().unwrap(),
                        "NOT_SENDED\n".to_string(),
                    ) {
                        return;
                    }
                }

                while transferred_bytes < total_bytes {
                    match stream.write_all(chunks[pos].as_ref()) {
                        Err(error) => {
                            println!("Pipe is broken! Error: {}", error);
                            return;
                        }
                        _ => (),
                    }
                    stream.flush().unwrap();

                    // Wait for acknowledgment from server after transmitting
                    let mut ack_message = String::new();
                    if !nets_io::read_stream(stream.try_clone().unwrap(), &mut ack_message) {
                        return;
                    }

                    // Check is it right ACK
                    if ack_message.trim() == format!("ACK{}", pos) {
                        transferred_bytes += chunks[pos].len();
                    } else {
                        continue;
                    }

                    if !nets_io::write_urg(
                        stream.try_clone().unwrap(),
                        format!("{:0>10}{:0>10}\n", transferred_bytes, total_bytes),
                    ) {
                        continue;
                    }

                    pos += 1;
                }

                // Get "uploaded" message from the server
                let mut uploaded_msg = String::new();
                if !nets_io::read_stream(stream.try_clone().unwrap(), &mut uploaded_msg) {
                    continue;
                }
                println!("{}", uploaded_msg);
            }

            // Download from server
            Some("download") => {
                // Check for file existence on the server
                let mut file_exist = String::new();
                if !nets_io::read_stream(stream.try_clone().unwrap(), &mut file_exist) {
                    continue;
                }

                println!("{}", file_exist);
                if file_exist.trim() == "File does not exist" {
                    continue;
                }

                let path_str = message_words[1];
                let file = path_str.split('/').last().unwrap();
                let path = PathBuf::from("downloaded_files/".to_string() + file.trim());

                // Ack to send ack message
                let mut ack_number = 0;
                if !path.exists() {
                    // If file not created - create it
                    File::create(path.clone()).unwrap();
                }
                let file_len = std::fs::read(path.clone()).unwrap().len();

                if file_len != 0 {
                    // Else - check last known position to send right ACK
                    ack_number = file_len / CHUNK_SIZE - 1;
                }

                // Create file to write our data
                let mut out_file = OpenOptions::new()
                    .write(true)
                    .append(true)
                    .open(path.clone())
                    .unwrap();

                let mut chunk = [0u8; CHUNK_SIZE];
                let mut buf = BufReader::new(stream.try_clone().unwrap());

                // Previous acknowledgment (0, if new downloading)
                let mut prev: usize = ack_number * CHUNK_SIZE;
                loop {
                    match buf.read(&mut chunk) {
                        Err(error) => {
                            println!("Server error: {}", error);
                        }
                        _ => {}
                    };

                    if !nets_io::write_stream(
                        stream.try_clone().unwrap(),
                        format!("ACK{}\n", ack_number),
                    ) {
                        return;
                    }

                    // Get "urgent" data
                    let mut urg_str = String::new();
                    if !nets_io::read_urg(stream.try_clone().unwrap(), &mut urg_str) {
                        return;
                    }

                    let (current, total) = urg_str.trim().split_at(10);
                    println!("{} / {}", current, total);

                    if file_len == total.parse().unwrap() {
                        println!("File is already downloaded!");
                        let mut fictive_msg = String::new();
                        if !nets_io::read_stream(stream.try_clone().unwrap(), &mut fictive_msg) {
                            return;
                        }
                        break;
                    }

                    // Check data
                    if chunk.len() != 0 {
                        let message = String::from_utf8(chunk.to_vec()).unwrap();
                        let mut idx: usize = CHUNK_SIZE;
                        if total.parse::<usize>().unwrap() < CHUNK_SIZE {
                            idx = total.parse().unwrap();
                        }
                        if current.parse::<usize>().unwrap() != 0 {
                            idx = current.parse::<usize>().unwrap() - prev;
                        }
                        // Check if message already in file, if renew downloading
                        if file_len < current.parse().unwrap() {
                            out_file.write(&message.as_bytes()[..idx]).unwrap();
                        }
                        prev = current.parse().unwrap();
                    }

                    if total == current {
                        break;
                    }

                    ack_number += 1;
                }

                // Send ACK that file downloaded
                if !nets_io::write_stream(stream.try_clone().unwrap(), "ACKSEND\n".to_string()) {
                    return;
                }

                // File send msg
                let mut sended_msg = String::new();
                if !nets_io::read_stream(stream.try_clone().unwrap(), &mut sended_msg) {
                    return;
                }

                println!("\n{}", sended_msg.trim());
            }

            // Empty line
            None => continue,

            Some("exit") => {
                stream.shutdown(std::net::Shutdown::Both).unwrap();
                println!("Session closed!");
                return;
            }

            // All other commands
            _ => {
                let mut message = String::new();

                if !nets_io::read_stream(stream.try_clone().unwrap(), &mut message) {
                    println!("Server error!");
                    return;
                }

                println!("{}", message.as_str().trim());
            }
        }
    }
}
