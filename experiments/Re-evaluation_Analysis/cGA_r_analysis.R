#load libraries

library("ggplot2")
library("scales")
library("grid")

#parameters

min = 1
center = 4
max = 8

step = 2
length = 15

maximum = 1000

#import and clean data

data <- read.csv(file = "Re-evaluation_Analysis/cGA_r_analysis.txt", header = TRUE, sep = " ", skip = 14)
dataPlot <- data.frame()

i <- NA
k <- NA
row <- min
for (i in 1:length){
  
  dataPlot <- rbind(dataPlot, data[data$N_RE_EVALUATIONS == row,])
  
  if (i < center) 
    row <- row + 1
  else if (i == center)
    row <- row + 2
  else{
    row <- row + step
    step <- min(step*2, max)
  }
  
}

dataPlot <- dataPlot[2:nrow(dataPlot),]
dataPlot$N_RE_EVALUATIONS <- as.factor(dataPlot$N_RE_EVALUATIONS)
rm(data)

#generate boxplot

scientific_10 <- function(x) {
  parse(text=gsub("e", " %*% 10^", scientific_format()(x)))
}

png("Re-evaluation_Analysis/cGA_r_analysis.png", width = 1920, height = 1200, units = "px")
g <- NA
g <- qplot(x = N_RE_EVALUATIONS, y = N_FITNESS_EVALUATIONS, data = dataPlot, geom="boxplot") 
g <- g + scale_y_log10(label = scientific_10)
g <- g + theme(plot.margin = unit(c(1,3,1, 1), "cm"))
g <- g + xlab("\n# re-evaluations\n")
g <- g + ylab("\n# fitness evaluations\n")
g <- g + ggtitle("\nRe-evaluation analysis for the cGA\nsolving binary OneMax with added posterior noise\n(K = 25, variance = 100, seed = 1)\n")
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
rm(i)
rm(length)
rm(max)
rm(min)
rm(row)
rm(step)
rm(scientific_10)