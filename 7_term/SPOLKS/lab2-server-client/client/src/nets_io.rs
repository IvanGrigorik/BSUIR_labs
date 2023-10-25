use std::io::{prelude::Write, BufRead, BufReader};

/// Attempt to write to TcpStream and return true, if there were no errors
/// # Examples
/// ```no_run
///
///  use std::net::{SocketAddr, TcpListener, IpAddr};
///  use std::str::FromStr;
///
///  fn main() {
///      let addr = SocketAddr::new(IpAddr::from_str("192.168.1.1").unwrap(), 8080);
///      let listener = TcpListener::bind(addr).unwrap();
///
///      for stream in listener.incoming() {
///          let stream = stream.unwrap();
///
///          if !write_stream(stream.try_clone().unwrap(), "Hello there!\n".to_string()){
///              // Pipe broken - do some internal logic
///             stream.shutdown(std::net::Shutdown::Both);
///         }
///      }
///  }
/// ```
pub fn write_stream(mut stream: std::net::TcpStream, msg: String) -> bool {
    match stream.write_all(msg.as_bytes()) {
        Err(error) => {
            println!("Pipe is broken! Error: {}", error.to_string());
            return false;
        }

        Ok(_) => return true,
    }
}

pub fn read_stream(mut stream: std::net::TcpStream, mut msg: &mut String) -> bool {
    let mut buf: BufReader<&mut std::net::TcpStream> = BufReader::new(&mut stream);
    match buf.read_line(&mut msg) {
        Err(error) => {
            println!("Reading from stream error! Err: {}", error.kind());
            return false;
        }
        _ => return true,
    };
}

pub fn write_urg(mut stream: std::net::TcpStream, msg: String) -> bool {
    match stream.write_all(msg.as_bytes()) {
        Err(error) => {
            println!("Urgent message writing error! Err: {}", error.kind());
            return false;
        }

        Ok(_) => return true,
    }
}

pub fn read_urg(mut stream: std::net::TcpStream, mut msg: &mut String) -> bool {
    let mut buf: BufReader<&mut std::net::TcpStream> = BufReader::new(&mut stream);
    match buf.read_line(&mut msg) {
        Err(error) => {
            println!("Urgent message reading error! Err: {}", error.kind());
            return false;
        }
        _ => return true,
    };
}


