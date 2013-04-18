import Data.Char

funcpot f 0 = (\x -> x)
funcpot f (n+1) = (funcpot f n).f

fibs = 0:1:(zipWith (+) fibs (tail fibs))

fl :: (a->b->c) -> b -> a -> c
fl f x y = f y x

sgn x | x>0  = 1
      | x==0 = 0
      | x<0  = -1



bolzano f min max tol | sgn (f min) == sgn (f max) = error "No se puede aplicar Bolzano."
                      | min + 2*tol > max = a
                      | f min == 0 = min
                      | f max == 0 = max
                      | f a == 0 = a
                      | sgn (f a) == sgn (f max) = bolzano f min a tol
                      | otherwise  =  bolzano f a max tol	
		where a = (min+max)/2


pot2 :: Int -> Int
pot2 1 = 1
pot2 x = 2 * pot2 (div x 2)

fib2 :: Int -> Int
fib2 n = round ((phi^n - (1-phi)^n)/sqrt 5) 
         where phi = (1+sqrt 5)/2

quicksort :: Ord a => [a] -> [a]
quicksort [] = []
quicksort (x:xs) = quicksort (filter (<x) xs) ++ [x] ++ quicksort (filter (>=x) xs)

minout' :: [Int] -> Int -> Int
minout' xs n | not (elem n xs) = n
             | otherwise = minout' xs (n+1)

minout :: [Int] -> Int
minout xs = minout' xs 0

balparen xs = balparen' xs 0

balparen' []       n = n==0
balparen' ('(':xs) n = n>=0 && balparen' xs (n+1)
balparen' (')':xs) n = n>=0 && balparen' xs (n-1)
balparen' (x:xs) n = n>=0 && balparen' xs n


bal :: [Bool] -> Bool
bal xs = gbal 0 xs

gbal :: Int -> [Bool] -> Bool
gbal n [] = (n==0)
gbal n (x:xs) | x==True  = gbal (n+1) xs
              | x==False = gbal (n-1) xs

data Nat = Zero | Succ Nat deriving (Eq,Show)

tonat :: Int -> Nat
tonat 0 = Zero
tonat (x+1) = Succ (tonat x)

toint :: Nat -> Int
toint Zero = 0
toint (Succ y) = 1 + toint y

suma :: Nat -> Nat -> Nat
suma x Zero = x
suma x (Succ y) = Succ (suma x y)

prod :: Nat -> Nat -> Nat
prod x Zero = Zero
prod x (Succ y) = suma (prod x y) x

power :: Nat -> Nat -> Nat
power (Succ x) Zero = Succ Zero
power Zero (Succ y) = Zero
power x (Succ y) = prod (power x y) x 

fact :: Nat -> Nat
fact Zero = Succ Zero
fact (Succ n) = prod (Succ n) (fact n)

fibn :: Nat -> Nat
fibn Zero = Zero
fibn (Succ Zero) = Succ Zero
fibn (Succ (Succ n)) = suma (fibn (Succ n)) (fibn n)

gt :: Nat -> Nat -> Bool
gt Zero x = False
gt (Succ Zero) Zero = True
gt (Succ x) (Succ y) = gt x y

ge :: Nat -> Nat -> Bool
ge x y = (gt x y) || x==y

lt :: Nat -> Nat -> Bool
lt x y = not (ge x y)

le :: Nat -> Nat -> Bool
le x y = not (gt x y)

comp :: Nat -> Nat -> Int
comp x y | gt x y    = 1
         | x==y      = 0
         | otherwise = -1

null :: [a] -> Bool
null [] = True
null (x:xs) = False

_length :: [a] -> Int
_length [] = 0
_length (x:xs) = 1 + _length xs

append :: [a] -> [a] -> [a]
append [] ys = ys
append (x:xs) ys = x:(append xs ys)

_concat :: [[a]] -> [a]
_concat [xs] = xs
_concat (xs:ys:xss) = append xs (_concat (ys:xss))

_reverse :: [a] -> [a]
_reverse [] = []
_reverse (x:xs) = append (_reverse xs) [x]

_head :: [a] -> a
_head (x:xs) = x

_tail :: [a] -> [a]
_tail (x:xs) = xs

_last :: [a] -> a
_last (x:[]) = x
_last (x:y:xs) = _last (y:xs)

_init :: [a] -> [a]
_init (x:[]) = [x]
_init (x:y:xs) = x : init(y:xs)

prodL :: [Int] -> Int
prodL [] = 1
prodL (x:xs) = x * prodL xs

minL :: [Int] -> Int
minL [x] = x
minL (x:xs) | x < minL xs = x
            | otherwise   = minL xs

andL :: [Bool] -> Bool
andL [] = True
andL (x:xs) = x && (andL xs)

mapL :: (a -> b) -> [a] -> [b]
mapL f [] = []
mapL f (x:xs) = (f x) : (mapL f xs)

duplicartodos :: [Int] -> [Int]
duplicartodos xs = mapL (*2) xs

longitudes :: [[a]] -> [Int]
longitudes xs = mapL length xs

amayus :: [Char] -> [Char]
amayus xs = mapL toUpper xs

duplistas :: [[Int]] -> [[Int]]
duplistas xs = mapL duplicartodos xs

filterL :: (a -> Bool) -> [a] -> [a]
filterL f [] = []
filterL f (x:xs) | f x = x : (filterL f xs)
                 | otherwise = filterL f xs

digitos :: [Char] -> [Char]
digitos xs = filter isDigit xs

apariciones :: Int -> [Int] -> [Int]
apariciones n xs = filterL (==n) xs

nocorta :: Int -> [a] -> Bool
nocorta n xs = length xs >= n

filtrarCortas :: Int -> [[a]] -> [[a]]
filtrarCortas n xss = filterL (nocorta n) xss

crec :: [Int] -> Bool
crec [x] = True
crec (x:y:xs) = x<=y && crec (y:xs)

ordenadas :: [[Int]] -> [[Int]]
ordenadas xss = filterL crec xss

data Dir = N | NE | E | SE | S | SO | O | NO deriving (Ord,Enum,Eq,Show)

invertir :: Dir -> Dir
invertir d = toEnum (mod (fromEnum d + 4) 8)

swap :: (a,b) -> (b,a)
swap (a,b) = (b,a)

data Dia = Lun | Mar |  Mie | Jue | Vie | Sab | Dom deriving(Eq,Show,Enum,Ord)


--uso: sieve [] 2  max = [primos 2 hasta max]
sieve :: [Int] -> Int -> Int -> [Int]
sieve xs ad max | ad>max = []
                | not (divisoren ad xs) = ad:(sieve (xs++[ad]) (ad+1) max)
                | otherwise       = sieve xs (ad+1) max

sieve' :: [Int] -> Int -> Int -> [Int]
sieve' xs ad max | ad>max = xs
                 | not (divisoren ad xs) = (sieve' (xs++[ad]) (ad+1) max)
                 | otherwise       = sieve' xs (ad+1) max

fib :: Int -> Integer
fib x = snd (fib' x)

fib':: Int -> (Integer, Integer)
fib' (n+1) = (b, a + b)
             where (a,b) = fib' n
fib' 0 = (1,0)

f :: Int -> Integer -> Integer -> Integer
f (n+1) a b = f n b (a+b)
f 0 a b = a

ff :: Int -> Integer
ff n = f n 0 1

divisoren :: Int -> [Int] -> Bool
divisoren x [] = False
divisoren x (y:ys) | y*y>x        = False
		   | mod x y == 0 = True
                   | otherwise    = divisoren x ys

pot :: Int -> Int -> Int
pot x 0 = 1
pot x n | n>0 = x * pot x (n-1)

split :: Int -> [a] -> ([a],[a])
split 0 xs = ([],xs)
split (n+1) [] = ([],[])
split (n+1) (x:xs) = (x:(fst a),snd a)
                     where a = split n xs

hascero :: [Int] -> Bool
hascero [] = False
hascero (x:xs) | x==0  =  True
               | otherwise = hascero xs
 
ultimocero :: [Int] -> Int
ultimocero xs | last xs == 0 = length xs - 1
              | otherwise    = ultimocero (init xs)

rev :: [a] -> [a]
rev [] = []
rev (x:xs) = (rev xs) ++ [x]

linf = 1:linf
inf = 1 + inf
linf2 = linf2++[1]

filter_ :: (a -> Bool) -> [a] -> [a]
filter_ f [] = []
filter_ f (x:xs) | f x = x:(filter_ f xs)
                 | otherwise = (filter_ f xs)

par :: Int -> Bool
par x = mod x 2 == 0

tienea :: String -> Bool
tienea s = head s == 'a'

prom :: Int -> Int -> Int -> Int
prom x y z = div (x+y+z) 3

naboveavg :: Int -> Int -> Int -> Int
naboveavg a b c = (if a>p then 1 else 0) + (if b>p then 1 else 0) + (if c>p then 1 else 0) 
		where p = prom a b c

max3 :: Int -> Int -> Int -> Int 
max3 x y z = if a>z then a else z
             where a = (if x>y then x else y)

rect :: Int -> Int -> Int -> Bool
rect x y z = x*x + y*y + z*z == 2*a*a
             where a = max3 x y z

isPrime :: Int -> Bool
isPrime x = divfree x 2

divfree :: Int -> Int -> Bool
divfree x d | d*d>x         = True
	    | mod x d == 0 = False
            | otherwise    = divfree x (d+1)

sort :: [Int] -> [Int]
sort [] = []
sort (x:xs) = insert x (sort xs)

insert :: Int -> [Int] -> [Int]
insert x [] = [x]
insert x (y:ys)   | x<=y       =  x:(y:ys) 
                  | otherwise  =  y:(insert x ys)

nat :: [Int]
nat = 0:(map (+1) nat)

merge :: [Int] -> [Int] -> [Int]
merge [] ys = ys
merge xs [] = xs
merge (x:xs) (y:ys) | x<y = x:(merge xs (y:ys))
                    | otherwise = y:(merge (x:xs) ys)

msort :: [Int] -> [Int]
msort []  = []
msort [x] = [x]
msort xs  = merge (msort (fst a)) (msort (snd a))
            where a = divide xs

divide :: [a] -> ([a],[a])
divide [] = ([],[])
divide (x:[]) = ([x],[])
divide (x:y:xs) = (x:(fst a),y:(snd a)) 
                where a = divide xs
