#load libraries

library("ggplot2")
library("scales")
library("grid")

#parameters

min = 6
center = 4
max = 8

step = 1
length = 100

#import and clean data

data <- read.csv(file = "Parameter_Calibration/GA_parameter_calibration.txt", header = TRUE, sep = " ", skip = 14)
dataPlot <- data.frame()

i <- NA
row <- min
for (i in 1:length){

  dataPlot <- rbind(dataPlot, data[data$MU == row,])
  if (i < center) 
    row <- row + 1
  else{
    row <- row + step
    step <- min(step+2, max)
  }
  
}

dataPlot <- dataPlot[2:nrow(dataPlot),]
dataPlot$MU <- as.factor(dataPlot$MU)
rm(data)

#generate plot

scientific_10 <- function(x) {
  parse(text=gsub("e", " %*% 10^", scientific_format()(x)))
}

png("Parameter_Calibration/GA_parameter_calibration.png", width = 1920, height = 1200, units = "px")
g <- NA
g <- qplot(x = MU, y = N_FITNESS_EVALUATIONS, data = dataPlot, geom="boxplot") 
#g <- g + geom_vline(xintercept = 4, colour="grey50", linetype = "longdash", position = "identity")
#g <- g + geom_text(aes(x=4.5, y=300000, label="min == 9", group=NULL), size = 5, color = "grey50", parse = T)
g <- g + scale_y_log10(label = scientific_10)
g <- g + theme(plot.margin = unit(c(1,3,1, 1), "cm"))
g <- g + xlab("\n# parents\n")
g <- g + ylab("\n# fitness evaluations\n")
g <- g + ggtitle("\nParameter calibration for the (mu + 1)-EA\nsolving binary OneMax with added posterior noise\n(variance = 10, re-evaluations = 1, seed = 1)\n")
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