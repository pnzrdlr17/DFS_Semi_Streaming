reset
set terminal png size 680,640 enhanced font "arial,25"
location=ARG1
GType=ARG2

set output 'results/real/sc_optimized_stats/'.GType.'/plots/kpath_memory.png'

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Space Parameter K"
set xrange [0:10]
set xtics 0,1

set ylabel "Memory (MB)"
set yrange [50:270]
set ytics 0,60

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

# Full plot
plot "".location."kpath0.csv" using 1:3 with linespoints title 'kPathO', \
    "".location."kpath1.csv" using 1:3 with linespoints title 'kPath1', \
    "".location."kpath2.csv" using 1:3 with linespoints title 'kPath2', \
    "".location."kpathN.csv" using 1:3 with linespoints title 'kPathN'

unset multiplot