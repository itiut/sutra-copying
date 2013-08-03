-- 5.2
my_abs :: Int -> Int
my_abs n = if n >= 0 then n else -n

my_signum :: Int -> Int
my_signum n = if n > 0 then 1 else
                if n < 0 then -1 else 0

-- 5.3
my_abs2 n | n >= 0    = n
          | otherwise = -n


my_signum2 n | n > 0 = 1
             | n < 0 = -1
             | otherwise = 0

-- 5.4
my_not :: Bool -> Bool
my_not True = False
my_not False = True

my_and :: Bool -> Bool -> Bool
my_and False _ = False
my_and True b = b

my_fst :: (a, b) -> a
my_fst (x, _) = x

my_snd :: (a, b) -> b
my_snd (_, y) = y

my_null :: [a] -> Bool
my_null [] = True
my_null (_:_) = False

my_head :: [a] -> a
my_head (x:_) = x

my_tail :: [a] -> [a]
my_tail (_:xs) = xs

my_pred :: Int -> Int
my_pred n = n - 1

-- 5.5
add = \x -> (\y -> x + y)

my_const :: a -> b -> a
my_const x = \_ -> x

odds :: Int -> [Int]
odds n = map (\x -> 2 * x + 1) [0..n-1]


-- 5.8 exercises
-- 1
halve :: [a] -> ([a], [a])
halve xs = (take n xs, drop n xs)
  where n = length xs `div` 2

-- 2
safetail1 :: [a] -> [a]
safetail1 xs = if null xs then [] else (tail xs)

safetail2 :: [a] -> [a]
safetail2 xs | null xs = []
             | otherwise = tail xs

safetail3 :: [a] -> [a]
safetail3 [] = []
safetail3 (_:xs) = xs

-- 3
binary_or1 :: Bool -> Bool -> Bool
binary_or1 False False = False
binary_or1 False True = True
binary_or1 True False = True
binary_or1 True True = True

binary_or2 :: Bool -> Bool -> Bool
binary_or2 False False = False
binary_or2 _ _ = True

binary_or3 :: Bool -> Bool -> Bool
binary_or3 False b = b
binary_or3 True _ = True

binary_or4 :: Bool -> Bool -> Bool
binary_or4 b c | b == c = b
               | otherwise = True

-- 4
binary_and1 :: Bool -> Bool -> Bool
binary_and1 a b | a == b = b
                | otherwise = False

-- 5
binary_and2 :: Bool -> Bool -> Bool
binary_and2 a b | a == True = b
                | otherwise = False

-- 6
mult :: Int -> Int -> Int -> Int
mult = \x -> \y -> \z -> x * y * z
