DATAFILE = "scripts/gnuplot_scripts/reduction_plots/errorbar_kLev_clustered.txt"
OUTFILE  = "scripts/gnuplot_scripts/reduction_plots/errorbar_kLev_clustered.png"

reset
set terminal pngcairo size 2400,850 enhanced font "arial,30"
set output OUTFILE

set multiplot
set autoscale

set xlabel "Space Parameter K"
set xrange [0.25:10.75]; set xtics 1,1,10

set yrange [0:7]
set ytics 0,1 

set ylabel "Number of Passes"
set key out horiz center top samplen 2 spacing 1 width 1 box
set colors classic
unset clip

# --------- main plot: four points per‑k, NO cross‑k line -----------
# explicit x values: 1,1.05,1.10,…,10.40
plot for [k in "1 1.08 1.16 1.24 1.32 1.40 1.48 1.56 1.64 1.72 \
               2 2.08 2.16 2.24 2.32 2.40 2.48 2.56 2.64 2.72 \
               3 3.08 3.16 3.24 3.32 3.40 3.48 3.56 3.64 3.72 \
               4 4.08 4.16 4.24 4.32 4.40 4.48 4.56 4.64 4.72 \
               5 5.08 5.16 5.24 5.32 5.40 5.48 5.56 5.64 5.72 \
               6 6.08 6.16 6.24 6.32 6.40 6.48 6.56 6.64 6.72 \
               7 7.08 7.16 7.24 7.32 7.40 7.48 7.56 7.64 7.72 \
               8 8.08 8.16 8.24 8.32 8.40 8.48 8.56 8.64 8.72 \
               9 9.08 9.16 9.24 9.32 9.40 9.48 9.56 9.64 9.72 \
               10 10.08 10.16 10.24 10.32 10.40 10.48 10.56 10.64 10.72"] \
        DATAFILE using (($1==k)?$1:1/0):2:3 with linespoints pt variable ps 1.8 lc rgb "blue" notitle, \
     NaN with points lc rgb "blue" pt 1 ps 1.8 title sprintf("%s0", "kLev"),\
     NaN with points lc rgb "blue" pt 4 ps 1.8 title sprintf("%s1", "kLev"),\
     NaN with points lc rgb "blue" pt 8 ps 1.8 title sprintf("%s2", "kLev"),\
     NaN with points lc rgb "blue" pt 3 ps 1.8 title sprintf("%sN", "kLev")

unset multiplot
unset output

# Usage: gnuplot scripts/gnuplot_scripts/reduction_plots/errorbar_plot_clustered_kLev.gp
