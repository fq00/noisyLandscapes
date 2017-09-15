library("ggplot2")
library("scales")
library("grid")

#manually inserted data

GA <- c(2658,2524,2639,4087,5156,6731,9102,10263,11717,13501,
        16973,17001,18967,22327,25274,28422,32029,30818,32716,
        36421,38901,41067,46343,46626,52388,53057,56904,60083,
        62589,66903,73932,71705,76823,80150,87239,90978,90745,
        95629,100059,104876,109616,113049,114097,121543,118216,
        126813,135396,138852,136543,148781,151520)
EA <- c(2788,4425,6278,5389,9807,9322,15414,18806,21908,28203,
        33092,40098,48277,53951,70475,86193,92733,108499,113988,
        141543,154399,181143,207985,233772,261448,268653,317152,
        364197,384529,439602,478758,520500,548044,593836,643851,
        721155,770354,775012,900246,1026495,1050388,1070928,1329791,
        1184631,1645082,1591511,1606271,1732347,1951967,2150697,2563121)
MMASib <- c(1205,1267,1134,1262,1115,1258,1283,1318,1411,1556,1558,
            1660,1736,1961,2090,2444,2146,2512,2482,2794,2769,3035,
            3307,3556,3499,3598,3798,4342,4435,4572,4631,5012,5292,
            5259,6234,5919,6354,6281,6939,6929,6920,8194,8122,8043,
            8868,8812,9650,9497,9558,10320,10272)

#import and clean data

setwd("..")
rowData <- read.csv2(file = "~/Runtime/cGA_runtime.txt", header = TRUE, sep = " ")
K = as.numeric(as.character(rowData$K))
RUNTIME = as.numeric(as.character(rowData$RUNTIME))
SIGMA = as.numeric(as.character(rowData$SIGMA))
i = 1
cGA = NA
for (sd in unique(SIGMA)){
  data = data.frame(k = unique(K[which(sd == SIGMA)]), 
                    mean = as.numeric(lapply(split(RUNTIME[which(sd == SIGMA)], K[which(sd == SIGMA)]), mean)), 
                    sd = as.numeric(lapply(split(RUNTIME[which(sd == SIGMA)], K[which(sd == SIGMA)]), sd)))
  
  cGA[i] = data[which(data$mean == min(data$mean)), 2]
  rm(data)
  i = i + 1
}
rm(i, K, rowData, RUNTIME, sd)
SIGMA = unique(SIGMA)

#find optimal re-sampling

myInterpolationEA = function(x, r){
  
  y = NA
  for(i in 1:length(r)){
    fit = x/sqrt(r[i])
    y[i] = exp(7.18781 + 2.38118*sqrt(fit))
  }
  return(y)
  
}

myInterpolationGA = function(x, r){
  
  y = NA
  for(i in 1:length(r)){
    fit = x/sqrt(r[i])
    y[i] = exp(7.18781 + 1.46010*sqrt(fit))
  }
  return(y)
  
}

#find optimal resampling

i = 1
r = NA
EA_resampling = NA
for(sd in SIGMA[1:51]){
  r[i] = which(seq(1:100)*myInterpolationEA(sd, seq(1:100)) == min(seq(1:100)*myInterpolationEA(sd,seq(1:100))))
  EA_resampling[i] = r[i]*myInterpolationEA(sd,r[i])
  i = i + 1
}
i = 1
w = NA
GA_resampling = NA
for(sd in SIGMA[1:51]){
  w[i] = which(seq(1:100)*myInterpolationGA(sd, seq(1:100)) == min(seq(1:100)*myInterpolationGA(sd,seq(1:100))))
  GA_resampling[i] = w[i]*myInterpolationGA(sd,w[i])
  i = i + 1
}


#re-evaluation runtime

cbbPalette <- c("#E69F00", "#56B4E9", "#009E73", "#F0E442", "#0072B2", "#D55E00")
greeks <- c("EA[no resampling]", "EA[resampling]", "GA[no resampling]",  "GA[resampling]", "cGA", "MMASib")
SIGMA = SIGMA[1:51]

g <- ggplot()
g <- g + geom_point(aes(x = SIGMA, y = EA, col = "EA", shape = "EA"))
g <- g + geom_point(aes(x = SIGMA, y = EA_resampling, col = "EA_resampling", shape = "EA_resempling"))
g <- g + geom_point(aes(x = SIGMA, y = GA, col = "GA", shape = "GA"))
g <- g + geom_point(aes(x = SIGMA, y = GA_resampling, col = "GA_resampling", shape = "GA_resempling"))
g <- g + geom_point(aes(x = SIGMA, y = cGA[1:51], col = "cGA", shape = "cGA"))
g <- g + geom_point(aes(x = SIGMA, y = MMASib, col = "MMASib", shape = "MMASib"))
g <- g + geom_line(aes(x = SIGMA, y = EA, col = "EA", shape = "EA"))
g <- g + geom_line(aes(x = SIGMA, y = EA_resampling, col = "EA_resampling", shape = "EA_resempling"))
g <- g + geom_line(aes(x = SIGMA, y = GA, col = "GA", shape = "GA"))
g <- g + geom_line(aes(x = SIGMA, y = GA_resampling, col = "GA_resampling", shape = "GA_resempling"))
g <- g + geom_line(aes(x = SIGMA, y = cGA[1:51], col = "cGA", shape = "cGA"))
g <- g + geom_line(aes(x = SIGMA, y = MMASib, col = "MMASib", shape = "MMASib"))
g <- g + xlab("noise standard deviation")
g <- g + scale_x_continuous()
g <- g + ylab("run time [sample mean]")
g <- g + scale_shape_manual(name = "Algorithm", values=c(0,1, 2, 3, 4, 5), labels = greeks)
g <- g + scale_colour_manual(name = "Algorithm", values=cbbPalette, label = greeks) #+ scale_colour_hue(name = "Algorithm", labels=greeks) 
g <- g + theme_bw()
g <- g + theme(panel.grid.major = element_line(colour = "#999999"))
g <- g + theme(panel.grid.minor = element_line(colour = "#666666", linetype = "dotted"))
g <- g + theme(panel.border = element_rect(colour = "black"))
g <- g + theme(legend.position = c(0.20, 0.8))
g <- g + ylim(0, EA[26])
g <- g + theme(legend.background = element_rect(colour = "black"))
g <- g + theme(legend.text = element_text(size = 14))
g <- g + theme(legend.title = element_text(size=14, face = "bold"))

setwd("..")
setwd("..")
pdf("~/Paper/Figures/reEvaluationRuntime.pdf", width = 6.5, height = 5.5)
g
dev.off()
rm(greeks, g)

#re-sampling trend (not present in final version)

greeks <- c("EA", "GA", "cGA", "MMASib")

g <- ggplot()
g <- g + geom_point(aes(x = SIGMA, y = log10(EA)/(log10(seq(2,52))), col = "EA", shape = "EA"))
g <- g + geom_point(aes(x = SIGMA, y = log10(GA)/(log10(seq(2,52))), col = "GA", shape = "GA"))
g <- g + geom_point(aes(x = SIGMA, y = log10(cGA[1:51])/(log10(seq(2,52))), col = "cGA", shape = "cGA"))
g <- g + geom_point(aes(x = SIGMA, y = log10(MMASib)/(log10(seq(2,52))), col = "MMASib", shape = "MMASib"))
g <- g + geom_line(aes(x = SIGMA, y = log10(EA)/(log10(seq(2,52))), col = "EA", shape = "EA"))
g <- g + geom_line(aes(x = SIGMA, y = log10(GA)/(log10(seq(2,52))), col = "GA", shape = "GA"))
g <- g + geom_line(aes(x = SIGMA, y = log10(cGA[1:51])/(log10(seq(2,52))), col = "cGA", shape = "cGA"))
g <- g + geom_line(aes(x = SIGMA, y = log10(MMASib)/(log10(seq(2,52))), col = "MMASib", shape = "MMASib"))
g <- g + xlab("noise standard deviation")
g <- g + scale_x_continuous()
g <- g + scale_y_log10(breaks = trans_breaks("log10", myFun),
                       labels = trans_format("log10", function(x) 10^x))
g <- g + ylab("# optimal re-sampling")
g <- g + scale_colour_hue(name = "Algorithm", labels=greeks) + scale_shape_manual(name = "Algorithm", values=c(15, 17, 18, 19), labels = greeks)
g <- g + theme_bw()
g <- g + theme(panel.grid.major = element_line(colour = "#999999"))
g <- g + theme(panel.grid.minor = element_line(colour = "#666666", linetype = "dotted"))
g <- g + theme(panel.border = element_rect(colour = "black"))
g <- g + theme(legend.position = c(0.9, 0.85))
g <- g + theme(legend.background = element_rect(colour = "black"))

pdf("~/Paper/Figures/runtimePoly.pdf", width = 6.5, height = 5.5)
g
dev.off()
rm(greeks, g)

#re-sampling sweet-spot

v = NA
for (i in 1:125)
  v[i] = i*myInterpolation(5/sqrt(i), i)
z = which(v == min(v))

g <- ggplot()
g <- g + geom_point(aes(x = seq(1:125), y = v, shape = "a"))
g <- g + geom_line(aes(x = seq(1:125), y = v))
g = g + geom_vline(xintercept = z, colour="blue", linetype = "longdash")
g = g + geom_text(aes(x = 10, y = 190000, label = "r = 7"), colour = "blue")
g <- g + xlab("# optimal re-sampling")
g <- g + scale_x_log10()
g = g + scale_shape_discrete(solid=F, guide = "none")
g <- g + ylab("run time")
g = g + theme_bw()
g = g + theme(panel.grid.major = element_line(colour = "#999999"))
g = g + theme(panel.grid.minor = element_line(colour = "#666666", linetype = "dotted"))

pdf("~/Paper/Figures/reSamplingSweetSpot.pdf", width = 6.5, height = 5.5)
g
dev.off()
rm(g)

#re-sampling trend

m = NA
for (i in 1:length(SIGMA)){
  v = NA
  for(j in 1:1000){
    v[j] = j*myInterpolation(SIGMA[i]/sqrt(j), j)
  }
  m[i] = which(min(v) == v)
}

g <- ggplot()
g <- g + geom_point(aes(x = SIGMA, y = m, shape = "a"))
g <- g + geom_line(aes(x = SIGMA, y = m))
g <- g + geom_vline(xintercept = 5.0, colour="blue", linetype = "longdash")
g <- g + geom_text(aes(x = 4.5, y = 9, label = "r = 7"), colour = "blue")
g <- g + scale_shape_discrete(solid=F, guide = "none")
g <- g + xlab("posterior noise standard deviation")
g <- g + ylab("re-sampling sweet spot")
g <- g + theme_bw()
g <- g + theme(panel.grid.major = element_line(colour = "#999999"))
g <- g + theme(panel.grid.minor = element_line(colour = "#666666", linetype = "dotted"))
g <- g + theme(panel.border = element_rect(colour = "black"))

pdf("~/reSamplingTrend.pdf", width = 6.5, height = 5.5)
dev.off()
rm(g)

rm(comp, cbbPalette, myInterpolation1, cGA, EA, GA_resampling, EA_resampling, GA, i, j, m , MMASib, r, sd, SIGMA, v, w, z, myInterpolation)
