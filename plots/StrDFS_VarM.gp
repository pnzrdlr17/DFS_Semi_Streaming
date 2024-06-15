reset
set terminal png size 700,590 enhanced font "arial,15"
#set terminal png size 700,580 enhanced font "arial,17"
#set terminal png size 680,640 enhanced font "arial,20"
N=ARG1
SP=ARG2
TST=ARG3
TYP=ARG4
location="./output/powlaw/"

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
set output 'plots/nonclipped/powerlaw/kpath_VarM_ncp_'.N.'_SP'.SP.'_'.LAB.'.png'

set multiplot

if(SP=='0')	M = '2n'
if(SP=='1')	M = '5n'
if(SP=='2')	M = 'nlog n'
if(SP=='3') 	M = 'n sqrt(n)'
if(SP=='4') 	M=  'n*n/2'

set   autoscale
#set xlabel "Number of Edges (x 10^5)"
set xlabel "Number of Edges"
set xtics 10000
#set xtics ("1" 100000, "2" 200000,  "3" 300000, "4" 400000)

if(TYP==1||TYP==2){
#set ylabel "Number of passes (x 100)"
set ylabel "Number of passes"
set yrange [0:50]
set ytics 0,5
#set ytics ("1" 100, "2" 200, "3" 300, "4" 400, "5" 500, "6" 600, "7" 700, "8" 800, "9" 900, "10" 1000)
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
set yrange [0:N]
set ytics 0,100
}
if(TYP==6){
set ylabel "Mean Comp Size"
set yrange [0:N]
set ytics 0,100
}
if(TYP==7){
set ylabel "Std Dev Comp Size"
set yrange [0:N]
set ytics 0,100
}

#set xrange [9:]
#set yrange [1:N]

#set yrange [0:100]
#set ytics 0,10

#set format y "%2.0t{/Symbol \327}10^{%L}"
#set xtics 2500000
#set format y "10^{%L}"
#set format y "%7.0f"
set format x "%7.0f"
#set yrange [0:2500000]
#set ytics 0,1


#set ytics 100
#set xrange [0:30100]
#set xtics 10000

set bmargin 5

if(TYP==1||TYP==2){
#set label center at graph 0.5,char 1 "".LAB.". Number of Passes vs Number of Edges (Vertices ".N.")"font ",14"
}
if(TYP==3){
set label center at graph 0.5,char 1 "Height of DFS Tree vs Number of Edges (Vertices ".N.")"font ",14"
}
if(TYP==4){
set label center at graph 0.5,char 1 "Max Comp Size Perc vs Number of Edges (Vertices ".N.")"font ",14"
}
if(TYP==5){
set label center at graph 0.5,char 1 "No of Comp vs Number of Edges (Vertices ".N.")"font ",14"
}
if(TYP==6){
set label center at graph 0.5,char 1 "Mean Comp Size vs Number of Edges (Vertices ".N.")"font ",14"
}
if(TYP==7){
set label center at graph 0.5,char 1 "Std Dev Comp Size vs Number of Edges (Vertices ".N.")"font ",14"
}

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box


# FOR RANDOM GRAPHS

#plot "".location."main_Simp_VarM_".N."_".SP."_".TST."_O1.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
   #  "".location."main_Improv_VarM_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
    # "".location."main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPath(5)' with linespoints, \
    # "".location."main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPath(10)' with linespoints, \
    # "".location."main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLev(5)' with linespoints, \
    # "".location."main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLev(10)' with linespoints, \


#plot "".location."/latest/corrected/Simp_VarM_4.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
   #  "".location."/latest/corrected/Improv_VarM_4.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_4_5.txt" using 1:(column(COL)) title 'kPath(5)' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_4_10.txt" using 1:(column(COL)) title 'KPath(10)' with linespoints, \
   #  "".location."/previous/corrected/Klev_VarM_4_5.txt" using 1:(column(COL)) title 'kLev(5)' with linespoints, \
   #  "".location."/previous/corrected/Klev_VarM_4_10.txt" using 1:(column(COL)) title 'kLev(10)' with linespoints, \


#plot "".location."/latest/corrected/KPath_VarM_4_2.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
  #   "".location."/latest/new/KPath_VarM_4_2.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
  #   "".location."/latest/corrected/KPath_VarM_4_5.txt" using 1:(column(COL)) title 'kPathO(5)' with linespoints, \
  #   "".location."/latest/new/KPath_VarM_4_5.txt" using 1:(column(COL)) title 'KPathN(5)' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_4_10.txt" using 1:(column(COL)) title 'kPathO(10)' with linespoints, \
   #  "".location."/latest/new/KPath_VarM_4_10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \

#plot "".location."/previous/corrected/Klev_VarM_4_2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_4_2.txt" using 1:(column(COL)) title 'KLevN(2)' with linespoints, \
   #  "".location."/previous/corrected/klev_VarM_4_5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_4_5.txt" using 1:(column(COL)) title 'KLevN(5)' with linespoints, \
   #  "".location."/previous/corrected/klev_VarM_4_10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_4_10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \


#plot "".location."/oldkpath/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'KPathO(2)' with linespoints, \
   #  "".location."/newkpath/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
   #  "".location."/oldkpath/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'KPathO(5)' with linespoints, \
   #  "".location."/newkpath/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'KPathN(5)' with linespoints, \
   #  "".location."/oldkpath/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPathO(10)' with linespoints, \
   #  "".location."/newkpath/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \
     

#plot "".location."1000_old/main_Simp_VarM_".N."_".SP."_".TST."_O1.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
   #  "".location."1000_old/main_Improv_VarM_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
   #  "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPath(5)' with linespoints, \
   #  "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPath(10)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLev(5)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLev(10)' with linespoints, \

#plot "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
   #  "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
   #  "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPathO(5)' with linespoints, \
   #  "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPathN(5)' with linespoints, \
   #  "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kPathO(10)' with linespoints, \
   #  "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevN(5)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \

# FOR POWERLAW GRAPHS

#plot "".location."/latest/corrected/KPath_VarM_3_2.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
   #  "".location."/latest/new/KPath_VarM_3_2.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_3_5.txt" using 1:(column(COL)) title 'kPathO(5)' with linespoints, \
   #  "".location."/latest/new/KPath_VarM_3_5.txt" using 1:(column(COL)) title 'KPathN(5)' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_3_10.txt" using 1:(column(COL)) title 'kPathO(10)' with linespoints, \
   #  "".location."/latest/new/KPath_VarM_3_10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \

#plot "".location."/previous/corrected/Klev_VarM_3_2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_3_2.txt" using 1:(column(COL)) title 'KLevN(2)' with linespoints, \
   #  "".location."/previous/corrected/klev_VarM_3_5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_3_5.txt" using 1:(column(COL)) title 'KLevN(5)' with linespoints, \
   #  "".location."/previous/corrected/klev_VarM_3_10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_3_10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \

#plot "".location."1000_old/main_Simp_VarM_".N."_".SP."_".TST."_O1.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
   # "".location."1000_old/main_Improv_VarM_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'Improv' with linespoints, \

plot "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
     "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
     "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPathO(5)' with linespoints, \
     "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPathN(5)' with linespoints, \
     "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kPathO(10)' with linespoints, \
     "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
   #  "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevN(5)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
   #  "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \


#plot "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
   #  "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevN(5)' with linespoints, \
   #  "".location."1000_old_mnop/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
   #  "".location."1000_new_mnop/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \

if((TYP==1||TYP==2)&&1){
unset key
unset label
set size 0.5,0.49
set origin 0.1,0.415
#set title 'Zoom' offset 0,-2

set yrange [0:10]
set ytics 0,2
set xrange [0:8000]
set xtics 4000
set xlabel ""
set ylabel ""


# FOR RANDOM GRAPHS

#plot "".location."main_Simp_VarM_".N."_".SP."_".TST."_O1.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
   #  "".location."main_Improv_VarM_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
    # "".location."main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPath(5)' with linespoints, \
    # "".location."main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPath(10)' with linespoints, \
    # "".location."main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLev(5)' with linespoints, \
    # "".location."main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLev(10)' with linespoints, \


#plot "".location."/latest/corrected/Simp_VarM_4.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
   #  "".location."/latest/corrected/Improv_VarM_4.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_4_5.txt" using 1:(column(COL)) title 'kPath(5)' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_4_10.txt" using 1:(column(COL)) title 'KPath(10)' with linespoints, \
   #  "".location."/previous/corrected/Klev_VarM_4_5.txt" using 1:(column(COL)) title 'kLev(5)' with linespoints, \
   #  "".location."/previous/corrected/Klev_VarM_4_10.txt" using 1:(column(COL)) title 'kLev(10)' with linespoints, \


#plot "".location."/latest/corrected/KPath_VarM_4_2.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
  #   "".location."/latest/new/KPath_VarM_4_2.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
  #   "".location."/latest/corrected/KPath_VarM_4_5.txt" using 1:(column(COL)) title 'kPathO(5)' with linespoints, \
  #   "".location."/latest/new/KPath_VarM_4_5.txt" using 1:(column(COL)) title 'KPathN(5)' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_4_10.txt" using 1:(column(COL)) title 'kPathO(10)' with linespoints, \
   #  "".location."/latest/new/KPath_VarM_4_10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \

#plot "".location."/previous/corrected/Klev_VarM_4_2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_4_2.txt" using 1:(column(COL)) title 'KLevN(2)' with linespoints, \
   #  "".location."/previous/corrected/klev_VarM_4_5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_4_5.txt" using 1:(column(COL)) title 'KLevN(5)' with linespoints, \
   #  "".location."/previous/corrected/klev_VarM_4_10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_4_10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \


#plot "".location."/oldkpath/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'KPathO(2)' with linespoints, \
   #  "".location."/newkpath/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
   #  "".location."/oldkpath/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'KPathO(5)' with linespoints, \
   #  "".location."/newkpath/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'KPathN(5)' with linespoints, \
   #  "".location."/oldkpath/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPathO(10)' with linespoints, \
   #  "".location."/newkpath/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \
     

#plot "".location."1000_old/main_Simp_VarM_".N."_".SP."_".TST."_O1.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
   #  "".location."1000_old/main_Improv_VarM_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'Improv' with linespoints, \
   #  "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPath(5)' with linespoints, \
   #  "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPath(10)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLev(5)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLev(10)' with linespoints, \

#plot "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
   #  "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
   #  "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPathO(5)' with linespoints, \
   #  "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPathN(5)' with linespoints, \
   #  "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kPathO(10)' with linespoints, \
   #  "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevN(5)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \

# FOR POWERLAW GRAPHS

#plot "".location."/latest/corrected/KPath_VarM_3_2.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
   #  "".location."/latest/new/KPath_VarM_3_2.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_3_5.txt" using 1:(column(COL)) title 'kPathO(5)' with linespoints, \
   #  "".location."/latest/new/KPath_VarM_3_5.txt" using 1:(column(COL)) title 'KPathN(5)' with linespoints, \
   #  "".location."/latest/corrected/KPath_VarM_3_10.txt" using 1:(column(COL)) title 'kPathO(10)' with linespoints, \
   #  "".location."/latest/new/KPath_VarM_3_10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \

#plot "".location."/previous/corrected/Klev_VarM_3_2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_3_2.txt" using 1:(column(COL)) title 'KLevN(2)' with linespoints, \
   #  "".location."/previous/corrected/klev_VarM_3_5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_3_5.txt" using 1:(column(COL)) title 'KLevN(5)' with linespoints, \
   #  "".location."/previous/corrected/klev_VarM_3_10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
   #  "".location."/latest/new/klev_VarM_3_10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \

#plot "".location."1000_old/main_Simp_VarM_".N."_".SP."_".TST."_O1.txt" using 1:(column(COL)) title 'Simp' with linespoints, \
   # "".location."1000_old/main_Improv_VarM_".N."_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'Improv' with linespoints, \

plot "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
     "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
     "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPathO(5)' with linespoints, \
     "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kPathN(5)' with linespoints, \
     "".location."1000_old/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kPathO(10)' with linespoints, \
     "".location."1000_new/main_KPath_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KPathN(10)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S2.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevO(5)' with linespoints, \
   #  "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S5.txt" using 1:(column(COL)) title 'kLevN(5)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'kLevO(10)' with linespoints, \
   #  "".location."1000_new/main_KLev_VarM_".N."_".SP."_".TST."_S10.txt" using 1:(column(COL)) title 'KLevN(10)' with linespoints, \


}

unset multiplot

 


