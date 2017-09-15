library(ggplot2)

setwd("..")
EA <- read.csv2("~/Runtime/EA_runtime.txt", sep=" ", skip = 14)
GA <- read.csv2("~/Runtime/GA_runtime.txt", sep=" ", skip = 14)

shape <- as.factor(c(1,2))

EA$SIGMA <- as.double(as.character(EA$SIGMA))
GA$SIGMA <- as.double(as.character(GA$SIGMA))

greeks <- list(bquote(mu - EA), bquote(mu - GA))
cbbPalette <- c("#E69F00", "#009E73")

g <- ggplot(data = GA)
g <- g + geom_point(aes(x = GA$SIGMA, y = GA$OPTIMAL_MU, colour = "GA", shape = "GA"), size = 3)
g <- g + geom_point(aes(x = EA$SIGMA, y = EA$OPTIMAL_MU, colour = "EA", shape = "EA"), size = 3)
g <- g + xlab("noise standard deviation")
g <- g + ylab("optimal parameter [sample mean]")
g <- g + scale_colour_manual(name = "Parameter", values = cbbPalette, labels=greeks) + scale_shape_manual(name = "Parameter", values=c(0, 2), labels = greeks)
g <- g + theme_bw()
g <- g + theme(panel.grid.major = element_line(colour = "#999999"))
g <- g + theme(panel.grid.minor = element_line(colour = "#666666", linetype = "dotted"))
g <- g + theme(panel.border = element_rect(colour = "black"))
g <- g + theme(legend.position = c(0.12, 0.88))
g <- g + theme(legend.text = element_text(size = 14))
g <- g + theme(legend.title = element_text(size=14, face = "bold"))
g <- g + theme(legend.background = element_rect(colour = "black"))

setwd("..")
setwd("..")
pdf("~/Paper/Figures/optimalParameter1.pdf", width = 6.5, height = 5.5)
g
dev.off()

MMASib <- read.csv2("~/Documents/Server/Reeval/Results/Runtime/MMASib_runtime.txt", sep=" ", skip = 14, nrows = 51)
CGA <- read.csv2("/Users/fq00/Desktop/new_Reeval/cGA[runtime].txt", sep=" ")

cbbPalette <- c("#0072B2", "#D55E00", "#CC79A7")
greeks <- list(bquote(K - cGA), bquote(lambda - MMASib),bquote(rho - MMASib))

MMASib$SIGMA <- as.double(as.character(MMASib$SIGMA))
MMASib$OPTIMAL_N_ANTS <- as.double(as.character(MMASib$OPTIMAL_N_ANTS))
MMASib$OPTIMAL_RHO <- as.double(as.character(MMASib$OPTIMAL_RHO))

CGA$SIGMA = as.numeric(as.character(CGA$SIGMA))
CGA$K = as.numeric(as.character(CGA$K))
CGA$RUNTIME = as.numeric(as.character(CGA$RUNTIME))

k = NA
i = 1
for (x in unique(CGA$SIGMA)){
  m = min(unique(CGA[which(CGA$SIGMA == x), 2]))
  for (y in unique(CGA[which(CGA$SIGMA == x), 2])){
    if (mean(CGA[which(CGA$SIGMA == x & CGA$K == y), 3]) < mean(CGA[which(CGA$SIGMA == x & CGA$K == m), 3])) m = y
  }
  k[i] = m
  i = i + 1
}


h <- ggplot()
h <- h + geom_point(aes(x = MMASib$SIGMA, y = k[1:length(MMASib$SIGMA)], shape = "1", colour = "1"), size = 3)
h <- h + geom_point(aes(x = MMASib$SIGMA, y = MMASib$OPTIMAL_N_ANTS, shape = "2", colour = "2"), size = 3)
h <- h + geom_point(aes(x = MMASib$SIGMA, y = MMASib$OPTIMAL_RHO, shape = "3", colour = "3"), size = 3)
h <- h + xlab("noise standard deviation")
h <- h + ylab("optimal parameter [sample mean]")
h <- h + scale_y_log10()
h <- h + scale_colour_manual(name = "Parameter", values = cbbPalette, labels=greeks) + scale_shape_manual(name = "Parameter", values=c(4, 5, 6), labels = greeks)
h <- h + theme_bw()
h <- h + theme(panel.grid.major = element_line(colour = "#999999"))
h <- h + theme(panel.grid.minor = element_line(colour = "#666666", linetype = "dotted"))
h <- h + theme(panel.border = element_rect(colour = "black"))
h <- h + theme(legend.position = c(0.16, 0.4))
h <- h + theme(legend.text = element_text(size = 14))
h <- h + theme(legend.title = element_text(size=14, face = "bold"))
h <- h + theme(legend.background = element_rect(colour = "black"))
h

pdf("/Users/fq00/Documents/Server/Reeval/Paper/Figures/optimalParameter2.pdf", width = 6.5, height = 5.5)
h
dev.off()

rm(CGA, EA, GA, MMASib, cbbPalette, g, greeks, h, i, k, m, shape, x, y)