import Data.Char                -- #ord #chr

my_sum = foldr (+) 0

my_odd :: Int -> Bool
my_odd = not . even

-- 7.6 String transmitter
type Bit = Int

bin2int :: [Bit] -> Int
bin2int bits = sum [w * b| (w, b) <- zip weights bits]
  where weights = iterate (*2) 1

bin2int' :: [Bit] -> Int
bin2int' = foldr (\x y -> x + 2 * y) 0

int2bin :: Int -> [Bit]
int2bin 0 = []
int2bin n = n `mod` 2 : int2bin (n `div` 2)

make8 :: [Bit] -> [Bit]
make8 bits = take 8 (bits ++ repeat 0)

encode :: String -> [Bit]
encode = concat . map (make8 . int2bin . ord)

chop8 :: [Bit] -> [[Bit]]
chop8 [] = []
chop8 bits = take 8 bits : chop8 (drop 8 bits)

decode :: [Bit] -> String
decode = map (chr . bin2int) . chop8

transmit :: String -> String
transmit = decode . channel . encode

channel :: [Bit] -> [Bit]
channel = id


-- 7.8 Exercises
-- exe1
comprehension :: (a -> a) -> [a] -> (a -> Bool) -> [a]
comprehension f xs p = map f (filter p xs)

-- exe2
my_all1 :: (a -> Bool) -> [a] -> Bool
my_all1 _ [] = True
my_all1 p (x:xs) = p x && my_all1 p xs

my_all2 :: (a -> Bool) -> [a] -> Bool
my_all2 p = foldr (\x y -> p x && y) True

my_any :: (a -> Bool) -> [a] -> Bool
my_any p = foldr (\x y -> p x || y) False

my_takeWhile :: (a -> Bool) -> [a] -> [a]
my_takeWhile _ [] = []
my_takeWhile p (x:xs) | p x       = x : (my_takeWhile p xs)
                      | otherwise = []

my_dropWhile :: (a -> Bool) -> [a] -> [a]
my_dropWhile _ [] = []
my_dropWhile p (x:xs) | p x       = my_dropWhile p xs
                      | otherwise = x:xs

-- exe3
my_map :: (a -> b) -> [a] -> [b]
my_map f = foldr (\x xs -> (f x):xs) []

my_filter :: (a -> Bool) -> [a] -> [a]
my_filter p = foldr (\x xs -> if p x then (x:xs) else xs) []

-- exe4
dec2int :: [Int] -> Int
dec2int = foldl (\x y -> x * 10 + y) 0

-- exe5
compose :: [a -> a] -> a -> a
compose = foldr (.) id

-- sumsqreven = compose [sum, map (^ 2), filter even]
-- `sum :: Num a -> [a] -> a` has a defferent type from others
-- (eg.) map (^ 2) :: Num a => [a] -> [a]
--       filter even :: Integral a => [a] -> [a]

-- exe6
my_curry :: ((a, b) -> c) -> a -> b -> c
my_curry f a b = f (a, b)

my_uncurry :: (a -> b -> c) -> (a, b) -> c
my_uncurry f (a, b) = f a b

-- exe7
unfold p h t x | p x       = []
               | otherwise = h x : unfold p h t (t x)

int2bin' = unfold (== 0) (`mod` 2) (`div` 2)

chop8' = unfold (null) (take 8) (drop 8)

-- exe8
count :: Eq a => a -> [a] -> Int
count a = foldr f 0
  where f x | x == a    = (+ 1)
            | otherwise = (+ 0)

parity :: [Bit] -> Bit
parity xs | odd (count 1 xs) = 0
          | otherwise        = 1

add_parity :: [Bit] -> [Bit]
add_parity xs = (parity xs) : xs

encode' :: String -> [Bit]
encode' = concat . map (add_parity . make8 . int2bin . ord)

chop :: Int -> [Bit] -> [[Bit]]
chop _ [] = []
chop x bits = take x bits : chop x (drop x bits)

chop9 = chop 9

remove_parity_unless_error :: [Bit] -> [Bit]
remove_parity_unless_error (pb:bits) | pb == parity bits = bits
                                     | otherwise         = error "parity bit is incorrect!"

decode' :: [Bit] -> String
decode' = map (chr . bin2int . remove_parity_unless_error) . chop9

-- exe9
transmit' :: String -> String
transmit' = decode' . channel . encode'

false_channel :: [Bit] -> [Bit]
false_channel = tail

falsely_transmit :: String -> String
falsely_transmit = decode' . false_channel . encode'
