#load libraries

library("ggplot2")
library("scales")
library("grid")

#import and clean data

data <- read.csv(file = "Variance_Analysis/cGA_variance_analysis.txt", header = TRUE, sep = " ", skip = 14)
data$SIGMA <- round(data$SIGMA^2, 2)

j <- NA
k <- 0
index <- seq(1, 9000, 600)
newSigma <-NA
for (j in index){
  newSigma[k] <- round(data$SIGMA[j], 2)
  k = k + 1
  
}

dataPlot <- data.frame()

i <- NA

for (i in newSigma)
  dataPlot <- rbind(dataPlot, data[data$SIGMA == i,])

dataPlot$SIGMA <- round(dataPlot$SIGMA^2, 2)
dataPlot$SIGMA <- as.factor(dataPlot$SIGMA)

#generate plot

scientific_10 <- function(x) {
  parse(text=gsub("e", " %*% 10^", scientific_format()(x)))
}

png("Variance_Analysis/cGA_variance_analysis.png", width = 1920, height = 1200, units = "px")
g <- NA
g <- qplot(x = SIGMA, y = N_FITNESS_EVALUATIONS, data = dataPlot, geom="boxplot") 
g <- g + theme(plot.margin = unit(c(1,3,1, 1), "cm"))
g <- g + scale_y_log10(label = scientific_10)
g <- g + xlab("\nnoise variance\n")
g <- g + ylab("\n# fitness evaluations\n")
g <- g + ggtitle("\nNoise variance analysis for the cGA\nsolving binary OneMax with added posterior noise\n(K = 25, re-evaluations = 10, seed = 1)\n")
g <- g + theme(plot.title = element_text(face="bold", size=30)) 
g <- g + theme(axis.title = element_text(size=20))
g <- g + theme(axis.text.x = element_text(size=15))
g <- g + theme(axis.text.y = element_text(size=15))
g
dev.off()

#clean-up

rm(dataPlot)
rm(g)
rm(scientific_10)
rm(index)
rm(i)
rm(j)
rm(k)
rm(newSigma)