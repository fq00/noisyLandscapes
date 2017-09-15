#load libraries

library("ggplot2")
library("scales")
library("grid")

#parameters

min = 11
center = 5
max = 100

step = 25
length = 15

#import and clean data

data <- read.csv(file = "Parameter_Calibration/cGA_parameter_calibration.txt", header = TRUE, sep = " ", skip = 14)
dataPlot <- data.frame()

i <- NA
row <- min
for (i in 1:length){
  
  dataPlot <- rbind(dataPlot, data[data$K == row,])
  if (i < center & i > 2) 
    row <- row + 4
  else if (i < center & i <= 2) 
    row <- row + 2
  else{
    row <- row + step
    step <- min(step*2, max)
  }
  
}

dataPlot <- dataPlot[2:nrow(dataPlot),]
dataPlot$K <- as.factor(dataPlot$K)
rm(data)

#generate plot

scientific_10 <- function(x) {
  parse(text=gsub("e", " %*% 10^", scientific_format()(x)))
}

png("Parameter_Calibration/cGA_parameter_calibration.png", width = 1920, height = 1200, units = "px")
g <- NA
g <- qplot(x = K, y = N_FITNESS_EVALUATIONS, data = dataPlot, geom="boxplot") 
#g <- g + geom_vline(xintercept = 4, colour="grey50", linetype = "longdash", position = "identity")
#g <- g + geom_text(aes(x=4.5, y=10000, label="min == 23", group=NULL), size = 5, color = "grey50", parse = T)
g <- g + scale_y_log10(label = scientific_10)
g <- g + theme(plot.margin = unit(c(1,3,1, 1), "cm"))
g <- g + xlab("\nK\n")
g <- g + ylab("\n# fitness evaluations\n")
g <- g + ggtitle("\nParameter calibration for the cGA\nsolving binary OneMax with added posterior noise\n(variance = 100, re-evaluations = 1, seed = 1)\n")
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
rm(scientific_10)
rm(step)