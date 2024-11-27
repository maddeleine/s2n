
use core::str;

use chacha20poly1305::{
    aead::{generic_array::{sequence::Lengthen, GenericArray}, Aead, AeadCore, KeyInit, OsRng}, Key, XChaCha20Poly1305 
};

fn main() -> Result<(), Box<chacha20poly1305::Error>>{
    // let key = XChaCha20Poly1305::generate_key(&mut OsRng);
    // println!("key: {:?}", key);

    // let cipher = XChaCha20Poly1305::new(&key);
    // let nonce = XChaCha20Poly1305::generate_nonce(&mut OsRng); // 192-bits; unique per message
    // println!("Nonce: {:?}", nonce);
    // let ciphertext = cipher.encrypt(&nonce, b"Hello there :)".as_ref())?;
    // println!("ciphertext: {:?}", ciphertext);
    // let plaintext = cipher.decrypt(&nonce, ciphertext.as_ref())?;
    // assert_eq!(&plaintext, b"Hello there :)");

    let key = [52, 141, 117, 167, 83, 250, 52, 22, 164, 129, 212, 243, 132, 130, 89, 101, 212, 55, 128, 204, 216, 5, 103, 1, 191, 111, 236, 69, 187, 109, 225, 49];
    let nonce = [57, 187, 132, 164, 49, 189, 241, 152, 16, 162, 163, 157, 189, 32, 224, 195, 173, 5, 89, 159, 75, 210, 85, 89];
    let ciphertext =  [204, 147, 123, 9, 46, 15, 161, 224, 79, 165, 9, 162, 1, 105, 255, 90, 108, 21, 202, 207, 45, 184, 105, 43, 6, 240, 236, 66, 144, 162];
    
    let key = Key::clone_from_slice(&key);
    let nonce = GenericArray::clone_from_slice(&nonce);
    let cipher = XChaCha20Poly1305::new(&key);
    let buf = cipher.decrypt(&nonce, ciphertext.as_ref())?;
    let s = match str::from_utf8(&buf) {
        Ok(v) => v,
        Err(e) => panic!("Invalid UTF-8 sequence: {}", e),
    };

    println!("resulting plaintext: {:?}", s);
    Ok(())
}
