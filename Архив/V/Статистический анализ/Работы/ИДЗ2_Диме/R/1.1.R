data <- scan(file = "data1.txt", sep = "")
data <- sort(data)
alpha1 <- 0.01
a <- 1.27; b <- 3.69; 
lambda0 <- 4.00; lambda1 <- 3.00
n <- 50

#a-------------------------------------------------------------------

axis_x <- unique(data)
table <- table(data)
axis_y <- c()

f<-function(data, t){z<-data[data<t]; length(z)/length(data)}
xu<-axis_x
yu<-0; for(i in 1:length(xu)) yu[i]<-f(data,xu[i]); yu[length(xu)+1]<-1
z<-stepfun(xu,yu)
plot(z,verticals=FALSE, main = "Эмпирическая функция распределения", ylab = "Fn(x)", col='blue')
     
hist(data, breaks = c(axis_x, 8), col = "red", right = FALSE, freq = FALSE)
#не могу вспомнить как строить, 8 - следующее число псоле max(data)

#b-------------------------------------------------------------------

mean <- mean(data); mean
var <- sum(data^2)/length(data)-mean^2; var
Med <- median(data); Med
asm <- sum((data-mean(data))^3)/length(data)/var(data)^(3/2); asm
exc <- sum((data-mean)^4)/length(data)/var^2-3; exc
p<-f(data,b)-f(data,a); p

#c-------------------------------------------------------------------

library(maxLik)
LL <- function(t){sum(dpois(data,t[1],log=TRUE))}
ml <- maxNR(LL,start=c(1)) 
val <- ml$estimate; val

#d-------------------------------------------------------------------

xal<-qnorm (1-alpha1/2); xal
T<-array(dim=2)
T[1]<-mean-xal*sqrt(mean/length(data))
T[2]<-mean+xal*sqrt(mean/length(data)) 
T
#считал вручную как Сучков; тут немного отличается, но можете просто формулы оставить, а числа подставить свои

#e-------------------------------------------------------------------

r<-8   #количество интервалов
b<-array(dim=r-1) 
b=c(0,1,2,3,4,5,6,7) #границы
p<-array(dim=r-1) 
p[1]<-ppois(b[1], lambda0)
i<-2
while(i<=r-1){
  p[i]<-ppois(b[i], lambda0)-ppois(b[i-1], lambda0);
  i<-i+1;}
p[r]<-1-ppois(b[r-1], lambda0)
yhu<-c(1,9,8,16,9,3,3,1) 
v1<-(yhu-n*p)^2/(n*p)
X2<-sum(v1)
xa<-qchisq(1-alpha1,r-2)
X2; xa
X2 < xa
alpha2<-1-pchisq(X2, r-2)
alpha2;
round(p, digits=3); round(n*p, digits=3); round(yhu-n*p, digits=3); round(v1, digits=3); #в таблицу

#f-------------------------------------------------------------------

P <- function(a){
  p <- 0
  p[1] <- ppois(0, a)
  p[2] <- ppois(1, a) - sum(p)
  p[3] <- ppois(2, a) - sum(p)
  p[4] <- ppois(3, a) - sum(p)
  p[5] <- ppois(4, a) - sum(p)
  p[6] <- ppois(5, a) - sum(p)
  p[7] <- ppois(6, a) - sum(p)
  p[8] <- 1-sum(p)
  p}
X2 <- function(a){g <- n*P(a); f <- (nu-g)^2/g; sum(f)}
nu <- c(1,9,8,16,9,3,3,1)
XM <- nlm(X2, lambda0)

xal1 <- qchisq(1-alpha1, r-3);
XM$minimum; xal1
XM$minimum < xal1
max <- 1-pchisq(XM$minimum, r-3); max

#g-------------------------------------------------------------------

c<-0
alpha0 <- 1-ppois(c, lambda0*n)-dpois(c, lambda0*n)

while(alpha0 > alpha1) { c<-c+1; alpha0<-1-ppois(c,lambda0*n)-dpois(c, lambda0*n) }
p<-(alpha1-alpha0)/dpois(c,lambda0*n)
alpha0; c; p

sum(data); c
sum(data) > c

#меняем гипотезы

c<-0; 
alpha0 <- ppois(c, lambda1*n)

while(alpha0<alpha1){ c<-c+1; alpha0<-ppois(c,lambda1*n) }
c <- c-1
c
  
alpha0<-ppois(c,lambda1*n)
p<-(alpha1-alpha0)/(dpois(c,lambda1*n))
alpha0; c; p

sum(data); c
sum(data) > c
