module Multiplier (multiplier) where

import Adder 
import Data.Bits

multiplier' _ 0 prod = prod
multiplier' a b prod = multiplier' (a `shiftL` 1) (b `shiftR` 1) prod'
                       where prod' | b .&. 1 == 0 = prod
                                   | otherwise = adder prod a

multiplier a b = multiplier' a b 0
