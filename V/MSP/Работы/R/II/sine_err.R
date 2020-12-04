#a
x <- seq(0, 2*pi, length.out = 1000)
y <- sin(x)
zn <- rnorm(1000, 0, 0.005)
z <- y+zn
#tab <- data.frame(x, y, z)
tab <- matrix(c(x, y, z), 1000, 3)

#b
df <- as.data.frame(rbind(head(tab, 100), tail(tab, 50)), row.names = 1:150)
names(df) <- c("x", "sinx", "sinxX")

#c
print(head(df, 5))

#d
print(tail(df, 5))

#e
plot(x, y, type="l", col="blue")
lines(x, z, col="red")


