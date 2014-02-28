 

#gcc 03_homework.c   methods.c -o 03_homework   -lm
#./03_homework > 03_homework.results.txt


gcc stack.c  04_Hermite.c -o 04_Hermite
./04_Hermite > 04_Hermite.results.txt

gcc stack.c  04_DivDiff.c -o 04_DivDiff
./04_DivDiff > 04_DivDiff.results.txt


gcc 04_Neville-mod.c -o 04_Neville-mod
./04_Neville-mod > 04_Neville-mod.results.txt

cat 04_Neville-mod.results.txt 04_Hermite.results.txt 04_DivDiff.results.txt > HWSet3.txt
