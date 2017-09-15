#load libraries

library("ggplot2")
library("scales")
library("grid")

#parameters

min = 3
center = 10
max = 1

step = 1
length = 100

#import and clean data

data <- read.csv(file = "Variance_Analysis/MMASib_variance_analysis.txt", header = TRUE, sep = " ", skip = 14)
dataPlot <- data[data$SIGMA <= sqrt(500),]
dataPlot$SIGMA <- round(dataPlot$SIGMA^2, 2)
dataPlot$SIGMA <- as.factor(dataPlot$SIGMA)
rm(data)

#generate plot

scientific_10 <- function(x) {
  parse(text=gsub("e", " %*% 10^", scientific_format()(x)))
}

png("Variance_Analysis/MMASib_variance_analysis.png", width = 1920, height = 1200, units = "px")
g <- NA
g <- qplot(x = SIGMA, y = N_FITNESS_EVALUATIONS, data = dataPlot, geom="boxplot") 
g <- g + theme(plot.margin = unit(c(1,3,1, 1), "cm"))
g <- g + xlab("\nnoise variance\n")
g <- g + scale_y_log10("\n# fitness evaluations\n")
g <- g + ggtitle("\nNoise variance analysis for the MMASib\nsolving binary OneMax with added posterior noise\n(ants = 5, evaporation = 0.45, re-evaluations = 10, seed = 1)\n")
g <- g + theme(plot.title = element_text(face="bold", size=30)) 
g <- g + theme(axis.title = element_text(size=20))
g <- g + theme(axis.text.x = element_text(size=15))
g <- g + theme(axis.text.y = element_text(size=15))
g
dev.off()

#clean-up

rm(center)
rm(dataPlot)
rm(g)
rm(length)
rm(max)
rm(min)
rm(scientific_10)
rm(step)