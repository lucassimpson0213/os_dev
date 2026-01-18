use kernel::idt::makeidt::IdtEntry;

pub fn test_idt_entry() -> u32 {
    IdtEntry::new()
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
