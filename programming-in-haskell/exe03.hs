-- 3.4
double x = x + x
quadruple x = double (double x)

factrial n = product [1..n]
average ns = sum ns `div` length ns


-- 3.6 exercises
-- 1
a1 = 2^3 * 4
a2 = 2 * 3 + 4 * 5
a3 = 2 + 3 * 4^5

-- 3
n = a `div` length xs
  where
    a = 10
    xs = [1, 2, 3, 4, 5]

-- 4
my_last_rec [x] = x
my_last_rec (x:xs) = my_last_rec xs

my_last xs = xs !! (length xs - 1)

-- 5
my_init_rec [x] = []
my_init_rec (x:xs) = [x] ++ my_init_rec xs

my_init xs = take (length xs - 1) xs
