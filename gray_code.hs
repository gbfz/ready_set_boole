import Data.Bits

gray_code b = b `xor` (b `shiftR` 1)
