reset
set terminal png size 680,640 enhanced font "arial,15"
graph_type=ARG1
algorithm=ARG2
input_folder_logN=ARG3
input_folder_sqrtN=ARG4
# input_folder_Nsq=ARG5

set output "results/random/VARK/".graph_type."/plot_".algorithm."_time.png"

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Space Parameter K"
set xtics 0,2000
# set xtics 0,10000000

set ylabel "Time (seconds)"
set yrange [0:2.5]
# set ytics 0,0.03

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."0.csv" using 1:2 with linespoints title "".algorithm."0(1)", \
    "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."N.csv" using 1:2 with linespoints title "".algorithm."N(1)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."0.csv" using 1:2 with linespoints title "".algorithm."0(2)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."N.csv" using 1:2 with linespoints title "".algorithm."N(2)"
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."0.csv" using 1:2 with linespoints title "".algorithm."0(3)", \
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."N.csv" using 1:2 with linespoints title "".algorithm."N(3)"

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.62,0.41
# set origin 0.35,0.49 klev
set origin 0.3,0.45 #kpath
set xlabel font "arial,10"
set ylabel font "arial,10"
set xtics font "arial,10"
set ytics font "arial,10"
set xrange [1:10]        # Zoomed range for X-axis
set xtics 0, 2
set yrange [0:30]        # Zoomed range for Y-axis
# set ytics 1,2
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."0.csv" using 1:2 with linespoints title "".algorithm."0(1)", \
    "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."N.csv" using 1:2 with linespoints title "".algorithm."N(1)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."0.csv" using 1:2 with linespoints title "".algorithm."0(2)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."N.csv" using 1:2 with linespoints title "".algorithm."N(2)"
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."0.csv" using 1:2 with linespoints title "".algorithm."0(3)", \
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."N.csv" using 1:2 with linespoints title "".algorithm."N(3)"

unset multiplot