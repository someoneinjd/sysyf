grammar SysYF;

comp_unit: global_def+ EOF;
global_def: const_decl | var_decl | func_def;
const_decl: 'const' btype const_def (',' const_def)* ';';
btype: INT_T | FLOAT_T;
const_def: ident (LBRACKET INT? RBRACKET)? '=' const_init_val;
const_init_val: exp | '{' '}' | '{' exp (',' exp)* '}';
var_decl: btype var_def (',' var_def)* ';';
var_def: ident (LBRACKET INT? RBRACKET)? ('=' init_val)?;
init_val: exp | '{' '}' | '{' exp (',' exp)* '}' ;
func_def: btype ident '(' (func_fparam (',' func_fparam)*)? ')' block | VOID_T ident '(' (func_fparam (',' func_fparam)*)? ')' block;
func_fparam: btype ident (LBRACKET RBRACKET)?;
block: '{' (block_item)* '}';
block_item: const_decl | var_decl | stmt;
stmt: assign_stmt | empty_stmt | exp_stmt | block | if_stmt | while_stmt | break_stmt | continue_stmt | return_stmt;
assign_stmt: lval '=' exp ';';
empty_stmt: ';';
exp_stmt: exp ';';
if_stmt: 'if' '(' cond_exp ')' stmt ('else' stmt)?;
while_stmt: 'while' '(' cond_exp ')' stmt ;
break_stmt: 'break' ';';
continue_stmt: 'continue' ';';
return_stmt: 'return' exp? ';';

cond_exp:
    exp | cond_exp (LT | GT | LTE | GTE) cond_exp
    | cond_exp (NEQ | EQ) cond_exp
    | cond_exp LAND cond_exp
    | cond_exp LOR cond_exp;

exp:
    (PLUS | MINUS | NOT) exp | lval | number | func_call | '(' exp ')'
    | exp (MUL | DIV | MOD) exp
    | exp (PLUS | MINUS) exp;

func_call: ident '(' (exp (',' exp)*)? ')';
lval: ident ('[' exp ']')? ;
ident: NAME;
number: INT | FLOAT;

VOID_T: 'void';
INT_T: 'int';
FLOAT_T: 'float';
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';
MOD: '%';
LOR: '||';
LAND: '&&';
EQ: '==';
NEQ: '!=';
LT: '<';
LTE: '<=';
GT: '>';
GTE: '>=';
NOT: '!';
LBRACKET: '[';
RBRACKET: ']';
NAME: [_a-zA-Z] [_0-9a-zA-Z]*;
INT:  '0' [0-7]* | [1-9] [0-9]* | '0' [xX] [0-9a-fA-F]+;
FLOAT:  ([0-9]* '.' [0-9]+ | [0-9]+ '.') ([eE] [-+]? [0-9]+)? | [0-9]+ [eE] [-+]? [0-9]+;
C_COMMENT: '/*' .*? '*/' -> skip;
CPP_COMMENT: ('//' | '/\\' ('\r'? '\n') '/') ~[\r\n\\]* ('\\' ('\r'? '\n')? ~[\r\n\\]*)* '\r'? '\n' -> skip;
WS: [ \t\f\r\n]+ -> skip;
