#a
vocab <- read.csv("Vocab.csv")

#b
str(vocab)
summary(vocab)
print(is.factor(vocab$sex))

#c
with(vocab, {
  mean_all <<- mean(vocabulary)
  mean_male <<- mean(vocabulary[sex == "Male"])
  mean_female <<- mean(vocabulary[sex == "Female"])
})

#d
means <- aggregate(vocabulary ~ education, vocab, mean)
vocab.means <- as.vector(means$vocabulary)
vocab.names <- paste(means$education, "лет") 
names(vocab.means) <- vocab.names

#e
barplot(vocab.means, names.arg = vocab.names, ylab = "Vocab", las = 2, col="#69b3e5")

#f
means_for_sex <- aggregate(vocabulary ~ education + sex, vocab, mean)
edsex <- as.data.frame(cbind(means_for_sex$vocabulary[1:21], means_for_sex$vocabulary[22:42], means_for_sex$education[1:21]))

cols <- c("#69b3a2", "#69b3e5")
par(lwd = 5, las = 2)
barplot(t(edsex[c(1, 2)]), beside = TRUE, border = cols, col = "white",
  names.arg = paste(edsex$V3, "лет"), ylab = "Vocab", legend.text = c('Female','Male'),
  args.legend = list(text.col = cols, col = cols, border = cols, bty = "n", x = "topleft"))

#g
with(vocab, {
  x <<- vocabulary[sex == "Female" & education == 20]
  y <<- vocabulary[sex == "Male" & education == 20]
})
print(t.test(x, y))

#h
un <- sort(unique(vocab$year))
print(un)

#i
means_for_year <- aggregate(vocabulary ~ year + education, vocab, mean)
a <- subset(means_for_year, means_for_year$education == 0)

par(lwd = 2)
plot(a$year, a$vocabulary, type = "l", xlab = "Year", ylab = "Vocab", main = "Ed = 0")

plot(means_for_year$year[means_for_year$education == 0], means_for_year$vocabulary[means_for_year$education == 0], type = "l", xlab = "Year", ylab = "Vocab")
for (i in 1:20) {
  par(lwd = 1)
  lines(means_for_year$year[means_for_year$education == i], means_for_year$vocabulary[means_for_year$education == i])
}




