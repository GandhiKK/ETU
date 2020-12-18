data <- scan(file = "data2.txt", sep = "");
data <- sort(data)

alpha2 <-  0.2;
c <-  2.90;
d <- 3.06;
h <- 0.05;
a0 <- 2.60;
sig0 <- 0.10;
a1 <- 3.00;
sig1 <- 0.10;

#a-------------------------------------------------------------------

axis_x <- unique(data)
table <- table(data)
axis_y <- c()

f<-function(data, t){z<-data[data<t]; length(z)/length(data)}
xu<-axis_x
yu<-0; for(i in 1:length(xu)) yu[i]<-f(data,xu[i]); yu[length(xu)+1]<-1
z<-stepfun(xu,yu)
plot(z,verticals=FALSE, main = "Эмпирическая функция распределения", ylab = "Fn(x)", pch=20)

hist (data, right = TRUE, freq = TRUE)
h1 <- hist(data)
lines(h1$counts ~ h1$mids, col="red")
rug(data)

#b-------------------------------------------------------------------

mean <- mean(data); Exp
Disp <- sum(data^2)/length(data)-mean^2; Disp
Med <- median(data); Med
asm <- sum((data-mean(data))^3)/length(data)/var(data)^(3/2); asm
exc <- sum((data-mean)^4)/length(data)/Disp^2-3; exc
p<-f(data,d)-f(data,c); p

#d-------------------------------------------------------------------

n <- length(data)
xal <- qnorm(1 - alpha2/2)
T <- array(dim=2)
T[1] <- mean - ((xal*sqrt(Disp))/sqrt(n-1))
T[2] <- mean + ((xal*sqrt(Disp))/sqrt(n-1))
T

#e-------------------------------------------------------------------

Fy<-ecdf(data);
Fnorm<-pnorm(data, a0, sig0)
Diff<-array(dim=50);
for(i in 1:n){Diff[i]<-abs(Fy(data[i])-Fnorm[i])}
D<-max(Diff);
Dn<-D*sqrt(n);
D; Dn
#ищите C = критическое значение распределения статистики Колмогорова (n, alpha2)
#Dn > C - отвергаем гипотезу, и наоборот
#p-value забыл откуда

#f-------------------------------------------------------------------

r<-5   #количество интервалов
a<-a0;
b<-array(dim=r-1) 
b=c(2.9, 2.97, 3.08, 3.15) #границы
hist(data, breaks=c(min(data), b, max(data)), right = TRUE, freq = TRUE, col="grey") 
p<-array(dim=r-1) 
p[1]<-pnorm(b[1], a, sig0)
i<-2
while(i<=r-1){
p[i]<-pnorm(b[i],a,sig0)-pnorm(b[i-1],a,sig0);
i<-i+1;}
 
p[r]<-1-pnorm(b[r-1],a,sig0)
yhu<-c(7, 15, 14, 9, 5) #частоты
v1<-(yhu-n*p)^2/(n*p)
X2<-sum(v1)
xa<-qchisq(1-alpha2,r-1)
X2; xa
X2 < xa
alpha3<-1-pchisq(X2, r-1)
alpha3;
p; v1; #в таблицу

#g-------------------------------------------------------------------
  
P<-function(a){
  p <- 0
  p[1] <- pnorm(2.9, a[1], a[2])
  p[2] <- pnorm(2.97, a[1], a[2]) - sum(p)
  p[3] <- pnorm(3.08, a[1], a[2]) - sum(p)
  p[4] <- pnorm(3.15, a[1], a[2]) - sum(p)
  p[5] <- 1 - sum(p)
  p}
  
X2 <- function(a){g <- n*P(a); f <- (nu-g)^2/g; sum(f)}
nu <- c(7, 15, 14, 9, 5)
a <- c(mean(data), sqrt(var(data)))
XM <- nlm(X2, a)

XM$minimum; XM$estimate  
yb <- qchisq(1-0.2, 2)  
XM$minimum < yb; yb
alpha3 <- 1-pchisq(XM$minimum, 2); alpha3
  
#h-------------------------------------------------------------------

C <- 0; 
C <- qnorm(alpha2, n*a0, sqrt(n)*sig0)
sum(data); C
sum(data) > C

C <- 0      
C <- qnorm(1-alpha2, n*a1, sqrt(n)*sig0)
sum(data); C
sum(data) > C
  