module Boolean_Evaluation (eval_formula) where
import Data.Bits
import Data.Char
import qualified Data.Map as Map

isBinOp op = op `elem` "&|^>="
isUnOp op = op == '!'

unop '!' n = if n == '1' then '0' else '1'
unop _ _ = error "Invalid unary operator"

binop' op [l, r] = intToDigit $ digitToInt l `op` digitToInt r
binop '&' = binop' (.&.)
binop '|' = binop' (.|.)
binop '^' = binop' (xor)
binop '>' = \[l, r] -> if l == '0' then '1' else r
binop '=' = \[l, r] -> if l == r then '1' else '0'
binop _ = error "Invalid binary operator"

operations = Map.fromList [('&', binop' (.&.)), 
                           ('|', binop' (.|.)),
                           ('^', binop' (xor)),
                           ('>', (\[l, r] -> if l == '0' then '1' else r)),
                           ('=', (\[l, r] -> if l == r then '1' else '0')),
                           ('!', (\[l] -> if l == '1' then '0' else '1'))
                          ]
aaa = case (Map.lookupKey '&' operations) of
      (Just op) -> if op == "!" then True else False
      (Nothing) -> False

eval stack '1' = '1':stack
eval stack '0' = '0':stack
{-
eval stack op | (isUnOp op) = unop op (head stack):(tail stack)
              | (isBinOp op) = binop op (take 2 stack):(drop 2 stack)
              | otherwise = ""
-}

eval_formula f = case (foldl (eval) "" f) of
                 "1" -> True
                 "0" -> False
                 _ -> error ("Invalid formula: " ++ f)
