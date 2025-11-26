reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder_logN=ARG1
input_folder_sqrtN=ARG2
input_folder_Nsq=ARG3

set output "results/random/VARK/POWLAW/plot_kPath_pass.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Space Parameter K"
set ylabel "Number of Pass(es)"

set xrange [1:50] 
set xtics 0,10

set yrange [0:30] 
set ytics 0,5


set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARK/POWLAW/".input_folder_logN."/kPath0.csv" using 1:4 with linespoints title "kPath0(1)", \
    "results/random/VARK/POWLAW/".input_folder_logN."/kPathN.csv" using 1:4 with linespoints title "kPathN(1)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kPath0.csv" using 1:4 with linespoints title "kPath0(2)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kPathN.csv" using 1:4 with linespoints title "kPathN(2)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kPath0.csv" using 1:4 with linespoints title "kPath0(3)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kPathN.csv" using 1:4 with linespoints title "kPathN(3)"

# Now let's set the zoomed-in plot
unset key
unset label

set xtics font "arial,15"
set ytics font "arial,15"

set size 0.3,0.5
set origin 0.2,0.36

set xlabel ""
set ylabel ""

set xrange [1:4] #kPath        # Zoomed range for X-axis
set xtics 0,1 #kPath
set yrange [0:80] #kPath        # Zoomed range for Y-axis
set ytics 0,15 #kPath


plot "results/random/VARK/POWLAW/".input_folder_logN."/kPath0.csv" using 1:4 with linespoints title "kPath0(1)", \
    "results/random/VARK/POWLAW/".input_folder_logN."/kPathN.csv" using 1:4 with linespoints title "kPathN(1)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kPath0.csv" using 1:4 with linespoints title "kPath0(2)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kPathN.csv" using 1:4 with linespoints title "kPathN(2)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kPath0.csv" using 1:4 with linespoints title "kPath0(3)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kPathN.csv" using 1:4 with linespoints title "kPathN(3)"


unset key
unset label
set size 0.55,0.5
set origin 0.42,0.36

set xtics font "arial,15"
set ytics font "arial,15"
set xlabel ""
set ylabel ""

set xrange [1:1000] #kPath        # Zoomed range for X-axis
set xtics 0,250 #kPath

set yrange [0:5] #kPath        # Zoomed range for Y-axis
set ytics 0,1 #kPath

# Zoomed-in plot
plot "results/random/VARK/POWLAW/".input_folder_logN."/kPath0.csv" using 1:4 with linespoints title "kPath0(1)", \
    "results/random/VARK/POWLAW/".input_folder_logN."/kPathN.csv" using 1:4 with linespoints title "kPathN(1)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kPath0.csv" using 1:4 with linespoints title "kPath0(2)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kPathN.csv" using 1:4 with linespoints title "kPathN(2)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kPath0.csv" using 1:4 with linespoints title "kPath0(3)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kPathN.csv" using 1:4 with linespoints title "kPathN(3)"

unset multiplot

#Usage:  gnuplot -c scripts/gnuplot_scripts/vark/powlaw/vark_plot_pass_kPath.gp sparsity_logN_N_1000_seed_1729_iter_1000_20250721_051734 sparsity_sqrtN_N_1000_seed_1729_iter_1000_20250721_051713 sparsity_N2_N_1000_seed_1729_iter_100_20250719_164310
#Usage:  gnuplot -c scripts/gnuplot_scripts/vark/powlaw/vark_plot_pass_kPath.gp sparsity_logN_N_1000_seed_1729_iter_1000_20250722_999999 sparsity_sqrtN_N_1000_seed_1729_iter_1000_20250722_999999 sparsity_N2_N_1000_seed_1729_iter_100_20250722_999999