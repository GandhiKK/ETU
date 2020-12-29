#a
name <- c("John Davis", "Angela Williams", "Janice Markhammer", "Bullwinkle Moose", "Mary Rayburn", "Greg Knox")
sex <- c("Male", "Female", "Female", "Male", "Female", "Male")
age <- c(21, 23, 40, 35, 18, 20)
education <- c("Secondary", "Higher", NA, "Secondary", "Secondary", "Higher")
income <- c(125, 345, 50, 399, 136, 120)
df <- data.frame(name, sex, age, education, income)

#b
sex <- factor(sex)
print(is.factor(sex))
education <- factor(education)
print(is.factor(education))

#c
df$income_20 <- income * 1.2

#d
mean_income <- mean(income)
print(mean_income)

#e
df_ia <- df[order(df$age), c(3, 5)]
barplot(df_ia$income, names.arg = df_ia$age, xlab = "Age", ylab = "Income")
#barplot(df_ia$income)
#barplot(df_ia$age)

#f
df$income_S <- df$income + df$income_20

#g
df$income_M <- df$income*100/max(df$income)

#h
mean_male <- mean(subset(df, sex == "Male")$income)
mean_female <- mean(subset(df, sex == "Female")$income)

#i
df$income_20 <- NULL
