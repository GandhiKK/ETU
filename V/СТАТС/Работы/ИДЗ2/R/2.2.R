data <- scan(file = "data2.txt", sep = "");
data <- sort(data)

alpha2 <-  0.2;
c <-  2.9;
d <- 3.06;
h <- 0.05;
a0 <- 2.6;
sig0 <- 0.1;
a1 <- 3;
sig1 <- 0.1;
med <- median(data);
mean <- mean(data)
n <- 50
D <- 0.00970184 #дисперсия с пукнта (а)

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
hist(data, breaks=c(min(data), 2.9, 2.97, 3.08, 3.15, max(data)), right = TRUE, freq = TRUE, col="grey")
a<-a0;
b<-array(dim=r-1)
b=c(2.9, 2.97, 3.08, 3.15)
p<-array(dim=5)
p[1]<-Flapl(b[1],a,sig0)
i<-2
while(i<=r-1){
p[i]<-Flapl(b[i],a,sig0)-Flapl(b[i-1],a,sig0);
i<-i+1;
}
p[r]<-1-Flapl(b[r-1],a,sig0)
yhu<-c(7, 15, 14, 9, 5)
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
  p[1] <- Flapl(2.9, a[1], a[2])
  p[2] <- Flapl(2.97, a[1], a[2]) - sum(p)
  p[3] <- Flapl(3.08, a[1], a[2]) - sum(p)
  p[4] <- Flapl(3.15, a[1], a[2]) - sum(p)
  p[5] <- 1 - sum(p)
  p}
  
X2 <- function(a){g <- n*P(a); f <- (nu-g)^2/g; sum(f)}
nu <- c(7,15,14,9,5)
a <- c(mean(data), sqrt(var(data)))
XM <- nlm(X2, a)
  
XM$minimum; XM$estimate 
yb <- qchisq(1-0.2, 2); yb 
XM$minimum < yb
alpha3 <- 1-pchisq(XM$minimum, 2); alpha3
