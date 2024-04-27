reset
set terminal png size 640,540 enhanced font "arial,15"
N=ARG1
SP=ARG2
TST=ARG3
TYP=ARG4
location="./output/powlaw/final/"

if(TYP==1){
COL=2
LAB='Avg'
}
if(TYP==2){
COL=3
LAB='Max'
}
if(TYP==3){
COL=4
LAB='Height of DFS Tree'
}
if(TYP==4){
COL=5
LAB='Max Comp Size Perc'
}
if(TYP==5){
COL=6
LAB='No of Comp'
}
if(TYP==6){
COL=7
LAB='Mean Comp Size'
}
if(TYP==7){
COL=8
LAB='Std Dev Comp Size'
}

set output 'plots/powlaw/new/VarN_N'.N.'_SP'.SP.'_'.LAB.'.png'

set multiplot

if(SP=='0')	M = '2n'
if(SP=='1')	M = '5n'
if(SP=='2')	M = 'nlog n'
if(SP=='3') 	M = 'n sqrt(n)'
if(SP=='4') 	M=  'n*n/2'

set   autoscale

set xlabel "Number of vertices"
set xrange [9:N+10]

if(TYP==1||TYP==2){
set ylabel "Number of passes"
set yrange [0:1000]
set ytics 0,100
}
if(TYP==3){
set ylabel "Height of DFS Tree"
set yrange [0:1000]
set ytics 0,100
}
if(TYP==4){
set ylabel "Max Comp Size Perc"
set yrange [0:100]
set ytics 0,10
}
if(TYP==5){
set ylabel "No of Comp"
set yrange [0:30]
set ytics 0,2
}
if(TYP==6){
set ylabel "Mean Comp Size"
set yrange [0:N]
set ytics 0,100
}
if(TYP==7){
set ylabel "Std Dev Comp Size"
set yrange [0:300]
set ytics 0,50
}


#set yrange [1:N]

#set yrange [0:300]
#set ytics 0,100

#set format y "%2.0t{/Symbol \327}10^{%L}"
#set xtics 2500000
#set format y "10^{%L}"
#set format y "%7.0f"
set format x "%7.0f"
#set yrange [0:2500000]
#set ytics 0,1

set bmargin 5
if(TYP==1||TYP==2){
#set label center at graph 0.5,char 1 "".LAB.". Number of Passes vs Number of Nodes (Sparsity ".M.")"font ",14"
}
if(TYP==3){
set label center at graph 0.5,char 1 " Height of DFS Tree vs Number of Nodes (Sparsity ".M.")"font ",14" 
}
if(TYP==4){
set label center at graph 0.5,char 1 " Max Comp Size Perc vs Number of Nodes (Sparsity ".M.")"font ",14" 
}
if(TYP==5){
set label center at graph 0.5,char 1 " No of Comp vs Number of Nodes (Sparsity ".M.")"font ",14" 
}
if(TYP==6){
set label center at graph 0.5,char 1 " Mean Comp Size vs Number of Nodes (Sparsity ".M.")"font ",14" 
}
if(TYP==7){
set label center at graph 0.5,char 1 " Std Dev Comp Size vs Number of Nodes (Sparsity ".M.")"font ",14" 
}


set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box



# FOR RANDOM GRAPHS

#plot "".location."main_Simp_VarN_".N."_".SP."_".TST."_O0.txt" using 1:(column(COL)) title 'SimpO' with linespoints, \
     #"".location."main_Simp_VarN_".N."_".SP."_".TST."_O1.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
     #"".location."main_Improv_VarN_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
     #"".location."main_KPath_VarN_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPath' with linespoints, \
     #"".location."main_KLev_VarN_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KLev' with linespoints, 


#plot "".location."/latest/corrected/SimpO_VarN_2_10.txt" using 1:(column(COL)) title 'SimpO' with linespoints, \
 #    "".location."/latest/corrected/Simp_VarN_2_10.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
  #   "".location."/latest/corrected/Improv_VarN_2_10.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
  #   "".location."/latest/corrected/KPath_VarN_2_10.txt" using 1:(column(COL)) title 'KPath' with linespoints, \
  #   "".location."/previous/corrected/klev_VarN_2_10.txt" using 1:(column(COL)) title 'KLev' with linespoints, 

#plot "".location."/latest/corrected/KPath_VarN_3_10.txt" using 1:(column(COL)) title 'KPathO' with linespoints, \
    # "".location."/latest/new/KPath_VarN_3_10.txt" using 1:(column(COL)) title 'KPathN' with linespoints, \
    # "".location."/previous/corrected/klev_VarN_3_10.txt" using 1:(column(COL)) title 'KLevO' with linespoints, \
    # "".location."/latest/new/Klev_VarN_3_10.txt" using 1:(column(COL)) title 'KLevN' with linespoints,
    

# FOR POWERLAW GRAPHS

plot "".location."/latest/corrected/SimpO_VarN_3_10.txt" using 1:(column(COL)) title 'SimpO' with linespoints, \
     "".location."/latest/corrected/Simp_VarN_3_10.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
     "".location."/latest/corrected/Improv_VarN_3_10.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
     "".location."/latest/corrected/KPath_VarN_3_10.txt" using 1:(column(COL)) title 'KPathO' with linespoints, \
     "".location."/latest/new/KPath_VarN_3_10.txt" using 1:(column(COL)) title 'KPathN' with linespoints, \
     "".location."/previous/corrected/klev_VarN_3_10.txt" using 1:(column(COL)) title 'KLevO' with linespoints, \
     "".location."/latest/new/Klev_VarN_3_10.txt" using 1:(column(COL)) title 'KLevN' with linespoints,


if((TYP==1||TYP==2)&&1){
unset key
unset label
set size 0.5,0.5
set origin 0.15,0.4
#set title 'Zoom' offset 0,-2

set xtics 250
set yrange [0:12]
set ytics 0,2
set xlabel ""
set ylabel ""


# FOR RANDOM GRAPHS

#plot "".location."main_Simp_VarN_".N."_".SP."_".TST."_O0.txt" using 1:(column(COL)) title 'SimpO' with linespoints, \
     #"".location."main_Simp_VarN_".N."_".SP."_".TST."_O1.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
     #"".location."main_Improv_VarN_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
     #"".location."main_KPath_VarN_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPath' with linespoints, \
     #"".location."main_KLev_VarN_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KLev' with linespoints, 


#plot "".location."/latest/corrected/SimpO_VarN_2_10.txt" using 1:(column(COL)) title 'SimpO' with linespoints, \
 #    "".location."/latest/corrected/Simp_VarN_2_10.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
  #   "".location."/latest/corrected/Improv_VarN_2_10.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
  #   "".location."/latest/corrected/KPath_VarN_2_10.txt" using 1:(column(COL)) title 'KPath' with linespoints, \
  #   "".location."/previous/corrected/klev_VarN_2_10.txt" using 1:(column(COL)) title 'KLev' with linespoints, 

#plot "".location."/latest/corrected/KPath_VarN_3_10.txt" using 1:(column(COL)) title 'KPathO' with linespoints, \
    # "".location."/latest/new/KPath_VarN_3_10.txt" using 1:(column(COL)) title 'KPathN' with linespoints, \
    # "".location."/previous/corrected/klev_VarN_3_10.txt" using 1:(column(COL)) title 'KLevO' with linespoints, \
    # "".location."/latest/new/Klev_VarN_3_10.txt" using 1:(column(COL)) title 'KLevN' with linespoints,
    

# FOR POWERLAW GRAPHS

plot "".location."/latest/corrected/SimpO_VarN_3_10.txt" using 1:(column(COL)) title 'SimpO' with linespoints, \
     "".location."/latest/corrected/Simp_VarN_3_10.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
     "".location."/latest/corrected/Improv_VarN_3_10.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
     "".location."/latest/corrected/KPath_VarN_3_10.txt" using 1:(column(COL)) title 'KPathO' with linespoints, \
     "".location."/latest/new/KPath_VarN_3_10.txt" using 1:(column(COL)) title 'KPathN' with linespoints, \
     "".location."/previous/corrected/klev_VarN_3_10.txt" using 1:(column(COL)) title 'KLevO' with linespoints, \
     "".location."/latest/new/Klev_VarN_3_10.txt" using 1:(column(COL)) title 'KLevN' with linespoints,

    


}
unset multiplot

 


