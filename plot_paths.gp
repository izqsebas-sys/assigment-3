set title "Disk Head Movement - FCFS / SCAN / C-SCAN"
set xlabel "Número de solicitud"
set ylabel "Cilindro"
set grid
set key left top

plot "fcfs.dat"  using 1:2 with lines lw 2 title "FCFS", \
     "scan.dat"  using 1:2 with lines lw 2 title "SCAN", \
     "cscan.dat" using 1:2 with lines lw 2 title "C-SCAN"
