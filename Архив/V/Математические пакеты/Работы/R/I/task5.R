sz <- 5

gen <- sample(c(0, 1), sz, replace = TRUE)

x <- rnorm(sz) # norm
y <- rexp(sz) # exp

gen[gen == 0] <- x[1:length(gen[gen==0])] #  0 -> first n numbers from norm
gen[gen == 1] <- y[1:length(gen[gen==1])] # 1 -> first m numbers from exp

print(gen)