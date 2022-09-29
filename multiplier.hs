import Data.Bits

adder 0 b = b
adder a b = adder ((a .&. b) `shift` 1) (a `xor` b)

multiplier' _ 0 prod = prod
multiplier' a b prod = multiplier' (shiftL a 1) (shiftR b 1) prod'
                       where prod' = if b .&. 1 == 0
                                     then prod
                                     else adder prod a
multiplier a b = multiplier' a b 0
