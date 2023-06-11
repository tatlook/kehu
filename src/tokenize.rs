// use std::{error::Error, str::Chars, fmt::{Display, write}};

// mod tokenize;

// pub enum Token {
//     String(String),
//     Integer(i64),
//     Mark(String),
// }

// // #[derive(Debug)]
// // struct InvaildTokenError {
// //     msg: String
// // }

// // impl Display for InvaildTokenError {
// //     fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
// //         write!(f, "{}", self.msg);
// //     }
// // }

// // impl Error for InvaildTokenError {
// //     fn source(&self) -> Option<&(dyn Error + 'static)> {
// //         None
// //     }
    
// //     fn type_id(&self) -> std::any::TypeId
// //     where
// //         Self: 'static,
// //     {
// //         todo!()
// //     }
    
// //     fn description(&self) -> &str {
// //         "description() is deprecated; use Display"
// //     }

// //     fn cause(&self) -> Option<&dyn Error> {
// //         self.source()
// //     }

// //     fn provide<'a>(&'a self, demand: &mut std::any::Demand<'a>) {}
// // }

// fn read_string(s: &mut str) -> Result<Token, String> {
//     if s[0] != '"' {
//         return Result::Err(String::from("We have no idea"));
//     }
//     let string = String::from("");
//     s = &mut s[1..];
//     while s[0] != '"' {
//         s = &mut s[1..];
//         string.push(s[0]);
//     }
//     s = &mut s[1..];
//     let tok = Token::String(string);
//     return Result::Ok(tok);
// }

// pub fn tokenize(s: &String) -> Vec<Token> {
//     let tokens = Vec::new();
//     let str = &mut s.as_str();
//     while str.len() > 0 {
//         read_string(str);
//     }
//     return tokens;
// }

// #[cfg(test)]
// mod tests {
//     use std::vec;

//     #[test]
//     fn test_tokenize() {
//         //assert_eq!(super::tokenize(String::from("")), vec![]);
//     }
// }
