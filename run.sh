# $1 is the name of the corresponding .mtx file
# $2 = 1 for weighted coordinates and 0 for unweighted coordinates

#invoke the graph conversion utility
#bin/graph_csr_cc $2 < data/$1".mtx" > data/$1".txt"

#echo $1 >> results.txt

time_original=$(bin/Ear_Original < data/$1".txt")
time_our=$(bin/Ear_V2 < data/$1".txt")
info=$(bin/info data/$1".txt")

echo $1 $info $time_original $time_our >> results.txt
