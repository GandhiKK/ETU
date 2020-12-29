sz = 1000

x <- runif(sz, -1, 1)
y <- rnorm(sz)
z <- rnorm(sz, 0, 10)
t <- rnorm(sz, 0.01, 1)

print(t.test(x))
print(t.test(y))
print(t.test(z))
print(t.test(t))

print(t.test(x, y, paired = TRUE))
print(t.test(x, z, paired = TRUE))
print(t.test(x, t, paired = TRUE))
print(t.test(y, z, paired = TRUE))
print(t.test(y, t, paired = TRUE))
print(t.test(z, t, paired = TRUE))