f :: Int -> Int 
f 1 = 1;
f n = f (n-1);

h :: Int -> Int
h 1 = 2;
h n = h (n-1)