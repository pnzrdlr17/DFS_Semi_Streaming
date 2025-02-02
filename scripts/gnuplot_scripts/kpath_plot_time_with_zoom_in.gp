reset
set terminal png size 680,640 enhanced font "arial,25"
location=ARG1
GType=ARG2

set output 'results/real/sc_optimized_stats/'.GType.'/plots/kpath_time_zoom.png'

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Space Parameter K"
set xrange [0:10]
set xtics 0,1

set ylabel "Time (seconds)"
set yrange [0:160]
set ytics 0, 30

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

# Full plot
plot "".location."kpath0.csv" using 1:2 with linespoints title 'kPathO', \
    "".location."kpath1.csv" using 1:2 with linespoints title 'kPath1', \
    "".location."kpath2.csv" using 1:2 with linespoints title 'kPath2', \
    "".location."kpathN.csv" using 1:2 with linespoints title 'kPathN'

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.6,0.575
set origin 0.35,0.25

set xrange [0:10]        # Zoomed range for X-axis
set xtics 0,2
set yrange [0:1.2]        # Zoomed range for Y-axis
set ytics 1, 1
set ytics add("0.28" 0.28)
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "".location."kpath0.csv" using 1:2 with linespoints title 'kPathO', \
    "".location."kpath1.csv" using 1:2 with linespoints title 'kPath1', \
    "".location."kpath2.csv" using 1:2 with linespoints title 'kPath2', \
    "".location."kpathN.csv" using 1:2 with linespoints title 'kPathN'

unset multiplot