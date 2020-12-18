data1 <- scan(file = "data1.txt", sep = "")
data2 <- scan(file = "data2.txt", sep = "")
alpha1 <- 0.05; h <- 1.70; n <- 50

#a----------------------------------------------------

regr <- data.frame(x = data2, y = data1)

with(regr, {
  plot(x, y)
  abline(lm(y~x), col="red")
  title("Linear regression")
})

meanX <- mean(regr$x)
meanY <- mean(regr$y)

b1 <- (mean(regr$x*regr$y)-meanX*meanY)/(sum(regr$x^2)/n-meanX^2); b1
b0 <- meanY - b1*meanX; b0

#b----------------------------------------------------

s <- sum((regr$y-meanY)^2)/(n-2); s
eps <- regr$y - b1*regr$x - b0; eps

eps <- sort(eps)
k <- min(eps)-h/2
u <- (eps[n]-eps[1])/h
for (i in 2:(u+3)) k[i]=k[i-1]+h
hist(eps, breaks <- k)

#ебашь выборку на 6 зон
r <- 6
P <- function(a){
  p<-0
  p[1] <- pnorm(-3.4, 0, a)
  p[2] <- pnorm(-1.7, 0, a) - sum(p)
  p[3] <- pnorm(0, 0, a) - sum(p)
  p[4] <- pnorm(1.7, 0, a) - sum(p)
  p[5] <- pnorm(3.4, 0, a) - sum(p)
  p[6] <- 1 - sum(p)
  p}
X2 <- function(a){g<-n*P(a); f<-(nu-g)^2/g;sum(f)}
nu <- c(5, 8, 10, 15, 9, 3)
a <- c(sqrt(s))
XM <- nlm(X2, a)
XM$estimate^2; XM$minimum

xa <- qchisq(1- alpha1, r-1-1)
XM$minimum < xa

#Колыма
kolm.stat<-function(s){
  sres<-sort(eps)
  fdistr<-pnorm(sres,0,s)
  max(abs(c(0:(n-1))/n-fdistr),abs(c(1:n)/n-fdistr))
}
ks.dist<-nlm(kolm.stat, XM$estimate)
ks.dist$minimum; ks.dist$estimate^2 

plot(ecdf(eps), main = '')
points(sort(eps), pnorm(sort(eps),0,ks.dist$estimate),type="l", col="green", lwd=2)

#c----------------------------------------------------

X <- matrix(c(rep(1, 50), regr$x), nrow=2, byrow=TRUE)
C <- diag(2)
XXt <- X %*% t(X)
BVar <- t(C) %*% solve(XXt) %*% C
xal <- qt(1-alpha1/2, n-2); xal
b_0 <- BVar[1,1]
b_1 <- BVar[2,2]

b0lw <- b0 - xal*sqrt(s)*sqrt(BVar[1,1])
b0up <- b0 + xal*sqrt(s)*sqrt(BVar[1,1])
b0lw; b0up
b1lw <- b1 - xal*sqrt(s)*sqrt(BVar[2,2])
b1up <- b1 + xal*sqrt(s)*sqrt(BVar[2,2])
b1lw; b1up

BVar[1, 1] = b_1
BVar[2, 2] = b_0
BVar
Fis <- qf(1-alpha1, 2, n-2); Fis
ff <- Fis*2*s; ff
zn <- eigen(BVar)$values; zn
sqrt(ff/zn[1]); sqrt(ff/zn[2])

#d----------------------------------------------------

f <- (b1^2)/BVar[2, 2]/s; f
xFal<-qf(1-alpha1, 1, n-2); xFal
pv.f<-pf(f,1,n-2,lower.tail=FALSE); pv.f
f < xFal

#e----------------------------------------------------

B1 <- b1
B0 <- b0
coef <- coefficients(lm(regr$y~regr$x+I(regr$x^2)))
b1 <- as.numeric(coef[3])
b2 <- as.numeric(coef[2])
b3 <- as.numeric(coef[1])

with(regr, {
  plot(x, y)
  xu <- sort(unique(x))
  points(xu, B1*xu+B0, col="red", type='l', lwd=2)
  points(xu, b1*xu^2+b2*xu+b3, col="blue", type='l', lwd=2)
  title("Linear regression")
})

#f----------------------------------------------------

s <- sum((regr$y-b1*regr$x^2 - b2*regr$x - b3)^2)/(n-3); s
eps = regr$y-b1*regr$x^2 - b2*regr$x - b3; eps

eps <- sort(eps)
k <- min(eps)-h/2
u <- (eps[n]-eps[1])/h
for (i in 2:(u+2)) k[i]=k[i-1]+h
hist(eps, breaks <- k)

#ебашь выборку на 6 зон
r <- 6
P <- function(a){
  p<-0
  p[1] <- pnorm(-3.4, 0, a)
  p[2] <- pnorm(-1.7, 0, a) - sum(p)
  p[3] <- pnorm(0, 0, a) - sum(p)
  p[4] <- pnorm(1.7, 0, a) - sum(p)
  p[5] <- pnorm(3.4, 0, a) - sum(p)
  p[6] <- 1 - sum(p)
  p}
X2 <- function(a){g<-n*P(a); f<-(nu-g)^2/g;sum(f)}
nu <- c(4, 9, 10, 15, 9, 3)
a <- c(sqrt(s))
XM <- nlm(X2, a)
XM$estimate^2; XM$minimum

xa <- qchisq(1- alpha1, r-1-1)
XM$minimum < xa

#Колыма
kolm.stat<-function(s){
  sres<-sort(eps)
  fdistr<-pnorm(sres,0,s)
  max(abs(c(0:(n-1))/n-fdistr),abs(c(1:n)/n-fdistr))
}
ks.dist<-nlm(kolm.stat, XM$estimate)
ks.dist$minimum; ks.dist$estimate^2 

plot(ecdf(eps), main = '')
points(sort(eps), pnorm(sort(eps),0,ks.dist$estimate),type="l", col="green", lwd=2)

#g----------------------------------------------------

X <- matrix(c(rep(1, 50), regr$x, regr$x^2), nrow=3, byrow=TRUE)
C <- diag(3)
XXt <- X %*% t(X)
BVar <- t(C) %*% solve(XXt) %*% C
xal <- qt(1-alpha1/2, n-3); xal
b_1 <- BVar[1,1]
b_2 <- BVar[2,2]
b_3 <- BVar[3,3]

b1lw <- b1 - xal*sqrt(s)*sqrt(b_3)
b1up <- b1 + xal*sqrt(s)*sqrt(b_3)
b1lw; b1up

b2lw <- b2 - xal*sqrt(s)*sqrt(b_2)
b2up <- b2 + xal*sqrt(s)*sqrt(b_2)
b2lw; b2up

b3lw <- b3 - xal*sqrt(s)*sqrt(b_1)
b3up <- b3 + xal*sqrt(s)*sqrt(b_1)
b3lw; b3up

rotate <- function(x) t(apply(x, 2, rev))
BVar <- rotate(rotate(BVar))
BVar

Fis <- qf(1-alpha1, 3, n-3); Fis
ff <- Fis*3*s; ff
zn <- eigen(BVar)$values; zn
sqrt(ff/zn[1]); sqrt(ff/zn[2]); sqrt(ff/zn[3])

#h----------------------------------------------------

f <- (b1^2)/(BVar[3, 3]*s); f
xFal<-qf(1-alpha1, 1, n-3); xFal
f < xFal
pv.f<-pf(f,1,n-3,lower.tail=FALSE); pv.f


