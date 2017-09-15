#load libraries

library("ggplot2")
library("scales")
library("grid")

#import and clean data

dataPlot <- read.csv(file = "Runtime/EA_runtime.txt", header = TRUE, sep = " ", skip = 14)
dataPlot$SIGMA <- round(dataPlot$SIGMA^2, 2)

#generate plot

scientific_10 <- function(x) {
  parse(text=gsub("e", " %*% 10^", scientific_format()(x)))
}

png("Runtime/EA_runtime.png", width = 1920, height = 1200, units = "px")
g <- NA
g <- qplot(x = SIGMA, y = N_FITNESS_EVALUATIONS, data = dataPlot) 
g <- g + geom_point(size = 5)
g <- g + geom_smooth(method = loess)
g <- g + theme(plot.margin = unit(c(1,3,1, 1), "cm"))
g <- g + xlab("\nnoise variance\n")
g <- g + ylab("\nruntime for optimal parameters\n")
g <- g + ggtitle("\nRuntime analysis for the EA\nsolving binary OneMax with added posterior noise\n")
g <- g + theme(plot.title = element_text(face="bold", size=30)) 
g <- g + theme(axis.title = element_text(size=20))
g <- g + theme(axis.text.x = element_text(size=15))
g <- g + theme(axis.text.y = element_text(size=15))
g
dev.off()

#clean-up

rm(scientific_10)
rm(g)
rm(dataPlot)