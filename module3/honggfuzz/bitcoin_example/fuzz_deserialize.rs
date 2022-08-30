extern crate bitcoin;
#[macro_use] extern crate honggfuzz;
use std::process;

fn do_fuzz(data: &[u8]) {
   let my_dec_msg: Result<bitcoin::network::message_network::VersionMessage, _> = bitcoin::consensus::encode::deserialize(data);
   
   if my_dec_msg.is_ok() {
      let dec_msg = my_dec_msg.unwrap(); 
      if data != bitcoin::consensus::encode::serialize(&dec_msg) {
		process::abort();
      }
   }
}

fn main() {
   loop {
       fuzz!(|data| {
           do_fuzz(data);
       });
   }
}

