module Adder (adder) where

import Data.Bits

adder 0 b = b
adder a b = adder ((a .&. b) `shift` 1) (a `xor` b)
