reset
set terminal png size 680,640 enhanced font "arial,15"
graph_type=ARG1
algorithm=ARG2
input_folder_logN=ARG3
input_folder_sqrtN=ARG4
# input_folder_Nsq=ARG5

set output "results/random/VARK/".graph_type."/plot_".algorithm."_pass.png"

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Space Parameter K"
# set xrange [100:50000000]
set xtics 0,2500
set xtics add("1000" 1000) 
set ylabel "Number of Pass(es)"
set yrange [0:8]
# set ytics 0,1

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."0.csv" using 1:4 with linespoints title "".algorithm."0(1)", \
    "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."N.csv" using 1:4 with linespoints title "".algorithm."N(1)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."0.csv" using 1:4 with linespoints title "".algorithm."0(2)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."N.csv" using 1:4 with linespoints title "".algorithm."N(2)"
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."0.csv" using 1:4 with linespoints title "".algorithm."0", \
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."N.csv" using 1:4 with linespoints title "".algorithm."N"

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.67,0.5
# set origin 0.35,0.49 klev
set origin 0.28,0.4 #kpath
set xlabel font "arial,10"
set ylabel font "arial,10"
set xtics font "arial,10"
set ytics font "arial,10"
set xrange [0:20]        # Zoomed range for X-axis
set xtics 0, 5
# set xtics add("10" 10)
set yrange [0:5]        # Zoomed range for Y-axis
# set ytics 1,2
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."0.csv" using 1:4 with linespoints title "".algorithm."0(1)", \
    "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."N.csv" using 1:4 with linespoints title "".algorithm."N(1)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."0.csv" using 1:4 with linespoints title "".algorithm."0(2)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."N.csv" using 1:4 with linespoints title "".algorithm."N(2)"
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."0.csv" using 1:4 with linespoints title "".algorithm."0", \
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."N.csv" using 1:4 with linespoints title "".algorithm."N"

unset multiplot