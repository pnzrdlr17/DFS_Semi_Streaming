#!/bin/bash
# Usage ./dataGen.sh TYP N SP TST for random graphs
# Usage ./dataGen.sh TYP N M for real graphs

TYP=$1  # 1 REAL 2 VARN 3 VARM 4 VARK


if [ $TYP = '1' ]
then 

N=$2
M=$3
INPUT_PATH=$4
OUTPUT_PATH=$5

# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 0 0 > "$OUTPUT_PATH"/Simp0.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 0 1 > "$OUTPUT_PATH"/Simp1.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 1 0 > "$OUTPUT_PATH"/Improv.txt

# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 1 > "$OUTPUT_PATH"/KPathO+H1_1.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 2 > "$OUTPUT_PATH"/KPathO+H1_2.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 5 > "$OUTPUT_PATH"/KPathO+H1+H2_5.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 10 > "$OUTPUT_PATH"/KPathO+H1+H2_10.txt

./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 1 > "$OUTPUT_PATH"/KLev_1.txt
./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 2 > "$OUTPUT_PATH"/KLev_2.txt
./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 5 > "$OUTPUT_PATH"/KLev_5.txt
./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 10 > "$OUTPUT_PATH"/KLev_10.txt

# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 3 > "$OUTPUT_PATH"/KPathO+H1+H2_3.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 4 > "$OUTPUT_PATH"/KPathO+H1+H2_4.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 6 > "$OUTPUT_PATH"/KPathO+H1+H2_6.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 7 > "$OUTPUT_PATH"/KPathO+H1+H2_7.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 8 > "$OUTPUT_PATH"/KPathO+H1+H2_8.txt
# ./bin/main_REAL "$N" "$M" "$INPUT_PATH" 2 0 9 > "$OUTPUT_PATH"/KPathO+H1+H2_9.txt

./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 3 > "$OUTPUT_PATH"/KLev_3.txt
./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 4 > "$OUTPUT_PATH"/KLev_4.txt
./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 6 > "$OUTPUT_PATH"/KLev_6.txt
./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 7 > "$OUTPUT_PATH"/KLev_7.txt
./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 8 > "$OUTPUT_PATH"/KLev_8.txt
./bin/main_REAL "$N" "$M" "$INPUT_PATH" 3 0 9 > "$OUTPUT_PATH"/KLev_9.txt





elif [ $TYP = '2' ]
   then

   N=$2
   SP=$3
   TST=$4

   # ./bin/main_VARN "$N" "$SP" "$TST" 0 0 > ./output/powlaw/1000_old_height/main_Simp_VarN_"$N"_"$SP"_"$TST"_O0.txt
   # ./bin/main_VARN "$N" "$SP" "$TST" 0 1 > ./output/powlaw/1000_old_height/main_Simp_VarN_"$N"_"$SP"_"$TST"_O1.txt
   # ./bin/main_VARN "$N" "$SP" "$TST" 1 0 > ./output/powlaw/1000_old_height/main_Improv_VarN_"$N"_"$SP"_"$TST"_S1.txt
   ./bin/main_VARN "$N" "$SP" "$TST" 2 0 10 > ./output/random/1000_new_height/main_KPath_VarN_"$N"_"$SP"_"$TST"_S1.txt
   ./bin/main_VARN "$N" "$SP" "$TST" 3 0 10 > ./output/random/1000_new_height/main_KLev_VarN_"$N"_"$SP"_"$TST"_S1.txt

   elif [ $TYP = '3' ]
      then

      N=$2
      SP=$3
      TST=$4

      
      # ./bin/main_VARM "$N" "$SP" "$TST" 2 0 5 > ./output/powlaw/1000_old/main_KPath_VarM_"$N"_"$SP"_"$TST"_S5.txt
      # ./bin/main_VARM "$N" "$SP" "$TST" 2 0 10 > ./output/powlaw/1000_old/main_KPath_VarM_"$N"_"$SP"_"$TST"_S10.txt
      # ./bin/main_VARM "$N" "$SP" "$TST" 3 0 5 > ./output/powlaw/1000_old/main_KLev_VarM_"$N"_"$SP"_"$TST"_S5.txt
      # ./bin/main_VARM "$N" "$SP" "$TST" 3 0 10 > ./output/powlaw/1000_old/main_KLev_VarM_"$N"_"$SP"_"$TST"_S10.txt
      # ./bin/main_VARM "$N" "$SP" "$TST" 2 0 2 > ./output/powlaw/1000_old/main_KPath_VarM_"$N"_"$SP"_"$TST"_S2.txt
      # ./bin/main_VARM "$N" "$SP" "$TST" 3 0 2 > ./output/powlaw/1000_old/main_KLev_VarM_"$N"_"$SP"_"$TST"_S2.txt
      # ./bin/main_VARM "$N" "$SP" "$TST" 0 1  > ./output/powlaw/1000_old/main_Simp_VarM_"$N"_"$SP"_"$TST"_O1.txt
      # ./bin/main_VARM "$N" "$SP" "$TST" 1 0  > ./output/powlaw/1000_old/main_Improv_VarM_"$N"_"$SP"_"$TST"_S1.txt

      ./bin/main_VARM "$N" "$SP" "$TST" 3 0 10 > ./output/powlaw/1000_new_mnop/main_KLev_VarM_"$N"_"$SP"_"$TST"_S10.txt


      N=$2
      SP=$3
      TST=$4


      # ./bin/main_VARK "$N" 0 "$TST" 2 0 1000 > ./output/random/main_KPath_VarK_"$N"_1_"$SP"_"$TST"_S1.txt
      # ./bin/main_VARK "$N" 1 "$TST" 2 0 1000 > ./output/random/main_KPath_VarK_"$N"_2_"$SP"_"$TST"_S1.txt      
      # ./bin/main_VARK "$N" 0 "$TST" 3 0 1000 > ./output/random/main_KLev_VarK_"$N"_1_"$SP"_"$TST"_S1.txt
      # ./bin/main_VARK "$N" 1 "$TST" 3 0 1000 > ./output/random/main_KLev_VarK_"$N"_2_"$SP"_"$TST"_S1.txt
      
      # ./bin/main_VARK "$N" 2 "$TST" 2 0 1000 > ./output/powlaw/1000_new/main_KPath_VarK_"$N"_1_"$SP"_"$TST"_S1.txt
      # ./bin/main_VARK "$N" 3 "$TST" 2 0 1000 > ./output/powlaw/1000_new/main_KPath_VarK_"$N"_2_"$SP"_"$TST"_S1.txt      
      # ./bin/main_VARK "$N" 4 "$TST" 2 0 1000 > ./output/random/1000_new/main_KPath_VarK_"$N"_3_"$SP"_"$TST"_S1.txt
      ./bin/main_VARK "$N" 2 "$TST" 3 0 1000 > ./output/powlaw/1000_new/main_KLev_VarK_"$N"_1_"$SP"_"$TST"_S1.txt
      ./bin/main_VARK "$N" 3 "$TST" 3 0 1000 > ./output/powlaw/1000_new/main_KLev_VarK_"$N"_2_"$SP"_"$TST"_S1.txt
      # ./bin/main_VARK "$N" 4 "$TST" 3 0 1000 > ./output/random/1000_new/main_KLev_VarK_"$N"_3_"$SP"_"$TST"_S1.txt


   fi
