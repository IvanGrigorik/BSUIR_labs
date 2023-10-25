use chrono::prelude::*;
use local_ip_address::local_ip;
use socket2::{Domain, Protocol, Socket, Type};
use std::fs::{self, File, OpenOptions};

use std::io::BufReader;
use std::net::IpAddr;
use std::path::PathBuf;
use std::{
    io::prelude::*,
    net::{SocketAddr, TcpListener, TcpStream},
};

mod nets_io;

const PORT: u16 = 1203;
const CHUNK_SIZE: usize = 1024;
const TIMEOUT_SEC: u64 = 10;

#[derive(PartialEq, Eq)]
enum LoadingType {
    Upload,
    Download,
}

struct BreakerBuff {
    load_buff: Vec<Vec<u8>>,
    pos: usize,
    ip: SocketAddr,
    is_pending: bool,
    transferred_bytes: usize,
    total_bytes: usize,
    path: String,
    kind: LoadingType,
}

fn main() {
    println!("Your address: {}:{}", local_ip().unwrap(), PORT);

    let (socket, listener) = connect_tcp_listener(local_ip().unwrap(), PORT);

    println!("Server is up!");
    let mut buff = BreakerBuff {
        load_buff: Vec::new(),
        pos: 0,
        ip: SocketAddr::new(local_ip().unwrap(), 1203),
        is_pending: false,
        transferred_bytes: 0,
        total_bytes: 0,
        path: String::new(),
        kind: LoadingType::Upload,
    };
    for stream in listener.incoming() {
        let stream = stream.unwrap();
        buff.ip = stream.peer_addr().unwrap().clone();
        handle_connection(socket.try_clone().unwrap(), stream, &mut buff);
        println!("Connection closed");
    }
}

fn connect_tcp_listener(ip: IpAddr, port: u16) -> (socket2::Socket, TcpListener) {
    let addr = SocketAddr::new(ip, port);
    let socket = Socket::new(Domain::IPV4, Type::STREAM, Some(Protocol::TCP))
        .expect("Socket must be created!");

    socket.bind(&addr.into()).expect("Socket must be binded!");
    // Socket ready to incoming traffic
    socket.listen(8).unwrap();
    (socket.try_clone().unwrap(), socket.into())
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

fn flush_breaker(buff: &mut BreakerBuff) {
    buff.pos = 0;
    buff.transferred_bytes = 0;
    buff.total_bytes = 0;
    buff.load_buff = Vec::new();
    buff.ip = SocketAddr::new(local_ip().unwrap(), 1203);
}

fn set_pending(buff: &mut BreakerBuff, file_path: String) {
    buff.is_pending = true;
    buff.path = file_path;
}

// TODO: Delete permission
fn handle_connection(_socket: socket2::Socket, mut stream: TcpStream, mut buff: &mut BreakerBuff) {
    println!("New connection: {}", stream.peer_addr().unwrap());
    
    stream
        .set_read_timeout(Some(std::time::Duration::new(20, 0)))
        .expect("set_read_timeout call failed");
    stream
        .set_write_timeout(Some(std::time::Duration::new(20, 0)))
        .expect("set_read_timeout call failed");

    // If new client connect
    if buff.ip.ip() != stream.peer_addr().unwrap().ip() {
        buff.ip = stream.peer_addr().unwrap();
        buff.is_pending = false;
    }

    loop {
        let mut message = String::new();
        if !nets_io::read_stream(stream.try_clone().unwrap(), &mut message) || message.is_empty() {
            break;
        }

        let message = message.trim_end().trim_start();
        let message_words: Vec<_> = message.split_whitespace().collect();
        let command = message_words.first().copied();

        // If we receive download/upload command without path:
        if message_words.len() < 2 && (command == Some("download") || command == Some("upload")) {
            continue;
        }

        match command.as_deref() {
            Some("echo") => {
                let mut echo_data = message_words[1..].join(" ");
                echo_data.push('\n');
                if !nets_io::write_stream(stream.try_clone().unwrap(), echo_data.clone()) {
                    return;
                }
            }

            Some("time") => {
                let mut time = Local::now().to_rfc2822();
                time.push('\n');
                if !nets_io::write_stream(stream.try_clone().unwrap(), time.clone()) {
                    return;
                }
            }

            Some("exit") => {
                if !nets_io::write_stream(
                    stream.try_clone().unwrap(),
                    "Connection closed\n".to_string(),
                ) {
                    return;
                }
                break;
            }

            // Upload from client to server
            Some("upload") => {
                if buff.kind == LoadingType::Download {
                    flush_breaker(buff);
                    buff.kind = LoadingType::Upload;
                }

                // Check for file existence on the client
                let mut file_exist = String::new();
                if !nets_io::read_stream(stream.try_clone().unwrap(), &mut file_exist) {
                    continue;
                }
                println!("{}", file_exist.trim());
                if file_exist.trim() == "File does not exist" {
                    continue;
                }

                // Get file name from message
                let path_str = message_words[1];
                let file = path_str.split('/').last().unwrap();
                let path = PathBuf::from("uploaded_files/".to_string() + file.trim());

                // Read file and decide how much content we already have, if file exist
                if !path.exists() {
                    File::create(path.clone()).unwrap();
                }
                let file_len = std::fs::read(path.clone()).unwrap().len();
                let file_pos = file_len / CHUNK_SIZE;
                buff.pos = file_pos;
                let mut prev = file_pos * CHUNK_SIZE;

                // Create file to write our data
                let mut out_file = OpenOptions::new()
                    .write(true)
                    .append(true)
                    .open(path.clone())
                    .unwrap();

                // Send file seek position to the client
                if !nets_io::write_stream(stream.try_clone().unwrap(), format!("{}\n", file_len)) {
                    return;
                }

                // Get status: is file uploaded fully or no
                let mut uploaded_status = String::new();
                if !nets_io::read_stream(stream.try_clone().unwrap(), &mut uploaded_status) {
                    continue;
                }
                if uploaded_status.trim() == "SENDED" {
                    println!("File at the server.");
                    continue;
                }

                // Set read timeout, due to client instability
                let timeout = std::time::Duration::new(TIMEOUT_SEC, 0);
                stream.set_read_timeout(Some(timeout)).unwrap();

                // Start to get file content from client with some timeout
                loop {
                    let mut chunk = [0u8; CHUNK_SIZE];
                    let mut buf: BufReader<&mut std::net::TcpStream> = BufReader::new(&mut stream);

                    // Read from buffer with timeout
                    match buf.read(&mut chunk) {
                        Err(error) => {
                            // Timeout error - need to pend this file and client!
                            if error.raw_os_error().unwrap() == 11 {
                                set_pending(buff, path_str.to_string());
                            } else {
                                println!("Timeout error!");
                                set_pending(buff, path_str.to_string());
                                return;
                            }
                            println!("Reading from stream error! Err: {}", error.kind());
                        }
                        _ => (),
                    };

                    if chunk.iter().all(|&x| x == 0) {
                        set_pending(buff, path_str.to_string());
                        println!("Uploading interrupted!");
                        return;
                    }

                    if !nets_io::write_stream(
                        stream.try_clone().unwrap(),
                        format!("ACK{}\n", buff.pos),
                    ) {
                        set_pending(buff, path_str.to_string());
                        return;
                    }

                    // Get "urgent" data
                    let mut urg_str = String::new();
                    if !nets_io::read_urg(stream.try_clone().unwrap(), &mut urg_str) {
                        set_pending(buff, path_str.to_string());
                        return;
                    }
                    if urg_str.is_empty() {
                        set_pending(buff, path_str.to_string());
                        return;
                    }

                    let (current, total) = urg_str.trim().split_at(10);
                    println!("{} / {}", current, total);

                    if chunk.len() != 0 {
                        let message = String::from_utf8(chunk.to_vec()).unwrap();
                        let mut idx: usize = CHUNK_SIZE;
                        if current.parse::<usize>().unwrap() != 0 {
                            idx = current.parse::<usize>().unwrap() - prev;
                        }
                        // Check if message already in file, if renew downloading
                        if file_len < current.parse().unwrap() {
                            out_file.write(&message.as_bytes()[..idx]).unwrap();
                        }
                        prev = current.parse().unwrap();
                    }

                    if current == total {
                        break;
                    }
                    // Ready to read next position
                    buff.pos += 1;
                }

                if !nets_io::write_stream(
                    stream.try_clone().unwrap(),
                    "File uploaded!\n".to_string(),
                ) {
                    return;
                }

                println!("File uploaded to the server!");
                flush_breaker(&mut buff);
                stream
                    .set_read_timeout(None)
                    .expect("set_read_timeout call failed");
            }

            // Download from server to client
            Some("download") => {
                // First - check buffer for loading type
                if buff.kind == LoadingType::Upload {
                    flush_breaker(buff);
                    buff.kind = LoadingType::Download;
                }

                // Get path from client request
                let path_str = message_words[1];

                if path_str != buff.path {
                    buff.is_pending = false;
                    buff.path = path_str.to_string();
                }

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
                    continue;
                } else {
                    if !nets_io::write_stream(
                        stream.try_clone().unwrap(),
                        "Initiate file transfer\n".to_string(),
                    ) {
                        return;
                    }
                }

                // Read content from file and divide it by chunks
                let content = fs::read(path.clone()).unwrap();
                buff.total_bytes = content.len();
                let chunks: Vec<Vec<u8>> = content.chunks(CHUNK_SIZE).map(|s| s.into()).collect();

                buff.load_buff = chunks;
                if !buff.is_pending {
                    buff.pos = 0;
                }

                // Start or resume downloading
                while buff.pos != buff.load_buff.len() {
                    match stream.write_all(buff.load_buff[buff.pos].as_ref()) {
                        Err(error) => {
                            buff.is_pending = true;
                            println!("Pipe is broken! Error: {}", error);
                            return;
                        }
                        _ => (),
                    }
                    stream.flush().unwrap();

                    // Wait for acknowledgment from client after transmitting
                    let mut ack_message = String::new();
                    if !nets_io::read_stream(stream.try_clone().unwrap(), &mut ack_message) {
                        buff.is_pending = true;
                        return;
                    }

                    if ack_message.trim() == "ACKSEND" {
                        break;
                    }

                    // Check is it right ACK
                    if ack_message.trim() == format!("ACK{}", buff.pos) {
                        buff.pos += 1;
                        if buff.pos != 0 {
                            buff.transferred_bytes += buff.load_buff[buff.pos - 1].len();
                        }
                    }

                    // Write "URG" message about transferred bytes
                    if !nets_io::write_urg(
                        stream.try_clone().unwrap(),
                        format!("{:0>10}{:0>10}\n", buff.transferred_bytes, buff.total_bytes),
                    ) {
                        buff.is_pending = true;
                        return;
                    }
                }

                nets_io::write_stream(stream.try_clone().unwrap(), "File sended!\n".to_string());
                flush_breaker(&mut buff);
                println!("File sended");
            }

            // Fictive ACKSEND message - ignore
            Some("ACKSEND") => (),

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
    if buff.pos != buff.load_buff.len() && buff.kind == LoadingType::Download {
        buff.is_pending = true;
    }
}
