library("ggplot2")
library("scales")
library("grid")

setwd("..")
CGA <- read.csv2("~/Runtime/cGA_runtime_N.txt", sep=" ")
MMASib <- read.csv2("~/Runtime/MMASib_runtime_N.txt", sep=" ", skip = 14)

#data cleaning

myMeanCGA = function(x){
  l = split(x$RUNTIME, x$K)
  mn = as.integer(as.character(lapply(l, mean)))
  mysd = NA
  for(i in 1:length(names(l))){
    mysd[i] = sd(l[[i]][which(l[[i]] < 10000)])
    
  }
  return(c(min(mn), min(mysd)))
}
l = split(CGA, CGA$n)
y = NA
w = NA
for (i in 1:length(names(l))){
  y[i] = myMeanCGA(l[[i]])[1]
  w[i] = myMeanCGA(l[[i]])[2]
}
z = as.numeric(as.character(lapply(split(MMASib[[6]], MMASib[[1]]), mean)))
v = as.numeric(as.character(lapply(split(MMASib[[6]], MMASib[[1]]), sd)))
               
#plot data in the nTrend figure

greeks <- list(bquote(cGA), bquote(MMASib))
cbbPalette <- c("#0072B2", "#D55E00")

k = abs(y+z)/2
mod = lm(k ~ unique(CGA$n))

g <- ggplot()
g <- g + geom_point(aes(unique(CGA$n), y, col = "cGA", shape = "cGA", size = w))
g <- g + geom_point(aes(unique(CGA$n), z, col = "MMASib", shape = "MMASib", size = v))
g <- g + geom_line(aes(unique(CGA$n), y, col = "cGA"))
g <- g + geom_line(aes(unique(CGA$n), z, col = "MMASib"))
g <- g + geom_line(aes(unique(CGA$n), predict(mod)), col = "gray")
g <- g + xlab("problem size")
g <- g + ylab("run time [sample mean]")
g <- g + scale_size_continuous(guide = "none")
g <- g + scale_colour_manual(name = "Algorithm", values = cbbPalette, labels=greeks) 
g <- g + scale_shape_manual(name = "Algorithm", values=c(4, 5), labels = greeks)
g <- g + theme_bw()
g <- g + theme(panel.grid.major = element_line(colour = "#999999"))
g <- g + theme(panel.grid.minor = element_line(colour = "#666666", linetype = "dotted"))
g <- g + theme(panel.border = element_rect(colour = "black"))
g <- g + theme(legend.position = c(0.115, 0.9))
g <- g + theme(legend.text = element_text(size = 14))
g <- g + theme(legend.title = element_text(size=14, face = "bold"))
g <- g + theme(legend.background = element_rect(colour = "black"))
g

setwd("..")
setwd("..")
pdf("~/Paper/Figures/nTrend.pdf", width = 6.5, height = 5.5)
g
dev.off()