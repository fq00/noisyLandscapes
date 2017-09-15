#load libraries

library("ggplot2")
library("scales")
library("grid")

#import and clean data

setwd("..")
rowData <- read.csv2(file = "~/Parameter_Calibration/cGA_parapeter_calibration.txt", header = TRUE, sep = " ")
K = as.numeric(as.character(rowData$K))
RUNTIME = as.numeric(as.character(rowData$RUNTIME))
SIGMA = as.numeric(as.character(rowData$SIGMA))

i = 1
x = y = z = NA
for (sd in unique(SIGMA)){
  data = data.frame(k = unique(K[which(sd == SIGMA)]), 
                    mean = as.numeric(lapply(split(RUNTIME[which(sd == SIGMA)], K[which(sd == SIGMA)]), mean)), 
                    sd = as.numeric(lapply(split(RUNTIME[which(sd == SIGMA)], K[which(sd == SIGMA)]), sd)))

  x[i] = sd
  y[i] = data[which(data$mean == min(data$mean)), 2]
  z[i] = data[which(data$mean == min(data$mean)), 3]
  rm(data)
  i = i + 1
}
rm(i, RUNTIME, SIGMA, sd)

#curve fitting
m = 0
n = 0
p = 0
q = 0
d1 = sqrt(sum((curve(x, m, n, y[1]) - y)^2))

fit = function(x,y){
  
  m = 0
  n = 0
  p = 0
  q = 0
  d1 = sqrt(sum((curve(x, m, n, y[1]) - y)^2))
  
  for (i in seq(0, 10, 0.1)){
    for (j in seq(0, 0.01, 0.000001)){
        d2 = sqrt(sum((curve(x, i, j, y[1]) - y)^2))
        if (d2 < d1) {
          m = i
          n = j
          d1 = d2
        }
    }
  }
  
  return(c(m,n))
  
}

curve = function(dom, a, b, e){
  r = NA
  i = 1
  for (x in dom){
    r[i] = b*x^a + + e
    i = i + 1
  }
  return (r)
}

w = curve(x, m, n, p, q, y[1])

#generate plot cGA runtime trend

scientific_10 <- function(x) {
  parse(text=gsub("e", " %*% 10^", scientific_format()(x)))
}

g <- ggplot(data = data.frame(x, y, z))
g <- g + geom_point(aes(x = x, y = y))
g <- g + geom_line(aes(x = x, y = w))
g <- g + xlab("K")
g <- g + ylab("run time [sample mean]")
g <- g + scale_colour_hue(name = "cGA run time", labels = c("Adjusted sample mean", "Sample mean"))
g <- g + theme(legend.position = c(0.67, 0.864))
g <- g + theme(legend.text = element_text(size = 14))
g <- g + theme(legend.title = element_text(size=14, face = "bold"))
g

setwd("..")
setwd("..")
pdf("~/Paper/Figures/cGA[parameter_tuning].pdf", width = 6.5, height = 5.5)
g
dev.off()

#clean-up

rm(conv, data, g, K, p, rect, RUNTIME, scientific_10)