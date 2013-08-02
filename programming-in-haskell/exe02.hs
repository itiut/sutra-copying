-- 2.5
qsort [] = []
qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
  where
    smaller = [a | a <- xs, a < x]
    larger  = [b | b <- xs, b >= x]


-- 2.7 exercises
-- 1
double x = x * 2

-- 3
my_product [] = 1
my_product (x:xs) = x * (my_product xs)

-- 4
rqsort [] = []
rqsort (x:xs) = rqsort larger ++ [x] ++ rqsort smaller
  where
    larger  = [a | a <- xs, a > x]
    smaller = [b | b <- xs, b <= x]
