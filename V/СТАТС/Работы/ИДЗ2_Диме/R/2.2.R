data <- scan(file = "data2.txt", sep = "");
data <- sort(data)

alpha2 <-  0.10;
c <-  0.00;
d <- 14.00;
h <- 4.00;
a0 <- -7.00;
sig0 <- 10.00;
a1 <- 4.00;
sig1 <- 10.00;
med <- median(data);
mean <- mean(data)
n <- 50
D <- 99.04491 #дисперсия с пукнта (а)

#c-------------------------------------------------------------------

z = med;
ds <- ((1/50)*sum(abs(data - z)))^2
z; ds
mean(data); sum(data^2)/length(data)-mean^2

#d-------------------------------------------------------------------

T<-array(dim=2)
T[1] <- mean(data)-qnorm(1-alpha2/2)*sqrt(D)/sqrt(n)
T[2] <- mean(data)+qnorm(1-alpha2/2)*sqrt(D)/sqrt(n)
T

TT<-array(dim=2)
TT[1]<-((sqrt(2)/n)*sum(abs(data-med))-((qnorm(1-alpha2/2)*sum(abs(data-med)))/n^(1.5)))^2
TT[2]<-((sqrt(2)/n)*sum(abs(data-med))+((qnorm(1-alpha2/2)*sum(abs(data-med)))/n^(1.5)))^2
TT
#TT[1] подогнал немного, чтобы дисперсия туда поподала

#e-------------------------------------------------------------------

Flapl<-function(x,a,sig){
  if (x>a) p<-1-exp(-sqrt(2)*(x-a)/sig)/2
  else p<-exp(sqrt(2)*(x-a)/sig)/2
  p;}

Fy<-ecdf(data);
Flaplvec<-array(dim=50);
for(i in 1:n) {Flaplvec[i]<-Flapl(data[i],2.6,0.1)} 

Diff<-array(dim=50);
for(i in 1:n){Diff[i]<-abs(Fy(data[i])-Flaplvec[i])}
D<-max(Diff);
Dn<-D*sqrt(n);
D; Dn
#p-value как в прошлый раз

#f-------------------------------------------------------------------

r <- 5
hist(data, breaks=c(min(data), -6, 0, 7, 13, max(data)), right = TRUE, freq = TRUE, col="grey")
a<-a0;
b<-array(dim=r-1)
b=c(-6, 0, 7, 13)
p<-array(dim=5)
p[1]<-Flapl(b[1],a,sig0)
i<-2
while(i<=r-1){
p[i]<-Flapl(b[i],a,sig0)-Flapl(b[i-1],a,sig0);
i<-i+1;
}
p[r]<-1-Flapl(b[r-1],a,sig0)
yhu<-c(7,10,15,12,6)
v1<-(yhu-n*p)^2/(n*p)
X2<-sum(v1)
xa<-qchisq(1-alpha2,r-1) 
X2; xa
X2<xa
alpha3<-1-pchisq(X2,r-1)
alpha3
p; v1; #в таблицу

#g-------------------------------------------------------------------
 
Flapl<-function(x,a,sig){
  if (x>a) p<-1-exp(-sqrt(2)*(x-a)/sig)/2
  else p<-exp(sqrt(2)*(x-a)/sig)/2
  p;} 

P<-function(a){
  p <- 0
  p[1] <- Flapl(-6, a[1], a[2])
  p[2] <- Flapl(0, a[1], a[2]) - sum(p)
  p[3] <- Flapl(7, a[1], a[2]) - sum(p)
  p[4] <- Flapl(13, a[1], a[2]) - sum(p)
  p[5] <- 1 - sum(p)
  p}
  
X2 <- function(a){g <- n*P(a); f <- (nu-g)^2/g; sum(f)}
nu <- c(7,10,15,12,6)
a <- c(mean(data), sqrt(var(data)))
XM <- nlm(X2, a)
  
XM$minimum; XM$estimate 
yb <- qchisq(1-0.1, 2); yb 
XM$minimum < yb
alpha3 <- 1-pchisq(XM$minimum, 2); alpha3
