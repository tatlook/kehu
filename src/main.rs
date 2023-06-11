mod ast;

use std::{env, fs};

use lalrpop_util::lalrpop_mod;

macro_rules! lalrpop_mod_doc {
    ($vis:vis $name:ident) => {
        lalrpop_util::lalrpop_mod!(
            #[allow(clippy::ptr_arg)]
            #[allow(clippy::vec_box)]
            $vis $name);
    }
}

lalrpop_mod_doc!(pub grammar); // synthesized by LALRPOP

fn print_helps() {
    println!("Kehu - a toy language by Tatlook");
    println!("    Useage: kehu [source] [output]");
    println!("Enjoy.");
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() <= 1 {
        print_helps();
        return;
    }
    let path = &args[1];
    let result = fs::read_to_string(path);
    let content = match result {
        Ok(content) => content,
        Err(err) => {
            eprintln!("Error occured due opening file: {err}");
            return;
        }
    };
    compile_source(content);
}

fn compile_source(content: String) {
    let parser = grammar::TileTreeParser::new();
    let result = parser.parse(&content);
    match result {
        Ok(nr) => {
            print!("nr = {nr}");
        }
        Err(err) => {
            eprintln!("Syntax error: {err}");
            return;
        }
    }
}

#[test]
fn test_compile_source() {
    compile_source(String::from("1"));
}
