#[derive(Debug)]
struct Struct;

pub trait Trait<T> {
    fn method(&self) -> T;
}

impl Trait<u8> for Struct {
    fn method(&self) -> u8 {
        16
    }
}

impl Trait<String> for Struct {
    fn method(&self) -> String {
        "hello".to_string()
    }
}

use std::fmt::Debug;

pub fn connect<T>(conn: T)
where
    T: Trait<u8> + Debug,
{
    println!("connect: {:?}", conn.method());
}

fn main() {
    let s = Struct;
    let a: u8 = s.method();
    let b: String = s.method();
    println!("a={}, b={}", a, b);
    println!("{:?}", connect(s));
}
