use core::fmt::{self, Display};

pub struct Statement {
    elements: Vec<StatementElement>,
}

pub enum StatementElement {
    RawString { value: String },
    RawChar { value: char },
    RawInteger { value: i32 },
    Word { name: String },
    Variable { name: String },
    Type { name: String },
    Term { sub_statement: Statement },
    Block { statements: Vec<Statement> },
}

impl Statement {
    pub fn new(elements: Vec<StatementElement>) -> Self {
        Statement { elements }
    }
}

impl Display for Statement {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for e in &self.elements {
            write!(f, "{} ", e)?;
        }
        write!(f, ".")
    }
}

impl StatementElement {
    pub fn string(value: String) -> Self {
        StatementElement::RawString { value }
    }

    pub fn char(value: char) -> Self {
        StatementElement::RawChar { value }
    }

    pub fn integer(value: i32) -> Self {
        StatementElement::RawInteger { value }
    }

    pub fn word(name: String) -> Self {
        StatementElement::Word { name }
    }

    pub fn variable(name: String) -> Self {
        StatementElement::Variable { name }
    }

    pub fn type_(name: String) -> Self {
        StatementElement::Type { name }
    }

    pub fn term(sub_statement: Statement) -> Self {
        StatementElement::Term { sub_statement }
    }

    pub fn block(statements: Vec<Statement>) -> Self {
        StatementElement::Block { statements }
    }
}

impl Display for StatementElement {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            StatementElement::RawString { value } => {
                write!(f, "\"{value}\"")
            }
            StatementElement::RawChar { value } => {
                write!(f, "'{value}'")
            }
            StatementElement::RawInteger { value } => {
                write!(f, "{value}")
            }
            StatementElement::Word { name } => {
                write!(f, "{name}")
            }
            StatementElement::Variable { name } => {
                write!(f, "{name}")
            }
            StatementElement::Type { name } => {
                write!(f, "{name}")
            }
            StatementElement::Term { sub_statement } => {
                write!(f, "(")?;
                for e in &sub_statement.elements {
                    write!(f, "{} ", e)?;
                }
                write!(f, ")")
            }
            StatementElement::Block { statements } => {
                writeln!(f, "{{")?;
                for st in statements {
                    writeln!(f, "\t{st}")?;
                }
                write!(f, "}}")
            }
        }
    }
}
