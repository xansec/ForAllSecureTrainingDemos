extern crate bitcoin;
#[macro_use] extern crate honggfuzz;
use std::process;
use std::net::{SocketAddr, IpAddr, Ipv4Addr};
use byteorder::{ByteOrder, LittleEndian};

fn do_fuzz(data: &[u8]) {
    // version
   if data.len() < 36 {
       return;
   }
   let _version: u32 = LittleEndian::read_u32(&data[0..3]); 

    // "bitfield of features to be enabled for this connection"
   let services: bitcoin::network::constants::ServiceFlags = bitcoin::network::constants::ServiceFlags::NONE;

    // "standard UNIX timestamp in seconds"
   let timestamp: i64 = LittleEndian::read_i64(&data[4..11]);

    // "The network address of the node receiving this message"
   let to_address = SocketAddr::new(IpAddr::V4(Ipv4Addr::new(data[12], data[13], data[14], data[15])), 0);
   let addr_recv = bitcoin::network::address::Address::new(&to_address, bitcoin::network::constants::ServiceFlags::NONE);

    // "The network address of the node emitting this message"
   let from_address = SocketAddr::new(IpAddr::V4(Ipv4Addr::new(data[16], data[17], data[18], data[19])), 0);
   let addr_send = bitcoin::network::address::Address::new(&from_address, bitcoin::network::constants::ServiceFlags::NONE);

    // "Node random nonce, randomly generated every time a version packet is sent. This nonce is used to detect connections to self."
   let nonce: u64 = LittleEndian::read_u64(&data[20..27]);

    // "User Agent (0x00 if string is 0 bytes long)"
   let user_agent: String = String::from_utf8_lossy(&data[28..31]).to_string();

    // "The last block received by the emitting node"
   let start_height: i32 = LittleEndian::read_i32(&data[32..35]);

   let dec_msg = bitcoin::network::message_network::VersionMessage::new(
        services,
        timestamp,
        addr_recv,
        addr_send,
        nonce,
        user_agent,
        start_height,
   );
   
   let enc_msg = bitcoin::consensus::encode::serialize(&dec_msg);
   if dec_msg != bitcoin::consensus::encode::deserialize(&enc_msg).unwrap() {
         process::abort();
   }
}


fn main() {
   loop {
       fuzz!(|data| {
           do_fuzz(data);
       });
   }
}

