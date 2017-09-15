#load libraries

library("ggplot2")
library("scales")
library("grid")

#import results

data <- read.csv("Parameter_Calibration/MMASib_parameter_calibration.txt", sep = " ", skip = 14)
data <- data[data$EVAPORATION >= 0.02 & data$N_ANTS <= 10, ]

#clean results

Evaporation <- rep(NA, length(unique(data$N_ANTS))*length(unique(data$EVAPORATION)))
Ants <- rep(NA, length(unique(data$N_ANTS))*length(unique(data$EVAPORATION)))
for (i in 1:length(unique(data$N_ANTS))){
  for (j in 1:length(unique(data$EVAPORATION))){
    Evaporation[length(unique(data$EVAPORATION))*(i-1)+j] <- unique(data$EVAPORATION)[j]
    Ants[length(unique(data$EVAPORATION))*(i-1)+j] <- unique(data$N_ANTS)[i]
  }
}

#compute mean

k <- 1
mean <- rep(NA, length(unique(data$N_ANTS))*length(unique(data$EVAPORATION)))
for (i in unique(Ants)){
  for (j in unique(Evaporation)){
    mean[k] <- mean(data$N_FITNESS_EVALUATIONS[data$N_ANTS == i & data$EVAPORATION == j])
    k <- k + 1
  }
}
data <- data.frame(Ants, Evaporation, mean)
data$Evaporation <- as.factor(data$Evaporation)

#make plot

scientific_10 <- function(x) {
  parse(text=gsub("e", " %*% 10^", scientific_format()(x)))
}
png("Parameter_Calibration/MMASib_parameter_calibration.png", width = 1920, height = 1200, units = "px")
g <- NA
g <- ggplot(data, aes(x=Ants,y=mean))
g <- g + geom_line(aes(colour=Evaporation))
g <- g + geom_point(aes(colour=Evaporation))
g <- g + ggtitle("\nParameter calibration for the MMASib\nsolving binary OneMax with added posterior noise\n(variance = 10, re-evaluation = 1, seed = 1)\n")
g <- g + ylab("\n# fitness evaluations (sample mean)\n")
g <- g + xlab("\n# ants\n")
g <- g + scale_y_continuous(label = scientific_10)
g <- g + theme(plot.title = element_text(face="bold", size=30)) 
g <- g + theme(axis.title = element_text(size=20))
g <- g + theme(axis.text.x = element_text(size=15))
g <- g + theme(axis.text.y = element_text(size=15))
g <- g + theme(legend.key.size = unit(1, "cm")) 
g <- g + theme(legend.title = element_text(size=20))
g <- g + theme(legend.text = element_text(size=15))
g
dev.off()

#clean-up

rm(Ants)
rm(data)
rm(Evaporation)
rm(g)
rm(i)
rm(j)
rm(k)
rm(mean)
rm(scientific_10)
