DATAFILE = "scripts/gnuplot_scripts/reduction_plots/errorbar_kPath_clustered.txt"
OUTFILE  = "scripts/gnuplot_scripts/reduction_plots/errorbar_kPath_clustered.png"

reset
set terminal pngcairo size 2400,900 enhanced font "arial,30"
set output OUTFILE

set multiplot
set autoscale

set bmargin 4

set xlabel "Space Parameter K"
set xrange [0.25:10.75]; set xtics 1,1,10

set yrange [1:100000]
set logscale y 2
set format y "2^{%L}"

set ylabel "Number of Passes"
set key out horiz center top samplen 2 spacing 1 width 1 box
set colors classic
unset clip

# # --------- main plot: four points per‑k, NO cross‑k line -----------
# # explicit x values: 1,1.05,1.10,…,10.40
# plot for [k in "1 1.05 1.10 1.15 1.20 1.25 1.30 1.35 1.40 \
#                1.45 1.50 1.55 1.60 1.65 1.70 1.75 1.80 1.85 1.90 1.95 \
#                2 2.05 2.10 2.15 2.20 2.25 2.30 2.35 2.40 2.45 \
#                2.50 2.55 2.60 2.65 2.70 2.75 2.80 2.85 2.90 2.95 \
#                3 3.05 3.10 3.15 3.20 3.25 3.30 3.35 3.40 3.45 \
#                3.50 3.55 3.60 3.65 3.70 3.75 3.80 3.85 3.90 3.95 \
#                4 4.05 4.10 4.15 4.20 4.25 4.30 4.35 4.40 4.45 \
#                4.50 4.55 4.60 4.65 4.70 4.75 4.80 4.85 4.90 4.95 \
#                5 5.05 5.10 5.15 5.20 5.25 5.30 5.35 5.40 5.45 \
#                5.50 5.55 5.60 5.65 5.70 5.75 5.80 5.85 5.90 5.95 \
#                6 6.05 6.10 6.15 6.20 6.25 6.30 6.35 6.40 6.45 \
#                6.50 6.55 6.60 6.65 6.70 6.75 6.80 6.85 6.90 6.95 \
#                7 7.05 7.10 7.15 7.20 7.25 7.30 7.35 7.40 7.45 \
#                7.50 7.55 7.60 7.65 7.70 7.75 7.80 7.85 7.90 7.95 \
#                8 8.05 8.10 8.15 8.20 8.25 8.30 8.35 8.40 8.45 \
#                8.50 8.55 8.60 8.65 8.70 8.75 8.80 8.85 8.90 8.95 \
#                9 9.05 9.10 9.15 9.20 9.25 9.30 9.35 9.40 9.45 \
#                9.50 9.55 9.60 9.65 9.70 9.75 9.80 9.85 9.90 9.95 \
#                10 10.05 10.10 10.15 10.20 10.25 10.30 10.35 10.40"] \
#         DATAFILE using (($1==k)?$1:1/0):2:3 with linespoints pt variable ps 1.8 lc rgb "red" notitle, \
#      NaN with points lc rgb "red" pt 1 ps 1.8 title sprintf("%s0", "kPath"),\
#      NaN with points lc rgb "red" pt 4 ps 1.8 title sprintf("%s1", "kPath"),\
#      NaN with points lc rgb "red" pt 8 ps 1.8 title sprintf("%s2", "kPath"),\
#      NaN with points lc rgb "red" pt 3 ps 1.8 title sprintf("%sN", "kPath")



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
        DATAFILE using (($1==k)?$1:1/0):2:3 with linespoints pt variable ps 1.8 lc rgb "red" notitle, \
     NaN with points lc rgb "red" pt 1 ps 1.8 title sprintf("%s0", "kPath"),\
     NaN with points lc rgb "red" pt 4 ps 1.8 title sprintf("%s1", "kPath"),\
     NaN with points lc rgb "red" pt 8 ps 1.8 title sprintf("%s2", "kPath"),\
     NaN with points lc rgb "red" pt 3 ps 1.8 title sprintf("%sN", "kPath")


# -------- inset for kPath ------------------------------------------

unset key
unset label
set tics font ", 20"
set size 0.52,0.47
set origin 0.46,0.45
set yrange [1:30]
set ytics ("1" 1, "2" 2, "5" 5, "10" 10, "20" 20)
set xlabel ""
set ylabel ""
replot

plot for [k=1:10] \
    DATAFILE using (($1==k)?$1:1/0):2:3 with linespoints pt variable ps 1.8 lc rgb "red" notitle, \
    NaN with points lc rgb "red" pt 1 ps 1.8 title sprintf("%s0", "kPath"),\
    NaN with points lc rgb "red" pt 4 ps 1.8 title sprintf("%s1", "kPath"),\
    NaN with points lc rgb "red" pt 8 ps 1.8 title sprintf("%s2", "kPath"),\
    NaN with points lc rgb "red" pt 3 ps 1.8 title sprintf("%sN", "kPath")



unset multiplot
unset output

# Usage: gnuplot scripts/gnuplot_scripts/reduction_plots/errorbar_plot_clustered_kPath.gp
