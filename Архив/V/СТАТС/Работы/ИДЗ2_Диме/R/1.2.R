data <- scan(file = "data1.txt", sep = "");
data <- sort(data)
alpha1 <- 0.01
a <- 1.27; b <- 3.69; 
lambda0 <- 4.00; lambda1 <- 3.00
n <- 50
axis_x <- unique(data)
table <- table(data)
axis_y <- c()

#c-------------------------------------------------------------------

library(maxLik)
LL <- function(t){ sum(dpois(data,t[1],log=TRUE)) }
ml <- maxNR(LL,start=c(1)) 
val <- ml$estimate; val

#d-------------------------------------------------------------------

mean <- mean(data)
T<-array(dim=2)
xal<-qnorm (1-alpha1/2); xal
((mean*(mean+1))/length(data))^(-1)
(mean*(mean+1))/length(data)
sqrt((mean*(mean+1))/length(data)) 
T[1]<-mean-xal*sqrt((mean*(mean+1))/length(data)) 
T[2]<-mean+xal*sqrt((mean*(mean+1))/length(data)) 
T

#e-------------------------------------------------------------------

r<-8   #количество интервалов
a <- lambda0
b<-array(dim=r-1) 
b=c(0,1,2,3,4,5,6,7) #границы
p<-array(dim=r-1) 
p[1]<-pgeom(b[1], 1/(a+1))
i<-2
while(i<=r-1){
  p[i]<-pgeom(b[i], 1/(a+1))-pgeom(b[i-1], 1/(a+1));
  i<-i+1;}
p[r]<-1-pgeom(b[r-1], 1/(a+1))
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
  p[1] <- pgeom(0, a)
  p[2] <- pgeom(1, a) - sum(p)
  p[3] <- pgeom(2, a) - sum(p)
  p[4] <- pgeom(3, a) - sum(p)
  p[5] <- pgeom(4, a) - sum(p)
  p[6] <- pgeom(5, a) - sum(p)
  p[7] <- pgeom(6, a) - sum(p)
  p[8] <- 1-sum(p)
  p}

X2 <- function(a){g <- n* P(a); f <- (nu-g)^2/g; sum(f)}
nu <- c(1,9,8,16,9,3,3,1) 
v1<-(nu-n*p)^2/(n*p)
XM <- nlm(X2, 1/5)
l = (1/XM$estimate)-1 ; l

XM <- nlm(X2, 1/(l+1))
round(p, digits=3); round(n*p, digits=3); round(yhu-n*p, digits=3); round(v1, digits=3); #в таблицу
xb<-qchisq(1-alpha1, r-3)  
XM$minimum; xb
XM$minimum<xb
alpha2<-1-pchisq(XM$minimum, r-3); alpha2
   