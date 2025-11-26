ALG      = ARG1
COL      = (ALG eq "kPath") ? "red" : "blue"
DATAFILE = "scripts/gnuplot_scripts/reduction_plots/errorbar_".ALG.".txt"
OUTFILE  = "scripts/gnuplot_scripts/reduction_plots/errorbar_".ALG.".png"

reset
set terminal png size 1000,600 enhanced font "arial,26"
set output OUTFILE

set multiplot
set autoscale

set xlabel "Space Parameter K"
set xrange [0.5:10.5]; set xtics 1,1,10
set yrange [0:90]; set ytics 0,20
# if (ALG eq "kPath") { set yrange [0:700]; set ytics 0,100 }
                    # else { set yrange [0:7];  set ytics 0,1 }
set ylabel "Improvement % over V0"
set key out horiz center top samplen 2 spacing 1 width 1 box
set colors classic
unset clip

# --------- main plot: four points per‑k, NO cross‑k line -----------
plot for [k=1:10] \
        DATAFILE using (($1==k)?$1:1/0):2:3 with linespoints pt variable ps 1.8 lc rgb COL notitle, \
     NaN with points lc rgb COL pt 1 ps 1.8 title sprintf("%s0", ALG),\
     NaN with points lc rgb COL pt 4 ps 1.8 title sprintf("%s1", ALG),\
     NaN with points lc rgb COL pt 8 ps 1.8 title sprintf("%s2", ALG),\
     NaN with points lc rgb COL pt 3 ps 1.8 title sprintf("%sN", ALG)

# -------- inset for kPath ------------------------------------------
# if (ALG eq "kPath") {
#     unset key
#     unset label
#     set size 0.6,0.65
#     set origin 0.35,0.25
#     set yrange [5:60]
#     set ytics 0,10
#     set xlabel ""
#     set ylabel ""
#     replot

#     plot for [k=1:10] \
#         DATAFILE using (($1==k)?$1:1/0):2:3 with linespoints pt variable ps 1.8 lc rgb COL notitle, \
#      NaN with points lc rgb COL pt 1 ps 1.8 title sprintf("%s0", ALG),\
#      NaN with points lc rgb COL pt 4 ps 1.8 title sprintf("%s1", ALG),\
#      NaN with points lc rgb COL pt 8 ps 1.8 title sprintf("%s2", ALG),\
#      NaN with points lc rgb COL pt 3 ps 1.8 title sprintf("%sN", ALG)

#     unset multiplot
#     unset output
# }

# Usage: gnuplot -c scripts/gnuplot_scripts/reduction_plots/errorbar_plot.gp kLev