-- 7.1
factrial :: Int -> Int
factrial 0 = 1
factrial n = n * factrial (n - 1)

-- 7.2
my_product :: [Int] -> Int
my_product [] = 1
my_product (n:ns) = n * my_product ns

my_length :: [a] -> Int
my_length [] = 0
my_length (_:xs) = 1 + length xs

my_reverse :: [a] -> [a]
my_reverse [] = []
my_reverse (x:xs) = reverse xs ++ [x]


-- 7.3
my_zip :: [a] -> [b] -> [(a, b)]
my_zip [] _ = []
my_zip _ [] = []
my_zip (x:xs) (y:ys) = (x, y) : zip xs ys

my_drop :: Int -> [a] -> [a]
my_drop 0 xs = xs
my_drop n [] = []
my_drop n (_:xs) = drop (n - 1) xs


-- 6.8 Exercises
-- exe1
pow :: Int -> Int -> Int
pow a 0 = 1
pow a n = a * pow a (n - 1)

-- exe3
my_and :: [Bool] -> Bool
my_and [] = True
my_and (x:xs) = x && my_and xs

my_concat :: [[a]] -> [a]
my_concat [] = []
my_concat (xs:xss) = xs ++ my_concat xss

my_replicate :: Int -> a -> [a]
my_replicate 0 _ = []
my_replicate n a = a : replicate (n - 1) a

my_exclamation2 :: [a] -> Int -> a
my_exclamation2 (x:xs) 0 = x
my_exclamation2 (_:xs) n = my_exclamation2 xs (n - 1)

my_elem :: Eq a => a -> [a] -> Bool
my_elem a [] = False
my_elem a (x:xs) | a == x = True
                 | otherwise = my_elem a xs

-- exe4
merge :: Ord a => [a] -> [a] -> [a]
merge [] xs = xs
merge xs [] = xs
merge (x:xs) (y:ys) | x <= y    = x : merge xs (y:ys)
                    | otherwise = y : merge (x:xs) ys

-- exe5
halve :: [a] -> ([a], [a])
halve [] = ([], [])
halve xs = (take half_length xs, drop half_length xs)
  where half_length = length xs `div` 2

merge_sort :: [Int] -> [Int]
merge_sort [] = []
merge_sort [x] = [x]
merge_sort xs = merge (merge_sort ys1) (merge_sort ys2)
  where (ys1, ys2) = halve xs

-- exe6
my_sum :: Num a => [a] -> a
my_sum [] = 0
my_sum (x:xs) = x + my_sum xs

my_take :: Int -> [a] -> [a]
my_take _ [] = []
my_take 0 _ = []
my_take n (x:xs) = x : my_take (n - 1) xs

my_last :: [a] -> a
my_last (x:[]) = x
my_last (_:xs) = my_last xs
