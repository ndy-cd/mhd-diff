set terminal gif animate delay 7

set output 'animate.gif'
set yrange [0.01:1.2]
set xrange [0:100]

do for [i=0:80] { 
 plot 'output.txt' every :::i::i using 1:2 with lines lw 2
}
