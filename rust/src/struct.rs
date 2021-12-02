struct Foo<T> {
    text: T,
}

impl<T> Foo<T> {
    fn value(&self) -> &T {
        &self.text
    }
}

fn main() {
    let x = Foo { text: 3i32 };

    println!("output: {}", x.value());
}
