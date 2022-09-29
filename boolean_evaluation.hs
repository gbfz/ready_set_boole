import Data.Bits

bool c | c == '1' = True
       | c == '0' = False
char b | b == True  = '1'
       | b == False = '0'

unop l op = case op of
            '!' -> char (not (bool l))
            _ -> error "Unknown unary operator"

binop l op r = case op of
               '&' -> char (bool l && bool r)
               '|' -> char (bool l || bool r)
               '^' -> char (bool l `xor` bool r)
               '>' -> char (bool l == bool r)
               '=' | l == '0' -> '1'
                   | l == r -> '1'
                   | otherwise -> '0'
               _ -> error "Unknown binary operator"

eval_formula' (l:r:'!':xs) = eval_formula' (l : unop r '!' : xs)
eval_formula' (l:'!':xs)   = eval_formula' (unop l '!' : xs)
eval_formula' (l:r:op:xs)  = eval_formula' (binop l op r : xs)
eval_formula' c = c

eval_formula f = case eval_formula' f of
                 ['1'] -> True
                 ['0'] -> False
                 _ -> error "Invalid formula"
