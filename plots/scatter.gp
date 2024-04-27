reset
set terminal png size 640,540 enhanced font "arial,15"

location="./output/scatter/"
set output 'plots/scatter/scatter.png'

set multiplot
set   autoscale

set xlabel "Space Parameter K"
set xrange [0:11]
set xtics 0,1

set ylabel "Number of Passes"
set yrange [0:1000]
set ytics 0,100


set label center at graph 0.5,char 1 "Comparison of Old and New Algorithms"

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box



plot "".location."kpath_old.txt" using 1:2 with points pt 1 ps 2 lc rgb "red" title "KPathOld", \
     "".location."kpath_new.txt" using 1:2 with points pt 2 ps 2 lc rgb "blue" title "KPathNew", \
     "".location."klev_old.txt" using 1:2 with points pt 3 ps 2 lc rgb "green" title "KLevOld", \
     "".location."klev_new.txt" using 1:2 with points pt 4 ps 2 lc rgb "orange" title "KLevNew", 
 

unset key
unset label
set size 0.6,0.7
set origin 0.3,0.2


set xtics 0,1
set yrange [0:10]
set ytics 0,1
set xlabel ""
set ylabel ""


plot "".location."kpath_old.txt" using 1:2 with points pt 1 ps 2 lc rgb "red" title "KPathOld", \
     "".location."kpath_new.txt" using 1:2 with points pt 2 ps 2 lc rgb "blue" title "KPathNew", \
     "".location."klev_old.txt" using 1:2 with points pt 3 ps 2 lc rgb "green" title "KLevOld", \
     "".location."klev_new.txt" using 1:2 with points pt 4 ps 2 lc rgb "orange" title "KLevNew", 

unset multiplot

 


